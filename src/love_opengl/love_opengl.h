/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_MODULE_OPENGL_H
#define LOVE_MODULE_OPENGL_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/filesystem/File.h"
#include "../liblove/luax.h"
#include "../liblove/types.h"

// Module
#include "Image.h"
#include "Animation.h"
#include "Color.h"
#include "TrueTypeFont.h"
#include "ParticleSystem.h"
#include "SpriteBatch.h"
#include "VertexBuffer.h"

namespace love
{
namespace opengl
{
	// Standard function.
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* Checks whether a display mode is supported or not. Note
	* that fullscreen is assumed, because windowed modes are
	* generally supported regardless of size.
	* @param width The window width.
	* @param height The window height.
	**/
	bool checkMode(int width, int height, bool fullscreen);

	/**
	* Sets the current display mode.
	* @param width The window width.
	* @param height The window height.
	* @param fullscreen True if fullscreen, false otherwise.
	* @param vsync True if we should wait for vsync, false otherwise.
	* @param fsaa Number of full scene anti-aliasing buffer, or 0 for disabled.
	**/
	bool setMode(int width, int height, bool fullscreen, bool vsync, int fsaa);

	/**
	* Toggles fullscreen. Note that this also needs to reload the
	* entire OpenGL context.
	**/
	bool toggleFullscreen();

	/**
	* Resets the current color, background color,
	* line style, and so forth. (This will be called
	* when the game reloads.
	**/
	void reset();
		
	/**
	* Clears the screen.
	**/
	void clear();

	/**
	* Flips buffers. (Rendered geometry is 
	* presented on screen).
	**/
	void present();

	/**
	* Sets the windows caption.
	**/
	void setCaption(const char * caption);

	int getCaption(lua_State * L);

	/**
	* Gets the width of the current display mode.
	**/
	int getWidth();

	/**
	* Gets the height of the current display mode.
	**/
	int getHeight();

	/**
	* True if some display mode is set.
	**/
	bool isCreated();

	/**
	* This native Lua function gets available modes
	* from SDL and returns them as a table on the following format:
	* 
	* { 
	*   { width = 800, height = 600 }, 
	*   { width = 1024, height = 768 },
	*   ...
	* }
	* 
	* Only fullscreen modes are returned here, as all
	* window sizes are supported (normally).
	**/
	int getModes(lua_State * L);

	/**
	* Scissor defines a box such that everything outside that box is discared and not drawn.
	* Scissoring is automatically enabled.
	* @param x The x-coordinate of the top-left corner.
	* @param y The y-coordinate of the top-left corner.
	* @param width The width of the box.
	* @param height The height of the box.
	**/
	void setScissor(int x, int y, int width, int height);

	/**
	* Clears any scissor that has been created.
	**/
	void setScissor();

	/**
	* This native Lua function gets the current scissor box in the order of:
	* x, y, width, height
	**/
	int getScissor(lua_State * L);

	/**
	* Creates a new Color object.
	**/
	Color * newColor( int r, int g, int b, int a );

	/**
	* Creates an Image object with padding and/or optimization.
	**/
	Image * newImage(File * file);
	Image * newImage(ImageData * data);

	/**
	* Creates a Font object.
	**/
	Font * newFont(File * file, int size = 12);

	/**
	* Creates an ImageFont object.
	**/
	//pFont newImageFont(File * file, const char * glyphs, float spacing = 1);
	
	/**
	* Creates an Animation object with no frames.
	**/
	//Animation * newAnimation(Image * image);

	/**
	* Creates an Animation object with generated frames in a grid.
	**/
	//Animation * newAnimation(Image * image, float fw, float fh, float delay, int num = 0);

	/**
	* Creates a ParticleSystem object with the specified buffer size and using the specified sprite.
	**/
	//pParticleSystem newParticleSystem(Image * image, unsigned int size);

	/**
	* Creates a PointParticleSystem object with the specified buffer size and sprite.
	* @param mode This should be love::POINT_SPRITE.
	**/
	//pParticleSystem newParticleSystem(Image * image, unsigned int size, int mode);

	SpriteBatch * newSpriteBatch(Image * image, int size, int usage);
	VertexBuffer * newVertexBuffer(Image * image, int size, int type, int usage);
		
	/**
	* Sets the foreground color.
	**/
	void setColor(Color * color);

	/**
	* Sets the foreground color.
	**/
	void setColor( int r, int g, int b, int a = 255);

	/**
	* Gets current color.
	**/
	Color * getColor();

	/**
	* Sets the background Color. 
	**/
	void setBackgroundColor( Color * color );

	/**
	* Sets the background Color. 
	**/
	void setBackgroundColor( int r, int g, int b );

	/**
	* Gets the current background color.
	**/
	Color * getBackgroundColor();

	/**
	* Sets the current font.
	* @parm font A Font object.
	**/
	void setFont( Font * font );

	/**
	* Sets a default font. The font is
	* loaded and sent to the GPU every time this is called, 
	* so no over-using.
	* @param file File from which to load the font.
	* @param size The size of the font.
	**/
	void setFont( File * file, int size = 12);

	/**
	* Gets the current Font, or nil if none.
	**/
	Font * getFont();

	/**
	* Sets the current blend mode.
	**/
	void setBlendMode( int mode );

	/**
	* Sets the current color mode.
	**/
	void setColorMode ( int mode );

	/**
	* Gets the current blend mode.
	**/
	int getBlendMode();

	/**
	* Gets the current color mode.
	**/
	int getColorMode();

	/**
	* Sets the line width.
	* @param width The new width of the line.
	**/
	void setLineWidth( float width );

	/**
	* Sets the line style.
	* @param style LINE_ROUGH or LINE_SMOOTH.
	**/
	void setLineStyle( int style );

	/**
	* Sets the type of line used to draw primitives.
	* A shorthand for setLineWidth and setLineStyle.
	**/
	void setLine( float width, int style = 0 );

	/**
	* Disables line stippling.
	**/
	void setLineStipple();

	/**
	* Sets a line stipple pattern.
	**/
	void setLineStipple(unsigned short pattern, int repeat = 1);

	/**
	* Gets the line width.
	**/
	float getLineWidth();

	/**
	* Gets the line style.
	**/
	int getLineStyle();

	/**
	* Gets the line stipple pattern and repeat factor.
	* @return pattern The stipplie bit-pattern.
	* @return repeat The reapeat factor.
	**/
	int getLineStipple(lua_State * L);

	/**
	* Sets the size of points.
	**/
	void setPointSize( float size );

	/**
	* Sets the style of points.
	* @param style POINT_SMOOTH or POINT_ROUGH.
	**/
	void setPointStyle( int style );

	/**
	* Shorthand for setPointSize and setPointStyle.
	**/
	void setPoint( float size, int style );

	/**
	* Gets the point size.
	**/
	float getPointSize();

	/**
	* Gets the point style.
	**/
	int getPointStyle();

	/**
	* Gets the maximum point size supported. 
	* This may vary from computer to computer.
	**/
	int getMaxPointSize();

	/**
	* Draw text on screen at the specified coordiantes (automatically breaks \n characters).
	*
	* @param str A string of text.
	* @param x The x-coordiante.
	* @param y The y-coordiante.
	**/
	void print( const char * str, float x, float y );

	/**
	* Draws text at the specified coordinates, with rotation.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	**/
	void print( const char * str, float x, float y , float angle );

	/**
	* Draws text at the specified coordinates, with rotation and 
	* scaling.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param s The scale factor. (1 = normal).
	**/
	void print( const char * str, float x, float y , float angle, float s );

	/**
	* Draws text at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	void print( const char * str, float x, float y , float angle, float sx, float sy);

	/**
	* Draw formatted text on screen at the specified coordinates.
	*
	* @param str A string of text.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param wrap The maximum width of the text area.
	* @param align Where to align the text.
	**/
	void printf( const char * str, float x, float y, float wrap, int align = 0 );

	/**
	* Draws an Image at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	//void draw(Drawable * drawable, float x, float y, float angle, float sx, float sy);

	/**
	* Draws a point at (x,y).
	* @param x Point along x-axis.
	* @param y Point along y-axis.
	**/
	void point( float x, float y );

	/**
	* Draws a line from (x1,y1) to (x2,y2).
	* @param x1 First x-coordinate.
	* @param y1 First y-coordinate.
	* @param x2 Second x-coordinate.
	* @param y2 Second y-coordinate.
	**/
	void line( float x1, float y1, float x2, float y2 );

	/**
	* Draws a triangle using the three coordinates passed.
	* @param type The type of drawing (line/filled).
	* @param x1 First x-coordinate.
	* @param y1 First y-coordinate.
	* @param x2 Second x-coordinate.
	* @param y2 Second y-coordinate.
	* @param x3 Third x-coordinate.
	* @param y3 Third y-coordinate.
	**/
	void triangle( int type, float x1, float y1, float x2, float y2, float x3, float y3 );

	/**
	* Draws a rectangle.
	* @param x Position along x-axis for top-left corner.
	* @param y Position along y-axis for top-left corner.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	**/
	void rectangle( int type, float x, float y, float w, float h );

	/**
	* Draws a quadrilateral using the four coordinates passed.
	* @param type The type of drawing (line/filled).
	* @param x1 First x-coordinate.
	* @param y1 First y-coordinate.
	* @param x2 Second x-coordinate.
	* @param y2 Second y-coordinate.
	* @param x3 Third x-coordinate.
	* @param y3 Third y-coordinate.
	* @param x4 Fourth x-coordinate.
	* @param y4 Fourth y-coordinate.
	**/
	void quad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 );

	/**
	* Draws a circle using the specified arguments.
	* @param type The type of drawing (line/filled).
	* @param x X-coordinate.
	* @param y Y-coordinate.
	* @param radius Radius of the circle.
	* @param points Amount of points to use to draw the circle.
	**/
	void circle( int type, float x, float y, float radius, int points = 10 );

	/**
	* Draws a polygon with an arbitrary number of vertices.
	* @param type The type of drawing (line/filled).
	* @param ... Vertex components (x1, y1, x2, y2, etc).
	**/
	int polygon( lua_State * L );

	/**
	* Creates a screenshot of the view and saves it to the default folder.
	* @param file The file to write the screenshot to.
	**/
	bool screenshot(File * file);

	void push();
	void pop();
	void rotate(float r);
	void scale(float x, float y = 1.0f);
	void translate(float x, float y);

	void drawTest(Image * image, float x, float y, float a, float sx, float sy, float ox, float oy);

} // opengl
} // love

#endif // LOVE_MODULE_OPENGL_H
