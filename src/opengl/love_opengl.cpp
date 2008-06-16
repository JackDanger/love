#include "love_opengl.h"

// LOVE
#include <love/version.h>
#include <love/constants.h>
#include <love/Exception.h>
#include <love/Core.h>

// Module.
#include "resources.h"

// SDL
#include <SDL.h>
#include "GLee.h"
#include <SDL_opengl.h>

// DevIL
#include <IL/il.h>

// Math
#include <math.h>

// From SWIG.
extern "C" {
	int luaopen_mod_opengl(lua_State * L);
}

namespace love_opengl
{
	// Contains SDL's information about the display device.
	const SDL_VideoInfo * video;

	// The current display mode.
	struct display_mode
	{
		int width, height; // The size of the screen.
		int color_depth; // The color depth of the display mode.
		bool fullscreen; // Fullscreen (true), or windowed (false).
		bool vsync; // Vsync enabled (true), or disabled (false).
		int fsaa; // 0 for no FSAA, otherwise 1, 2 or 4.
	};
	
	// The one and only display_mode instance.
	display_mode current_mode;

	// The current set font. (Initially not set).
	pFont current_font;

	// The width of the lines used to draw primitives
	float lineWidth = 1;

	// Function pointers.
	love::pFile * (*getFile)(const char *) = 0;
	love::Core * core = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		love_opengl::core = core;

		// Init the SDL video system.
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Could not init SDL_VIDEO: " << SDL_GetError() << std::endl;
			return false;
		}

		try
		{
			getFile = (love::pFile * (*)(const char *))core->getf(love::Module::FILESYSTEM, "getFile");
		}
		catch(love::Exception exc)
		{
			std::cerr << exc.msg() << std::endl;
			return false;
		}

		SDL_WM_SetCaption("LOVE " LOVE_VERSION_FULL_STR, 0);

		// Get the video info 
		video = SDL_GetVideoInfo();

		// Init DevIL
		ilInit();

		current_mode.width = 0;
		current_mode.height = 0;

		std::cout << "INIT love.graphics [" << "OpenGL/DevIL/FreeType" << "]" << std::endl;
		return true;
	}

	bool module_quit()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		std::cout << "QUIT love.graphics [" << "OpenGL/DevIL/FreeType" << "]" << std::endl;	
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_opengl(s);
		return true;
	}

	// abs, float edition.
	inline float fabs(float f)
	{
		return (f < 0) ? -f : f;
	}

	bool feature(int f)
	{
		switch(f)
		{
		case love::POINT_SPRITE:
			return (GLEE_ARB_point_sprite == GL_TRUE);
			break;
		}

		return false;
	}

	bool checkMode(int width, int height, bool fullscreen)
	{
		Uint32 sdlflags = fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Check if mode is supported
		int bpp = SDL_VideoModeOK(width, height, 32, sdlflags);

		return (bpp >= 16);	
	}

	bool setMode(int width, int height, bool fullscreen, bool vsync, int fsaa)
	{

		// Temp variables that holds the saved
		// graphics state if we are *changing* display mode.
		pColor color, bg;
		int blend_mode = 0, color_mode = 0;
		float line_width = 1;
		bool line_smooth = true;

		// If screen is already created, then we're about to 
		// change the display mode.
		if(isCreated())
		{
			// Save the state.
			color = getColor();
			bg = getBackgroundColor();
			blend_mode = getBlendMode();
			color_mode = getColorMode();
			line_smooth = glIsEnabled(GL_LINE_SMOOTH) == GL_TRUE;
			glGetFloatv(GL_LINE_WIDTH, &line_width);

			// Caption too.
			std::string caption = getCaption();

			// Reload all Volatiles.
			Volatile::unloadAll();

			// Special case for fullscreen -> windowed.
			if( !current_mode.fullscreen )
			{
				// Restarting the SDL_VIDEO subsystem was the only thing
				// that did what I wanted.
				SDL_QuitSubSystem(SDL_INIT_VIDEO);

				if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
				{
					std::cout << "Could not init SDL_VIDEO: " << SDL_GetError() << std::endl;
					return false;
				}
			}

			// Set caption here, not with the rest of the state.
			setCaption(caption.c_str());
		}

		// Set GL attributes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, (vsync ? 1 : 0));

		// FSAA
		if(fsaa > 0)
		{
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, fsaa ) ;
		}

		// Fullscreen?
		Uint32 sdlflags = fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Have SDL set the video mode.
		if(SDL_SetVideoMode(width, height, 32, sdlflags ) == 0)
		{
			std::cerr << "Could not set video mode: "  << SDL_GetError() << std::endl;
			return false;
		}

		// Check if FSAA failed or not
		if(fsaa > 0)
		{
			int buffers;
			int samples;

			glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & buffers ) ;
			glGetIntegerv( GL_SAMPLES_ARB, & samples ) ;

			// Don't fail because of this, but issue a warning.
			if ( ! buffers || (samples != fsaa))
				printf("Warning, quality setting failed! (Result: buffers: %i, samples: %i)\n", buffers, samples);
		}

		
		// Okay, setup OpenGL.

		// Enable blending
		glEnable(GL_BLEND);

		// "Normal" blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable line smoothing.
		glEnable (GL_LINE_SMOOTH);
		glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

		// Cull backface
		glEnable(GL_CULL_FACE);		// Enable face culling (no need to render surfaces we can't see
		glCullFace(GL_BACK);		// Do not render back face.

		// Set the background color
		glClearColor( 0.0, 0.0, 0.0, 0.0 );
		glColor4ub(255, 255, 255, 255);

		// Enable textures
		glEnable(GL_TEXTURE_2D);	

		// Set the viewport to top-left corner
		glViewport(0,0, width, height);

		// Reset the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up orthographic view (no depth)
		glOrtho(0.0, width, height,0.0, -1.0, 1.0);

		// Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Restore the saved state, if any.
		if(isCreated())
		{
			if(!Volatile::loadAll())
				std::cerr << "Could not reload all volatile objects." << std::endl;

			// Restore the state.
			setColor(color);
			setBackgroundColor(bg);
			setBlendMode(blend_mode);
			setColorMode(color_mode);
			setLine(line_width, line_smooth ? love::LINE_SMOOTH : love::LINE_ROUGH);
		}

		// Set the new display mode as the current display mode.
		current_mode.width = width;
		current_mode.height = height;
		current_mode.color_depth = 32;
		current_mode.fsaa = fsaa;
		current_mode.fullscreen = fullscreen;
		current_mode.vsync = vsync;

		return true;
	}

	bool toggleFullscreen()
	{
		current_mode.fullscreen = !current_mode.fullscreen;

		// Try to do the change.
		if(!setMode(current_mode.width, current_mode.height, current_mode.fullscreen, 
			current_mode.vsync, current_mode.fsaa))
			return false;
		return true;
	}

	void reset()
	{
		setColor(255, 255, 255);
		setBackgroundColor(0, 0, 0);
		setBlendMode(love::BLEND_NORMAL);
		setColorMode(love::COLOR_NORMAL);
		setLine(1, love::LINE_SMOOTH);
	}

	void clear_screen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void present()
	{
		SDL_GL_SwapBuffers();
	}

	int getModes(lua_State * L)
	{

		// Windowed:

		SDL_Rect ** modes = SDL_ListModes(0, SDL_OPENGL | SDL_FULLSCREEN);

		if(modes == (SDL_Rect **)0 || modes == (SDL_Rect **)-1)
			return 0;

		int index = 1;

		lua_newtable(L);

		for(int i=0;modes[i];++i)
		{
			lua_pushinteger(L, index);
			lua_newtable(L);

			// Inner table attribs.

			lua_pushstring(L, "width");
			lua_pushinteger(L, modes[i]->w);
			lua_settable(L, -3);

			lua_pushstring(L, "height");
			lua_pushinteger(L, modes[i]->h);
			lua_settable(L, -3);

			// Inner table attribs end.

			lua_settable(L, -3);

			index++;
		}

		return 1;
	}

	pColor newColor( int r, int g, int b, int a )
	{
		pColor c(new Color(r, g, b, a));
		return c;
	}

	pImage newImage(int image)
	{
		switch(image)
		{
		case love::DEFAULT_LOGO_128:
			return newImage(love::logo128x64_png);
			break;
		case love::DEFAULT_LOGO_256:
			return newImage(love::logo256x128_png);
			break;
		case love::DEFAULT_VERMIN:
			return newImage(love::mutant_vermin_png, love::IMAGE_OPTIMIZE);
			break;
		default: // ALWAYS MOOSE:
			return newImage(love::mini_moose_png);
			break;
		}
	}

	pImage newImage(const char * filename)
	{
		love::pFile * file = getFile(filename);
		pImage image = newImage(*file);
		delete file;
		return image;
	}

	pImage newImage(love::pFile file)
	{
		// Create the image file.
		pImage image(new Image(file));

		// Load the image. Check for errors.
		if(!image->load())
		{
			std::stringstream ss;
			ss << "Could not load image \"" << file->getFilename() << "\".";

			// Trigger error.
			core->error(ss.str().c_str());
		}
		return image;
	}

	pImage newImage(love::pFile file, int mode)
	{
		// Create the new image.
		pImage image(new Image(file));

		// Read the image.
		if(!image->read())
		{	
			std::stringstream err;
			err << "Could not load image \"" << file->getFilename() << "\".";
			core->error(err.str().c_str());
			return image;
		}

		// Optionally pad.
		if(mode == love::IMAGE_PAD || mode == love::IMAGE_PAD_AND_OPTIMIZE)
			image->pad();

		// Optionally optimize.
		if(mode == love::IMAGE_OPTIMIZE || mode == love::IMAGE_PAD_AND_OPTIMIZE)
			image->optimize();

		// Lock the image.
		if(!image->lock())
		{
			std::stringstream err;
			err << "Could not lock image \"" << file->getFilename() << "\".";
			core->error(err.str().c_str());
			return image;
		}

		return image;
	}

	pImage newImage(const char * filename, int mode)
	{
		love::pFile * file = getFile(filename);

		// Create the new image.
		pImage image = newImage(*file);

		delete file;

		return image;
	}

	pFont newFont(const char * filename, int size)
	{
		love::pFile * file = getFile(filename);
		pFont font(new TrueTypeFont(*file, size));
		delete file;

		// Load it and check for errors.
		if(!font->load())
		{
			std::stringstream err;
			err << "Could not load font \"" << filename << "\".";
			core->error(err.str().c_str());
		}

		return font;
	}

	pFont newFont(int f, int size)
	{
		
		// There's only one default font yet, so
		// no need to check f.

		pFont font(new TrueTypeFont(love::Vera_ttf, size));
		if(!font->load())
			std::cerr << "Could not load default font!" << std::endl;
		return font;
	}

	pFont newImageFont(const char * filename, const char * glyphs, float spacing)
	{
		love::pFile * file = getFile(filename);
		pFont font(new ImageFont(*file, std::string(glyphs)));
		delete file;
		font->setSpacing(spacing);

		// Load it and check for errors.
		if(!font->load())
		{
			std::stringstream err;
			err << "Could not load imagefont \"" << filename << "\".";
			core->error(err.str().c_str());
		}

		return font;
	}

	pAnimation newAnimation(pImage image)
	{
		// Create the animation.
		pAnimation anim(new Animation(image));
		return anim;
	}

	pAnimation newAnimation(pImage image, float fw, float fh, float delay, int num)
	{
		// Create the animation.
		pAnimation anim(new Animation(image, fw, fh, delay, num));
		return anim;
	}

	pAnimation newAnimation(const char * filename)
	{
		// Load the image.
		pImage img = newImage(filename);

		if(!img->load())
		{
			std::stringstream err;
			err << "Could not load animation \"" << filename << "\".";
			core->error(err.str().c_str());
		}

		// Create the animation.
		pAnimation anim(new Animation(img));
		return anim;
	}

	pAnimation newAnimation(const char * filename, float fw, float fh, float delay, int num)
	{
		// Load the image.
		pImage img = newImage(filename);

		if(!img->load())
		{
			std::stringstream err;
			err << "Could not load animation \"" << filename << "\".";
			core->error(err.str().c_str());
		}

		// Create the animation.
		pAnimation anim(new Animation(img, fw, fh, delay, num));
		return anim;
	}

	pParticleSystem newParticleSystem(pImage sprite, unsigned int size)
	{
		// Create the particle system.
		pParticleSystem part(new ParticleSystem(sprite, size));
		return part;
	}

	pParticleSystem newParticleSystem(pImage sprite, unsigned int size, int mode)
	{
		if(feature(mode))
		{
			// Create the particle system.
			pParticleSystem part(new PointParticleSystem(sprite, size));
			return part;	
		}
		
		return newParticleSystem(sprite, size);
	}

	void setCaption(const char * caption)
	{
		SDL_WM_SetCaption(caption, 0);
	}

	int getWidth()
	{
		return current_mode.width;
	}

	int getHeight()
	{
		return current_mode.height;
	}

	bool isCreated()
	{
		return (current_mode.width > 0) || (current_mode.height > 0);
	}

	void setScissor(int x, int y, int width, int height)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, width, height);
	}

	std::string getCaption()
	{	
		char * title = 0;
		SDL_WM_GetCaption(&title, 0);
		return std::string(title);
	}

	void setColor( int r, int g, int b, int a)
	{
		glColor4ub(r, g, b, a);
	}

	void setColor( const pColor & color )
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	pColor getColor()
	{
		float c[4];
		glGetFloatv(GL_CURRENT_COLOR, c);
		pColor clr(new Color((int)(255.0f*c[0]), (int)(255.0f*c[1]), (int)(255.0f*c[2]), (int)(255.0f*c[3])));
		return clr;
	}

	void setBackgroundColor( int r, int g, int b )
	{
		glClearColor( (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
	}

	void setBackgroundColor( const pColor & color )
	{
		glClearColor( (float)color->getRed()/255.0f, (float)color->getGreen()/255.0f, (float)color->getBlue()/255.0f, 1.0f);
	}

	pColor getBackgroundColor()
	{
		float c[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, c);
		pColor clr(new Color((int)(255.0f*c[0]), (int)(255.0f*c[1]), (int)(255.0f*c[2]), (int)(255.0f*c[3])));
		return clr;
	}

	void setFont( pFont font )
	{
		current_font = font;
	}

	pFont getFont()
	{
		return current_font;
	}

	void setBlendMode( int mode )
	{
		if(mode == love::BLEND_ADDITIVE)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else // mode == love::BLEND_NORMAL
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void setColorMode ( int mode )
	{
		if(mode == love::COLOR_MODULATE)
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		else // mode = love::COLOR_NORMAL
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	
	int getBlendMode()
	{
		int dst, src;
		glGetIntegerv(GL_BLEND_DST, &dst);
		glGetIntegerv(GL_BLEND_SRC, &src);

		if(dst == GL_SRC_ALPHA && src == GL_ONE)
			return love::BLEND_ADDITIVE;
		else // dst == GL_SRC_ALPHA && src == GL_ONE_MINUS_SRC_ALPHA
			return love::BLEND_NORMAL;
	}

	int getColorMode()
	{
		int mode;
		glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &mode);

		if(mode == GL_MODULATE)
			return love::COLOR_MODULATE;
		else // // mode == GL_REPLACE
			return love::COLOR_NORMAL;
	}

	void setLine( float width, int type )
	{
		lineWidth = width;

		if(type == 0)
			return;

		if(type == love::LINE_ROUGH)
			glDisable (GL_LINE_SMOOTH);
		else // type == love::LINE_SMOOTH
		{
			glEnable (GL_LINE_SMOOTH);
			glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
		}

	}

	float push_color_mode()
	{
		float t;
		glGetTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &t);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		return t;
	}

	void pop_color_mode(float f)
	{
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, f);
	}

	/**
	* Text drawing.
	**/
	void draw( const char * str, float x, float y )
	{
		if(current_font != 0)
		{
			float texenv = push_color_mode();

			std::string text(str);

			if(text.find("\n") == std::string::npos)
				current_font->print(text, x, y);
			else
			{
				int lines = 0;
				text = "";
				
				for(unsigned int i = 0; i < std::strlen(str); i++)
				{
					if(str[i] == '\n')
					{
						current_font->print(text, x, y + (lines * current_font->getHeight() * current_font->getLineHeight()));
						text = "";
						lines++;
					}
					else
						text += str[i];
				}
				
				if(text != "") // Print the last text (if applicable).
					current_font->print(text, x, y + (lines * current_font->getHeight() * current_font->getLineHeight()));
			}

			pop_color_mode(texenv);

		}
	}

	void draw( const char * str, float x, float y , float angle)
	{
		if(current_font != 0)
		{
			float texenv = push_color_mode();
			std::string text(str);
			current_font->print(text, x, y, angle, 1, 1);
			pop_color_mode(texenv);
		}
	}

	void draw( const char * str, float x, float y , float angle, float s)
	{
		if(current_font != 0)
		{
			float texenv = push_color_mode();
			std::string text(str);
			current_font->print(text, x, y, angle, s, s);
			pop_color_mode(texenv);
		}
	}

	void draw( const char * str, float x, float y , float angle, float sx, float sy)
	{
		if(current_font != 0)
		{
			float texenv = push_color_mode();
			std::string text(str);
			current_font->print(text, x, y, angle, sx, sy);
			pop_color_mode(texenv);
		}
	}


	void drawf( const char * str, float x, float y, float wrap, int align)
	{
		const pFont & font = current_font;

		if(font != 0)
		{
			float texenv = push_color_mode();
			std::string text = "";
			float width = 0;
			float lines = 0;
			
			for(unsigned int i = 0; i < std::strlen(str); i++)
			{
				if(str[i] == '\n')
				{
					switch(align)
					{
						case love::ALIGN_LEFT:
							font->print(text, x, y + (lines * font->getHeight() * font->getLineHeight()) );
							break;
							
						case love::ALIGN_RIGHT:
							font->print(text, (x + (wrap - font->getWidth(text))), y + (lines * font->getHeight() * font->getLineHeight()) );
							break;
							
						case love::ALIGN_CENTER:
							font->print(text, ceil(x + ((wrap - font->getWidth(text)) / 2)), ceil(y + (lines * font->getHeight() * font->getLineHeight())) );
							break;
							
						default: // A copy of the left align code. Kept separate in case an error message is wanted.
							font->print(text, x, y + (lines * font->getHeight() * font->getLineHeight()) );
							break;
					}

					text = "";
					width = 0;
					lines++;
				}
				else
				{
					width += font->getWidth(str[i]);
					
					if(width > wrap && text.find(" ") != std::string::npos) // If there doesn't exist a space, then ignore the wrap limit.
					{						
						// Seek back to the nearest space and print that.
						unsigned int space = (unsigned int)text.find_last_of(' ');
						std::string temp = text.substr(0, space);
						
						switch(align)
						{
							case love::ALIGN_LEFT:
								font->print(temp, x, y + (lines * font->getHeight() * font->getLineHeight()) );
								break;
							
							case love::ALIGN_RIGHT:
								font->print(temp, (x + (wrap - font->getWidth(temp))), y + (lines * font->getHeight() * font->getLineHeight()) );
								break;
							
							case love::ALIGN_CENTER:
								font->print(temp, ceil(x + ((wrap - font->getWidth(temp)) / 2)), ceil(y + (lines * font->getHeight() * font->getLineHeight())) );
								break;
							
							default: // A copy of the left align code. Kept separate in case an error message is wanted.
								font->print(temp, x, y + (lines * font->getHeight() * font->getLineHeight()) );
								break;
						}	
						
						text = text.substr(space + 1);
						width = font->getWidth(text);
						lines++;
					}
					
					text += str[i];
				}
			} // for

			if(text != "") // Print the last text (if applicable).
			{
				switch(align)
				{
					case love::ALIGN_LEFT:
						font->print(text, x, y + (lines * font->getHeight() * font->getLineHeight()) );
						break;
							
					case love::ALIGN_RIGHT:
						font->print(text, (x + (wrap - font->getWidth(text))), y + (lines * font->getHeight() * font->getLineHeight()) );
						break;
							
					case love::ALIGN_CENTER:
						font->print(text, ceil(x + ((wrap - font->getWidth(text)) / 2)), ceil(y + (lines * font->getHeight() * font->getLineHeight())) );
						break;
							
					default: // A copy of the left align code. Kept separate in case an error message is wanted.
						font->print(text, x, y + (lines * font->getHeight() * font->getLineHeight()));
						break;
				}
			} 

			pop_color_mode(texenv);
		}
	}



	/**
	* Image drawing functions.
	**/

	void draw( const pImage & sprite, float x, float y )
	{
		sprite->draw(x, y);
	}

	void draw( const pImage & sprite, float x, float y , float angle)
	{
		sprite->draw(x, y, angle, 1, 1);
	}

	void draw( const pImage & sprite, float x, float y , float angle, float s)
	{
		sprite->draw(x, y, angle, s, s);
	}

	void draw( const pImage & sprite, float x, float y , float angle, float sx, float sy)
	{
		int f = love::FLIP_NONE;

		if( sx < 0 && sy > 0 )
		{
			f = love::FLIP_VERTICAL;
			sx = fabs(sx);
		}
		if( sy < 0 && sx > 0 )
		{
			f = love::FLIP_HORIZONTAL;
			sy = fabs(sy);
		}

		sprite->draw(x, y, angle, sx, sy, f);
	}

	/**
	* Subsprite.
	**/

	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h )
	{
		sprite->draws(x, y, cx, cy, w, h, 0, 1, 1, -w/2.0f, -h/2.0f, love::FLIP_NONE);
	}

	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle)
	{
		sprite->draws(x, y, cx, cy, w, h, angle, 1, 1, -w/2.0f, -h/2.0f, love::FLIP_NONE);
	}

	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float s)
	{
		sprite->draws(x, y, cx, cy, w, h, angle, s, s, -w/2.0f, -h/2.0f, love::FLIP_NONE);
	}
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy)
	{
		sprite->draws(x, y, cx, cy, w, h, angle, sx, sy, -w/2.0f, -h/2.0f, love::FLIP_NONE);
	}

	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy, float ox, float oy)
	{
		sprite->draws(x, y, cx, cy, w, h, angle, sx, sy, ox, oy, love::FLIP_NONE);
	}

	/**
	* Animation 
	**/

	void draw( const pAnimation & sprite, float x, float y )
	{
		sprite->draw(x, y);
	}

	void draw( const pAnimation & sprite, float x, float y, float angle)
	{
		sprite->draw(x, y, angle, 1, 1, love::FLIP_NONE);
	}

	void draw( const pAnimation & sprite, float x, float y, float angle, float s)
	{
		sprite->draw(x, y, angle, s, s, love::FLIP_NONE);
	}

	void draw( const pAnimation & sprite, float x, float y, float angle, float sx, float sy)
	{
		int f = love::FLIP_NONE;

		if( sx < 0 && sy > 0 )
		{
			f = love::FLIP_VERTICAL;
			sx = fabs(sx);
		}
		if( sy < 0 && sx > 0 )
		{
			f = love::FLIP_HORIZONTAL;
			sy = fabs(sy);
		}

		sprite->draw(x, y, angle, sx, sy, f);
	}

	/**
	* Particle System
	**/
	void draw( const pParticleSystem & system, float x, float y)
	{
		system->draw(x, y);
	}

	/**
	* Primitives
	**/

	void point( float x, float y )
	{
		glPointSize(1.0f);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POINTS);
			glVertex2f(x, y);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void line( float x1, float y1, float x2, float y2 )
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

	void triangle( int type, float x1, float y1, float x2, float y2, float x3, float y3 )
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		switch(type)
		{
		case love::DRAW_LINE:
			glLineWidth(lineWidth);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
			break;

		default:
		case love::DRAW_FILL:
			glBegin(GL_TRIANGLES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
			break;
		}

		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

	void quad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 )
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		switch(type)
		{
		case love::DRAW_LINE:
			glLineWidth(lineWidth);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);				
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
			break;

		default:
		case love::DRAW_FILL:
			glBegin(GL_QUADS);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
			break;
		}

		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

	void circle( int type, float x, float y, float radius, int points )
	{
		float two_pi = 3.14159265f * 2;
		if(points <= 0) points = 1;
		float angle_shift = (two_pi / points);

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		glTranslatef(x, y, 0.0f);

		switch(type)
		{
		case love::DRAW_LINE:
			glLineWidth(lineWidth);
			glBegin(GL_LINE_LOOP);

			for(float i = 0; i < two_pi; i+= angle_shift)
				glVertex2f(radius * sin(i),radius * cos(i));

			glEnd();
			break;

		default:
		case love::DRAW_FILL:
			glBegin(GL_TRIANGLE_FAN);

			for(float i = 0; i < two_pi; i+= angle_shift)
				glVertex2f(radius * sin(i),radius * cos(i));

			glEnd();
			break;
		}

		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

} // love_opengl
