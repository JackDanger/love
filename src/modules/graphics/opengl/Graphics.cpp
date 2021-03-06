/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "Graphics.h"

// LOVE
#include <common/config.h>
#include <common/constants.h>

namespace love
{
namespace graphics
{
namespace opengl
{

	Graphics::Graphics()
		: currentFont(0)
	{
		// Indicates that there is no screen
		// created yet.
		currentMode.width = 0;
		currentMode.height = 0;

		// Windows should be centered.
		SDL_putenv("SDL_VIDEO_CENTERED=center");

		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
			throw Exception(SDL_GetError());
	}

	Graphics::~Graphics()
	{
		if(currentFont != 0)
			currentFont->release();

		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}

	const char * Graphics::getName() const
	{
		return "love.graphics.opengl";
	}

	bool Graphics::checkMode(int width, int height, bool fullscreen)
	{
		Uint32 sdlflags = fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Check if mode is supported
		int bpp = SDL_VideoModeOK(width, height, 32, sdlflags);

		return (bpp >= 16);	
	}

	DisplayState Graphics::saveState()
	{
		DisplayState s;
		//create a table in which to store the color data in float format, before converting it
		float color[4];
		//get the color
		glGetFloatv(GL_CURRENT_COLOR, color);
		s.color[0] = (GLubyte)(color[0]*255.0f);
		s.color[1] = (GLubyte)(color[1]*255.0f);
		s.color[2] = (GLubyte)(color[2]*255.0f);
		s.color[3] = (GLubyte)(color[3]*255.0f);
		//get the background color
		glGetFloatv(GL_COLOR_CLEAR_VALUE, color);
		s.backgroundColor[0] = (GLubyte)(color[0]*255.0f);
		s.backgroundColor[1] = (GLubyte)(color[1]*255.0f);
		s.backgroundColor[2] = (GLubyte)(color[2]*255.0f);
		s.backgroundColor[3] = (GLubyte)(color[3]*255.0f);
		//store modes here
		int mode;
		//get blend mode
		glGetIntegerv(GL_BLEND_DST, &mode);
		//following syntax seems better than if-else every time
		s.blendMode = (mode == GL_ONE) ? BLEND_ADDITIVE : BLEND_NORMAL;
		//get color mode
		glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &mode);
		s.colorMode = (mode == GL_MODULATE) ? COLOR_MODULATE : COLOR_NORMAL;
		//get the line width (directly to corresponding variable)
		glGetFloatv(GL_LINE_WIDTH, &s.lineWidth);
		//get line style
		s.lineStyle = (glIsEnabled(GL_LINE_SMOOTH) == GL_TRUE) ? LINE_SMOOTH : LINE_ROUGH;
		//get line stipple
		s.stipple = (glIsEnabled(GL_LINE_SMOOTH) == GL_TRUE) ? true : false;
		if (s.stipple)
		{
			//get the stipple repeat
			glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &s.stippleRepeat);
			//get the stipple pattern
			glGetIntegerv(GL_LINE_STIPPLE_PATTERN, &s.stipplePattern);
		}
		//get the point size
		glGetFloatv(GL_POINT_SIZE, &s.pointSize);
		//get point style
		s.pointStyle = (glIsEnabled(GL_POINT_SMOOTH) == GL_TRUE) ? POINT_SMOOTH : POINT_ROUGH;
		//get scissor status
		s.scissor = (glIsEnabled(GL_SCISSOR_TEST) == GL_TRUE) ? true : false;
		//do we have scissor, if so, store the box
		if (s.scissor)
			glGetIntegerv(GL_SCISSOR_BOX, s.scissorBox);
		return s;
	}

	void Graphics::restoreState(const DisplayState & s)
	{
		setColor(s.color[0], s.color[1], s.color[2], s.color[3]);
		setBackgroundColor(s.backgroundColor[0], s.backgroundColor[1], s.backgroundColor[2]);
		setBlendMode(s.blendMode);
		setColorMode(s.colorMode);
		setLine(s.lineWidth, s.lineStyle);
		if (s.stipple)
			setLineStipple(s.stipplePattern, s.stippleRepeat);
		else
			setLineStipple();
		setPoint(s.pointSize, s.pointStyle);
		if (s.scissor)
			setScissor(s.scissorBox[0], s.scissorBox[1], s.scissorBox[2], s.scissorBox[3]);
		else
			setScissor();
	}

	bool Graphics::setMode(int width, int height, bool fullscreen, bool vsync, int fsaa)
	{
		// This operation destroys the OpenGL context, so
		// we must save the state.
		DisplayState tempState;
		if (isCreated())
			tempState = saveState();

		// Unlad all volatile objects. These must be reloaded after
		// the display mode change.
		Volatile::unloadAll();

		// Get caption.

		// Special case for fullscreen -> windowed. Windows XP did not
		// work well with "normal" display mode change in this case. 
		// The application window does leave fullscreen, but the desktop
		// resolution does not revert to the correct one. Restarting the
		// SDL video subsystem does the trick, though.
		if( currentMode.fullscreen && !fullscreen )
		{
			// Restart.
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
			{
				std::cout << "Could not init SDL_VIDEO: " << SDL_GetError() << std::endl;
				return false;
			}
		}

		// Set caption.

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
			GLint buffers;
			GLint samples;

			glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & buffers ) ;
			glGetIntegerv( GL_SAMPLES_ARB, & samples ) ;

			// Don't fail because of this, but issue a warning.
			if ( ! buffers || (samples != fsaa))
				std::cerr << "Warning, quality setting failed! (Result: buffers: " << buffers << ", samples: " << samples << std::endl;
		}

		// Okay, setup OpenGL.

		// Enable blending
		glEnable(GL_BLEND);

		// "Normal" blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable line/point smoothing.
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

		// TODO:
		//reset();

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

		// Set the new display mode as the current display mode.
		currentMode.width = width;
		currentMode.height = height;
		currentMode.colorDepth = 32;
		currentMode.fsaa = fsaa;
		currentMode.fullscreen = fullscreen;
		currentMode.vsync = vsync;

		// Reload all volatile objects.
		if(!Volatile::loadAll())
			std::cerr << "Could not reload all volatile objects." << std::endl;

		// Restore the display state.
		restoreState(tempState);

		return true;
	}

	bool Graphics::toggleFullscreen()
	{
		// Try to do the change.
		if(!setMode(currentMode.width, 
			currentMode.height, 
			!currentMode.fullscreen, 
			currentMode.vsync, 
			currentMode.fsaa))
			return false;
		currentMode.fullscreen = !currentMode.fullscreen;
		return true;
	}


	void Graphics::reset()
	{
		DisplayState s;
		restoreState(s);
	}

	void Graphics::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void Graphics::present()
	{
		SDL_GL_SwapBuffers();
	}

	void Graphics::setCaption(const char * caption)
	{
		SDL_WM_SetCaption(caption, 0);
	}

	int Graphics::getCaption(lua_State * L)
	{
		char * title = 0;
		SDL_WM_GetCaption(&title, 0);
		lua_pushstring(L, title);
		return 1;
	}

	int Graphics::getWidth()
	{
		return currentMode.width;
	}

	int Graphics::getHeight()
	{
		return currentMode.height;
	}

	bool Graphics::isCreated()
	{
		return (currentMode.width > 0) || (currentMode.height > 0);
	}

	int Graphics::getModes(lua_State * L)
	{
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

	void Graphics::setScissor(int x, int y, int width, int height)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, getHeight() - (y + height), width, height); // Compensates for the fact that our y-coordinate is reverse of OpenGLs.
	}

	void Graphics::setScissor()
	{
		glDisable(GL_SCISSOR_TEST);
	}

	int Graphics::getScissor(lua_State * L)
	{
		if(glIsEnabled(GL_SCISSOR_TEST) == GL_FALSE)
			return 0;

		GLint scissor[4];
		glGetIntegerv(GL_SCISSOR_BOX, scissor);

		lua_pushnumber(L, scissor[0]);
		lua_pushnumber(L, getHeight() - (scissor[1] + scissor[3])); // Compensates for the fact that our y-coordinate is reverse of OpenGLs.
		lua_pushnumber(L, scissor[2]);
		lua_pushnumber(L, scissor[3]);

		return 4;
	}

	Image * Graphics::newImage(love::image::ImageData * data)
	{
		// Create the image.
		Image * image = new Image(data);

		if(!image->load())
		{
			image->release();
			return 0;
		}

		return image;
	}
	
	Frame * Graphics::newFrame(Image *image, int x, int y, int w, int h)
	{
		return new Frame(image, x, y, w, h);
	}

	Color * Graphics::newColor(int r, int g, int b, int a)
	{
		return new Color(r, g, b, a);
	}

	Font * Graphics::newFont(love::filesystem::File * file, int size)
	{
		Font * font = new TrueTypeFont(file, size);

		// Load it and check for errors.
		if(!font->load())
		{
			delete font;
			return 0;
		}

		return font;
	}

	Font * Graphics::newImageFont(Image * image, const char * glyphs, float spacing)
	{
		Font * font = new ImageFont(image, std::string(glyphs));

		// Load it and check for errors.
		if(!font->load())
		{
			delete font;
			return 0;
		}

		return font;
	}

	Animation * Graphics::newAnimation(Image * image)
	{
		return new Animation(image);
	}

	Animation * Graphics::newAnimation(Image * image, float fw, float fh, float delay, int num)
	{
		return new Animation(image, fw, fh, delay, num);
	}

	SpriteBatch * Graphics::newSpriteBatch(Image * image, int size, int usage)
	{
		return new SpriteBatch(image, size, usage);
	}

	VertexBuffer * Graphics::newVertexBuffer(Image * image, int size, int type, int usage)
	{
		return new VertexBuffer(image, size, type, usage);
	}

	void Graphics::setColor( int r, int g, int b, int a)
	{
		glColor4ub(r, g, b, a);
	}

	void Graphics::setColor( Color * color )
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	Color * Graphics::getColor()
	{
		float c[4];
		glGetFloatv(GL_CURRENT_COLOR, c);
		return new Color((int)(255.0f*c[0]), (int)(255.0f*c[1]), (int)(255.0f*c[2]), (int)(255.0f*c[3]));
	}

	void Graphics::setBackgroundColor( int r, int g, int b )
	{
		glClearColor( (float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
	}

	void Graphics::setBackgroundColor( Color * color )
	{
		glClearColor( (float)color->getRed()/255.0f, (float)color->getGreen()/255.0f, (float)color->getBlue()/255.0f, 1.0f);
	}

	Color * Graphics::getBackgroundColor()
	{
		float c[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, c);
		return new Color((int)(255.0f*c[0]), (int)(255.0f*c[1]), (int)(255.0f*c[2]), (int)(255.0f*c[3]));
	}

	void Graphics::setFont( Font * font )
	{
		if(currentFont != 0)
			currentFont->release();

		currentFont = font;

		if(font != 0)
			currentFont->retain();
	}

	void Graphics::setFont( love::filesystem::File * file, int size )
	{
		if(currentFont != 0)
			currentFont->release();

		currentFont = new TrueTypeFont(file, size);
		currentFont->load();
	}

	Font * Graphics::getFont()
	{
		return currentFont;
	}

	void Graphics::setBlendMode( int mode )
	{
		if(mode == BLEND_ADDITIVE)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else // mode == BLEND_NORMAL
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Graphics::setColorMode ( int mode )
	{
		if(mode == COLOR_MODULATE)
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		else // mode = COLOR_NORMAL
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	
	int Graphics::getBlendMode()
	{
		GLint dst, src;
		glGetIntegerv(GL_BLEND_DST, &dst);
		glGetIntegerv(GL_BLEND_SRC, &src);

		if(src == GL_SRC_ALPHA && dst == GL_ONE)
			return BLEND_ADDITIVE;
		else // src == GL_SRC_ALPHA && dst == GL_ONE_MINUS_SRC_ALPHA
			return BLEND_NORMAL;
	}

	int Graphics::getColorMode()
	{
		GLint mode;
		glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &mode);

		if(mode == GL_MODULATE)
			return COLOR_MODULATE;
		else // // mode == GL_REPLACE
			return COLOR_NORMAL;
	}

	void Graphics::setLineWidth( float width )
	{
		glLineWidth(width);
	}

	void Graphics::setLineStyle( int style )
	{
		if(style == LINE_ROUGH)
			glDisable (GL_LINE_SMOOTH);
		else // type == LINE_SMOOTH
		{
			glEnable (GL_LINE_SMOOTH);
			glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
		}		
	}

	void Graphics::setLine( float width, int style )
	{
		glLineWidth(width);

		if(style == 0)
			return;

		if(style == LINE_ROUGH)
			glDisable (GL_LINE_SMOOTH);
		else // type == LINE_SMOOTH
		{
			glEnable (GL_LINE_SMOOTH);
			glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
		}
	}

	void Graphics::setLineStipple()
	{
		glDisable(GL_LINE_STIPPLE);
	}

	void Graphics::setLineStipple(unsigned short pattern, int repeat)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple((GLint)repeat, (GLshort)pattern);
	}

	float Graphics::getLineWidth()
	{
		float w;
		glGetFloatv(GL_LINE_WIDTH, &w);
		return w;
	}

	int Graphics::getLineStyle()
	{
		if(glIsEnabled(GL_LINE_SMOOTH) == GL_TRUE)
			return LINE_SMOOTH;
		else
			return LINE_ROUGH;
	}

	int Graphics::getLineStipple(lua_State * L)
	{
		if(glIsEnabled(GL_LINE_STIPPLE) == GL_FALSE)
			return 0;
	
		GLint factor, pattern;
		glGetIntegerv(GL_LINE_STIPPLE_PATTERN, &pattern);
		glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &factor);
		lua_pushinteger(L, pattern);
		lua_pushinteger(L, factor);
		return 2;
	}

	void Graphics::setPointSize( float size )
	{
		glPointSize((GLfloat)size);
	}

	void Graphics::setPointStyle( int style )
	{
		if( style == POINT_SMOOTH )
			glEnable(GL_POINT_SMOOTH);
		else // love::POINT_ROUGH
			glDisable(GL_POINT_SMOOTH);
	}

	void Graphics::setPoint( float size, int style )
	{
		if( style == POINT_SMOOTH )
			glEnable(GL_POINT_SMOOTH);
		else // POINT_ROUGH
			glDisable(GL_POINT_SMOOTH);

		glPointSize((GLfloat)size);
	}

	float Graphics::getPointSize()
	{
		GLfloat size;
		glGetFloatv(GL_POINT_SIZE, &size);
		return (float)size;
	}

	int Graphics::getPointStyle()
	{
		if(glIsEnabled(GL_POINT_SMOOTH) == GL_TRUE)
			return POINT_SMOOTH;
		else
			return POINT_ROUGH;
	}

	int Graphics::getMaxPointSize()
	{
		GLint max;
		glGetIntegerv(GL_POINT_SIZE_MAX, &max);
		return (int)max;
	}

	void Graphics::print( const char * str, float x, float y )
	{
		if(currentFont != 0)
		{
			std::string text(str);

			if(text.find("\n") == std::string::npos)
				currentFont->print(text, x, y);
			else
			{
				int lines = 0;
				text = "";
				
				for(unsigned int i = 0; i < strlen(str); i++)
				{
					if(str[i] == '\n')
					{
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
						text = "";
						lines++;
					}
					else
						text += str[i];
				}
				
				if(text != "") // Print the last text (if applicable).
					currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
			}
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, 1, 1);
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle, float s)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, s, s);
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle, float sx, float sy)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, sx, sy);
		}
	}

	void Graphics::printf( const char * str, float x, float y, float wrap, int align)
	{
		if(currentFont != 0)
		{
			std::string text = "";
			float width = 0;
			float lines = 0;
			
			for(unsigned int i = 0; i < strlen(str); i++)
			{
				if(str[i] == '\n')
				{
					switch(align)
					{
						case ALIGN_LEFT:
							currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;
							
						case ALIGN_RIGHT:
							currentFont->print(text, (x + (wrap - currentFont->getWidth(text))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;
							
						case ALIGN_CENTER:
							currentFont->print(text, ceil(x + ((wrap - currentFont->getWidth(text)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
							break;
							
						default: // A copy of the left align code. Kept separate in case an error message is wanted.
							currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;
					}

					text = "";
					width = 0;
					lines++;
				}
				else
				{
					width += currentFont->getWidth(str[i]);
					
					if(width > wrap && text.find(" ") != std::string::npos) // If there doesn't exist a space, then ignore the wrap limit.
					{						
						// Seek back to the nearest space and print that.
						unsigned int space = (unsigned int)text.find_last_of(' ');
						std::string temp = text.substr(0, space);
						
						switch(align)
						{
							case ALIGN_LEFT:
								currentFont->print(temp, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;
							
							case ALIGN_RIGHT:
								currentFont->print(temp, (x + (wrap - currentFont->getWidth(temp))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;
							
							case ALIGN_CENTER:
								currentFont->print(temp, ceil(x + ((wrap - currentFont->getWidth(temp)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
								break;
							
							default: // A copy of the left align code. Kept separate in case an error message is wanted.
								currentFont->print(temp, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;
						}	
						
						text = text.substr(space + 1);
						width = currentFont->getWidth(text);
						lines++;
					}
					
					text += str[i];
				}
			} // for

			if(text != "") // Print the last text (if applicable).
			{
				switch(align)
				{
					case ALIGN_LEFT:
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
						break;
							
					case ALIGN_RIGHT:
						currentFont->print(text, (x + (wrap - currentFont->getWidth(text))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
						break;
							
					case ALIGN_CENTER:
						currentFont->print(text, ceil(x + ((wrap - currentFont->getWidth(text)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
						break;
							
					default: // A copy of the left align code. Kept separate in case an error message is wanted.
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
						break;
				}
			} 
		}
	}

	/**
	* Primitives
	**/

	void Graphics::point( float x, float y )
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POINTS);
			glVertex2f(x, y);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	void Graphics::line( float x1, float y1, float x2, float y2 )
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

	void Graphics::triangle( int type, float x1, float y1, float x2, float y2, float x3, float y3 )
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		switch(type)
		{
		case love::DRAW_LINE:
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
		glEnable(GL_CULL_FACE);
	}

	void Graphics::rectangle( int type, float x, float y, float w, float h )
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		switch(type)
		{
		case love::DRAW_LINE:
			glBegin(GL_LINE_LOOP);
				glVertex2f(x, y);				
				glVertex2f(x, y+h);
				glVertex2f(x+w, y+h);
				glVertex2f(x+w, y);
			glEnd();
			break;

		default:
		case love::DRAW_FILL:
			glBegin(GL_QUADS);
				glVertex2f(x, y);				
				glVertex2f(x, y+h);
				glVertex2f(x+w, y+h);
				glVertex2f(x+w, y);
			glEnd();
			break;
		}

		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}

	void Graphics::quad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 )
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();

		switch(type)
		{
		case love::DRAW_LINE:
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
		glEnable(GL_CULL_FACE);
	}

	void Graphics::circle( int type, float x, float y, float radius, int points )
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

	int Graphics::polygon( lua_State * L )
	{
		// Get number of params.
		int n = lua_gettop(L);

		// Need at least two params.
		if( n < 2 )
			return luaL_error(L, "Error: function needs at least two parameters.");

		// The first one MUST be a number.
		if( !lua_isnumber(L, 1) )
			return luaL_error(L, "Error: first parameter must be a number.");

		// Get rendering mode. (line/fill)
		int mode = (int)lua_tonumber(L, 1);

		// Get the type of the second argument.
		int luatype = lua_type(L, 2);

		// Perform additional type checking.
		switch(luatype)
		{
		case LUA_TNUMBER:
			if( n-1 < 6 ) return luaL_error(L, "Error: function requires at least 3 vertices.");
			if( ((n-1)%2) != 0 ) return luaL_error(L, "Error: number of vertices must be a multiple of two.");
			break;
		case LUA_TTABLE:
			if( (lua_objlen(L, 2)%2) != 0 ) return luaL_error(L, "Error: number of vertices must be a multiple of two.");
			break;
		default:
			return luaL_error(L, "Error: number type or table expected.");
		}

		
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);

		glBegin((mode==love::DRAW_LINE) ? GL_LINE_LOOP : GL_POLYGON);

		switch(luatype)
		{
		case LUA_TNUMBER:
			for(int i = 2; i<n; i+=2)
				glVertex2f((GLfloat)lua_tonumber(L, i), (GLfloat)lua_tonumber(L, i+1));
			break;
		case LUA_TTABLE:
			lua_pushnil(L); 
			while (true)
			{
				if(lua_next(L, 2) == 0) break;
				GLfloat x = (GLfloat)lua_tonumber(L, -1);
				lua_pop(L, 1); // pop value
				if(lua_next(L, 2) == 0) break;
				GLfloat y = (GLfloat)lua_tonumber(L, -1);
				lua_pop(L, 1); // pop value
				glVertex2f(x, y);
			}
			break;
		}

		glEnd();

		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);

		return 0;
	}

	int Graphics::polygong( lua_State * L )
	{
		// Get number of params.
		int n = lua_gettop(L);

		// Need at least two params.
		if( n < 2 )
			return luaL_error(L, "Error: function needs at least two parameters.");

		// The first one MUST be a number.
		if( !lua_isnumber(L, 1) )
			return luaL_error(L, "Error: first parameter must be a number.");

		int vertc = 0, colorc = 0;

		if( n == 3 )
		{
			if((!lua_istable(L, 2) || !lua_istable(L, 3))) 
				return luaL_error(L, "Error: two tables expected.");
			vertc = (int)lua_objlen(L, 2);
			colorc = (int)lua_objlen(L, 3);
			if( (vertc <= 0 || colorc <= 0)) 
				return luaL_error(L, "Error: empty table.");
		}

		// Get rendering mode. (line/fill)
		int mode = (int)lua_tonumber(L, 1);
		GLenum glmode = (mode==love::DRAW_LINE) ? GL_LINE_LOOP : GL_POLYGON;

		// Get the type of the second argument.
		int luatype = lua_type(L, 2);

		if(!(luatype == LUA_TTABLE || luatype == LUA_TNUMBER))
			return luaL_error(L, "Error: expected number or table values.");

		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);

		switch(luatype)
		{
		case LUA_TTABLE:

			if( n == 2 )
			{
				glBegin(glmode);
				lua_pushnil(L);
				while(true)
				{
					if(lua_next(L, 2) == 0) break;
					GLfloat x = (GLfloat)lua_tonumber(L, -1);
					lua_pop(L, 1);
					if(lua_next(L, 2) == 0) break;
					GLfloat y = (GLfloat)lua_tonumber(L, -1);
					lua_pop(L, 1);
					if(lua_next(L, 2) == 0) break;
					GLubyte r = (GLubyte)lua_tonumber(L, -1);
					lua_pop(L, 1);
					if(lua_next(L, 2) == 0) break;
					GLubyte g = (GLubyte)lua_tonumber(L, -1);
					lua_pop(L, 1);
					if(lua_next(L, 2) == 0) break;
					GLubyte b = (GLubyte)lua_tonumber(L, -1);
					lua_pop(L, 1);
					if(lua_next(L, 2) == 0) break;
					GLubyte a = (GLubyte)lua_tonumber(L, -1);
					lua_pop(L, 1);
					glColor4ub(r, g, b, a);
					glVertex2f(x, y);
				}
				glEnd();
			}
			else if(n == 3)
			{
				// Allocate memory.
				GLfloat * verts = new GLfloat[vertc];
				GLubyte * colors = new GLubyte[colorc];
				int verti = 0, colori = 0;

				// Get verts.
				lua_pushnil(L);
				while(lua_next(L, 2))
				{
					verts[verti++] = (GLfloat)lua_tonumber(L, -1);
					lua_pop(L, 1);
				}

				// Get colors.
				lua_pushnil(L);
				while(lua_next(L, 3))
				{
					colors[colori++] = (GLubyte)lua_tonumber(L, -1);
					lua_pop(L, 1);
				}

				glEnable(GL_VERTEX_ARRAY);
				glEnable(GL_COLOR_ARRAY);
				glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
				glVertexPointer(2, GL_FLOAT, 0, verts);
				glDrawArrays(glmode, 0, (GLint)(vertc/2));
				glDisable(GL_VERTEX_ARRAY);
				glDisable(GL_COLOR_ARRAY);
				delete [] verts;
				delete [] colors;
			}	

			break;
		case LUA_TNUMBER:
			// Assume params to be packed like this: x, y, r, g, b, a, x, y, r, ...
			glBegin(glmode);
			for(int i = 2; i < (n-1); i+=6)
			{
				glColor4ub((GLubyte)lua_tonumber(L, i+2), (GLubyte)lua_tonumber(L, i+3), (GLubyte)lua_tonumber(L, i+4), (GLubyte)lua_tonumber(L, i+5));
				glVertex2f((GLfloat)lua_tonumber(L, i), (GLfloat)lua_tonumber(L, i+1));
			}				
			glEnd();
			break;
		}

		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glPopAttrib();


		return 0;
	}

	bool Graphics::screenshot(love::filesystem::File * file)
	{
		// TODO: update this.
		/*
		int w = getWidth();
		int h = getHeight();

		// Declare some storage.
		GLubyte * pixels = new GLubyte[3*w*h];
		GLubyte * screenshot = new GLubyte[3*w*h];
		ILuint image;

		// Read the pixels on the screen.
		glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

		ilGenImages(1, &image);
		ilBindImage(image);
		ilTexImage(w, h, 1, 3, IL_RGB, IL_UNSIGNED_BYTE, (ILvoid*)pixels);

		delete [] pixels;

		// Create the image.
		ilSaveL(IL_BMP, screenshot, 3*w*h);

		bool success = true;

		if(file->open())
		{
			if(!file->write((const char *)screenshot, 3*w*h))
				success = false;
			file->close();
		}
		else
			success = false;

		delete [] screenshot;
		ilDeleteImages(1, &image);
		*/

		return false;
	}

	void Graphics::push()
	{
		glPushMatrix();
	}

	void Graphics::pop()
	{
		glPopMatrix();
	}

	void Graphics::rotate(float r)
	{
		glRotatef(r, 0, 0, 1);
	}

	void Graphics::scale(float x, float y)
	{
		glScalef(x, y, 1);
	}

	void Graphics::translate(float x, float y)
	{
		glTranslatef(x, y, 0);
	}

	void Graphics::drawTest(Image * image, float x, float y, float a, float sx, float sy, float ox, float oy)
	{
		image->bind();

		// Buffer for transforming the image.
		vertex buf[4];

		Matrix t;
		t.translate(x, y);
		t.rotate(a);
		t.scale(sx, sy);
		t.translate(ox, oy);
		t.transform(buf, image->getVertices(), 4);

		const vertex * vertices = image->getVertices();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&buf[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&vertices[0].s);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

} // opengl
} // graphics
} // love
