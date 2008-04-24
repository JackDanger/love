#include "love_opengl.h"
#include "../constants.h"
#include "../version.h"
#include "resources.h"

// SDL
#include <SDL.h>
#include "GLee.h"
#include <SDL_opengl.h>

// DevIL
#include <IL/ilut.h>

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
	love::display_mode current;

	// The desktop display mode.
	love::display_mode desktop;

	// The current set font. (Initially not set).
	pFont current_font;

	// The width of the lines used to draw primitives
	float lineWidth = 1;

	// The Console.
	Console console(800, 300);
	pFont console_font;
	pImage love_logo;

	bool init(love_mod::modconf * conf)
	{
		// Init the SDL video system.
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Could not init SDL_VIDEO: " << SDL_GetError() << std::endl;
			return false;
		}

		// Get the video info 
		video = SDL_GetVideoInfo();

		// Create desktop video mode.
		desktop.height = video->current_h;
		desktop.width = video->current_w;

		// Init DevIL
		ilInit();

		love_mod::setConf(conf);
		love_mod::setFilesystem(conf->filesystem);
		love_mod::report_init("love.graphics", "OpenGL/DevIL");
		return true;
	}

	bool quit()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		love_mod::report_init("love.graphics", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_opengl(s);
		love_mod::do_string("love.graphics = mod_opengl");
		setColorMode(love::COLOR_NORMAL);

		return true;
	}

	// abs, float edition.
	inline float fabs(float f)
	{
		return (f < 0) ? -f : f;
	}

	int is_supported(const love::display_mode & dm)
	{
			Uint32 sdlflags = dm.fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

			// Check if mode is supported
			int bpp = SDL_VideoModeOK(dm.width, dm.height, dm.color_depth, sdlflags);

			if(bpp == 0)
			{
				return 0;
			}

			// Ok, return the color depth.
			return bpp;	
	}

	bool try_change(const love::display_mode & dm)
	{
		// Set GL attributes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, (dm.vsync ? 1 : 0));

		// FSAA
		if(dm.fsaa > 0)
		{
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, dm.fsaa ) ;
		}

		// Fullscreen?
		Uint32 sdlflags = dm.fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Have SDL set the video mode.
		if(SDL_SetVideoMode(dm.width, dm.height, dm.color_depth, sdlflags ) == 0)
		{
			std::cout << "Could not set video mode: "  << SDL_GetError() << std::endl;
			return false;
		}

		SDL_WM_SetCaption("LOVE", 0);

		// Check if FSAA failed or not
		if(dm.fsaa > 0)
		{
			int buffers;
			int samples;

			glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & buffers ) ;
			glGetIntegerv( GL_SAMPLES_ARB, & samples ) ;

			// Don't fail because of this, but issue a warning.
			if ( ! buffers || (samples != dm.fsaa))
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
		glViewport(0,0, dm.width, dm.height);

		// Reset the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up orthographic view (no depth)
		glOrtho(0.0, dm.width,dm.height,0.0, -1.0, 1.0);

		// Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set the new display mode as the current display mode
		current = dm;

		console.resize(dm.width, console.getHeight());

		// Create font.
		if(console_font == 0)
		{
			console_font.reset<Font>(new TrueTypeFont(love::Vera_ttf, 10));
			console_font->load();
		}

		if(love_logo == 0)
		{
			love_logo.reset<Image>(new Image(love::logo128x64_png));
			love_logo->load();
			love_logo->setCenter(0, love_logo->getHeight());
			console.add(love_logo);
			console.add("This is LOVE " LOVE_VERSION_FULL_STR ".");
		}


		return true;
	}

	bool toggleFullscreen()
	{
		// Create new display mode.
		love::display_mode dm = current;
		dm.fullscreen = !current.fullscreen;

		// Reload all Volatiles.
		love::Volatile::unloadAll();

		// Special case for fullscreen -> windowed.
		if( !dm.fullscreen )
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

		// Try to do the change.
		if(!try_change(dm))
			return false;

		bool success = true;
		success = success && love::Volatile::loadAll();

		return success;

	}

	void clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void present()
	{
		SDL_GL_SwapBuffers();
	}

	/**
	* Console.
	**/

	void draw_console()
	{
		// "Push" the state.
		pFont old_font = current_font;
		glPushAttrib(GL_CURRENT_BIT);
		
		current_font = console_font;
		console.draw(0, current.height);

		// "Pop" the state.
		glPopAttrib();
		current_font = old_font;
	}

	void print(const char * str)
	{
		std::string text(str);

		// Check for "tags".
		if(text == "LOVE")
		{
			console.add(love_logo);
			return;
		}
		if(text == "[box]")
		{
			console.push_box();
			return;
		}
		if(text == "[error]")
		{
			console.push_error();
			return;
		}
		if(text == "[/box]" || text == "[/error]")
		{
			console.pop();
			return;
		}

		if(text.find("\n") == std::string::npos)
		{
			console.add(text);
			return;
		}

		// Normal text with line breaks:

		int lines = 0;
		text = "";
		
		for(unsigned int i = 0; i < std::strlen(str); i++)
		{
			if(str[i] == '\n')
			{
				console.add(text);
				text = "";
				lines++;
			}
			else
				text += str[i];
		}
		
		if(text != "") // Print the last text (if applicable).
			console.add(text);	
	}

	bool checkMode(int width, int height, bool fullscreen)
	{
		love::display_mode dm;
		dm.width = width;
		dm.height = height;
		dm.fullscreen = fullscreen;
		dm.color_depth = 32;

		return ( is_supported(dm) == dm.color_depth );
	}


	bool setMode(int width, int height, bool fullscreen, bool vsync, int fsaa)
	{
		love::display_mode dm;
		dm.width = width;
		dm.height = height;
		dm.fullscreen = fullscreen;
		dm.color_depth = 32;
		dm.vsync = vsync;
		dm.fsaa = fsaa;

		return try_change(dm);
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
		default: // ALWAYS MOOSE:
			return newImage(love::mini_moose_png);
			break;
		}
	}

	pImage newImage(const char * filename)
	{

		love::pFile file = love_mod::newFile(filename);

		// Create and return an image.
		pImage image(new Image(file));
		image->load();
		return image;
	}

	pImage newImage(love::pFile file)
	{
		// Create and return an image.
		pImage image(new Image(file));
		image->load();
		return image;
	}

	pImage newImage(const char * filename, int mode)
	{
		love::pFile file = love_mod::newFile(filename);

		// Create the new image.
		pImage image(new Image(file));

		switch(mode)
		{
		case love::IMAGE_OPTIMIZE:
			if(!image->read()) 
				break;
			image->optimize();
			if(!image->lock()) 
				break;
			break;
		case love::IMAGE_PAD:
			if(!image->read()) 
				break;
			image->pad();
			if(!image->lock()) 
				break;
			break;
		case love::IMAGE_PAD_AND_OPTIMIZE:
			if(!image->read()) 
				break;
			image->pad();
			image->optimize();
			if(!image->lock()) 
				break;
			break;
		default:
			// If an unrecognized number is passed:
			image->load();
			break;
		}

		return image;
	}

	pFont newFont(const char * filename, int size)
	{
		love::pFile file = love_mod::newFile(filename);
		pFont font(new TrueTypeFont(file, size));
		font->load();
		return font;
	}

	pFont newFont(int f, int size)
	{
		
		// There's only one default font yet, so
		// the f-integer isn't really checked.

		pFont font(new TrueTypeFont(love::Vera_ttf, size));
		font->load();
		return font;
	}

	pFont newImageFont(const char * filename, const char * glyphs, float spacing)
	{
		love::pFile file = love_mod::newFile(filename);
		pFont font(new ImageFont(file, std::string(glyphs)));
		font->setSpacing(spacing);
		font->load();
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

		// Create the animation.
		pAnimation anim(new Animation(img));
		return anim;
	}

	pAnimation newAnimation(const char * filename, float fw, float fh, float delay, int num)
	{
		// Load the image.
		pImage img = newImage(filename);

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

	int getWidth()
	{
		return current.width;
	}

	int getHeight()
	{
		return current.height;
	}

	void setColor( int r, int g, int b, int a)
	{
		glColor4ub(r, g, b, a);
	}

	void setColor( const pColor & color )
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	void setBackgroundColor( int r, int g, int b )
	{
		glClearColor( (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
	}

	void setBackgroundColor( const pColor & color )
	{
		glClearColor( (float)color->getRed()/255.0f, (float)color->getGreen()/255.0f, (float)color->getBlue()/255.0f, 1.0f);
	}

	void setFont( pFont font )
	{
		current_font = font;
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
