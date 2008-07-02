/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This is the love_opengl graphics module. It is probably one of
* the most extensive modules, and has the following dependencies:
* - Lua (of course).
* - SDL (window setup).
* - OpenGL (graphics).
* - FreeType (font rasterization).
* - DevIL (image decoding).
* 
* This module also depends on love.filesystem to load
* image and font files.
**/

#ifndef LOVE_MOD_OPENGL_H
#define LOVE_MOD_OPENGL_H

// LOVE
#include <love/mod.h>
#include <love/File.h>

// Module files.
#include "Color.h"
#include "Image.h"
#include "Animation.h"
#include "TrueTypeFont.h"
#include "ImageFont.h"
#include "ParticleSystem.h"
#include "PointParticleSystem.h"
#include "Volatile.h"

/// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_opengl
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

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
	* Draws the console on screen.
	**/
	void draw_console();

	/**
	* Prints a message in the console.
	**/
	void print(const char * str);

	/**
	* Sets the windows caption.
	**/
	void setCaption(const char * caption);

	/**
	* True if some display mode is set.
	**/
	bool isCreated();

	/**
	* Checks if some feature is present.
	**/
	bool feature(int f);

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
	* Creates a new Color object.
	**/
	pColor newColor( int r, int g, int b, int a = 255 );

	/**
	* Creates an Image object from one of the built-in ones.
	* (Just for internal use).
	**/
	pImage newImage(int image);	

	/**
	* Creates an Image object.
	**/
	pImage newImage(const char * filename);	

	/**
	* Creates an Image object with padding and/or optimization.
	**/
	pImage newImage(const char * filename, int mode);	

	/**
	* Creates an Image object. (This is not exposed in Lua).
	**/
	pImage newImage(love::pFile file);

	/**
	* Creates an Image object with padding and/or optimization.
	**/
	pImage newImage(love::pFile file, int mode);

	/**
	* Creates a Font object.
	**/
	pFont newFont(const char * filename, int size);

	/**
	* Creates a Font object (using default fonts).
	**/
	pFont newFont(int f, int size);

	/**
	* Creates an ImageFont object.
	**/
	pFont newImageFont(const char * filename, const char * glyphs, float spacing = 1);

	/**
	* Creates an Animation object with no frames.
	**/
	pAnimation newAnimation(pImage image);

	/**
	* Creates an Animation object with generated frames in a grid.
	**/
	pAnimation newAnimation(pImage image, float fw, float fh, float delay, int num = 0);

	/**
	* Creates an Animation object with no frames.
	**/
	pAnimation newAnimation(const char * filename);

	/**
	* Creates an Animation object with generated frames in a grid.
	**/
	pAnimation newAnimation(const char * filename, float fw, float fh, float delay, int num = 0);

	/**
	* Creates a ParticleSystem object with the specified buffer size and using the specified sprite.
	**/
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size);

	/**
	* Creates a PointParticleSystem object with the specified buffer size and sprite.
	* @param mode This should be love::POINT_SPRITE.
	**/
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size, int mode);

	/**
	* Gets the width of the current display mode.
	**/
	int getWidth();

	/**
	* Gets the height of the current display mode.
	**/
	int getHeight();

	/**
	* Scissor defines a box such that everything outside that box
	* is discared and not drawn. Scissoring is automatically 
	* enabled.
	* @param x The x-coordinate of the top-left corner.
	* @param y The y-coordinate of the top-left corner.
	* @param width The width of the box.
	* @param height The height of the box.
	**/
	void setScissor(int x, int y, int width, int height);

	/**
	* Gets the current display caption.
	**/
	std::string getCaption();

	/**
	* Sets the foreground color.
	**/
	void setColor(const pColor & color);

	/**
	* Sets the foreground color.
	**/
	void setColor( int r, int g, int b, int a = 255);

	/**
	* Gets current color.
	**/
	pColor getColor();

	/**
	* Sets the background Color. 
	**/
	void setBackgroundColor( const pColor & color );

	/**
	* Sets the background Color. 
	**/
	void setBackgroundColor( int r, int g, int b );

	/**
	* Gets the current background color.
	**/
	pColor getBackgroundColor();

	/**
	* Sets the current font.
	**/
	void setFont( pFont font );

	/**
	* Gets the current Font.
	**/
	pFont getFont();

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
	* Sets the type of line used to draw primitives.
	**/
	void setLine( float width, int type = 0 );

	/**
	* Draw text on screen at the specified coordiantes (automatically breaks \n characters).
	*
	* @param str A string of text.
	* @param x The x-coordiante.
	* @param y The y-coordiante.
	**/
	void draw( const char * str, float x, float y );

	/**
	* Draws text at the specified coordinates, with rotation.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	**/
	void draw( const char * str, float x, float y , float angle );

	/**
	* Draws text at the specified coordinates, with rotation and 
	* scaling.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param s The scale factor. (1 = normal).
	**/
	void draw( const char * str, float x, float y , float angle, float s );

	/**
	* Draws text at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	void draw( const char * str, float x, float y , float angle, float sx, float sy);

	/**
	* Draw formatted text on screen at the specified coordinates.
	*
	* @param str A string of text.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param wrap The maximum width of the text area.
	* @param align Where to align the text.
	**/
	void drawf( const char * str, float x, float y, float wrap, int align = 0 );

	/**
	* Draws an Image at the specified coordinates.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	**/
	void draw( const pImage & sprite, float x, float y );

	/**
	* Draws an Image at the specified coordinates, with rotation.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	**/
	void draw( const pImage & sprite, float x, float y , float angle);

	/**
	* Draws an Image at the specified coordinates, with rotation and 
	* scaling.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param s The scale factor. (1 = normal).
	**/
	void draw( const pImage & sprite, float x, float y , float angle, float s);

	/**
	* Draws an Image at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	void draw( const pImage & sprite, float x, float y , float angle, float sx, float sy);

	/**
	* Draws an Amage at the specified coordinates.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	**/
	void draw( const pAnimation & sprite, float x, float y );

	/**
	* Draws an Amage at the specified coordinates, with rotation.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	**/
	void draw( const pAnimation & sprite, float x, float y, float angle);

	/**
	* Draws an Animation at the specified coordinates, with rotation and 
	* scaling.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param s The scale factor. (1 = normal).
	**/
	void draw( const pAnimation & sprite, float x, float y, float angle, float s);
	
	/**
	* Draws an Animation at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	void draw( const pAnimation & sprite, float x, float y, float angle, float sx, float sy);

	/**
	* Draws a ParticleSystem at the specified coordinates.
	* @param system The particle system.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	**/
	void draw( const pParticleSystem & system, float x, float y);

	/**
	* Draws the section (cx, cy, w, h) of an Image at position (x, y).
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param cx The x-position of the image section. (top-left).
	* @param cy The y-position of the image section. (top-left).
	* @param w The width of the image section.
	* @param h The height of the image section.
	**/
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h );

	/**
	* Draws the section (cx, cy, w, h) of an Image at position (x, y), 
	* with rotation.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param cx The x-position of the image section. (top-left).
	* @param cy The y-position of the image section. (top-left).
	* @param w The width of the image section.
	* @param h The height of the image section.
	* @param angle The amount to rotate the image section.
	**/
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle);
	
	/**
	* Draws the section (cx, cy, w, h) of an Image at position (x, y), 
	* with rotation and scaling.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param cx The x-position of the image section. (top-left).
	* @param cy The y-position of the image section. (top-left).
	* @param w The width of the image section.
	* @param h The height of the image section.
	* @param angle The amount to rotate the image section.
	* @param s The scale factor. (1 = normal).
	**/
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float s);

	/**
	* Draws the section (cx, cy, w, h) of an Image at position (x, y), 
	* with rotation and scaling along each axis.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param cx The x-position of the image section. (top-left).
	* @param cy The y-position of the image section. (top-left).
	* @param w The width of the image section.
	* @param h The height of the image section.
	* @param angle The amount to rotate the image section.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	**/
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy);
	
	/**
	* Draws the section (cx, cy, w, h) of an Image at position (x, y), 
	* with rotation, scaling, and a different center point.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param cx The x-position of the image section. (top-left).
	* @param cy The y-position of the image section. (top-left).
	* @param w The width of the image section.
	* @param h The height of the image section.
	* @param angle The amount to rotate the image section.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	* @param ox The x-coordinate of the center.
	* @param oy The y-coordinate of the center.
	**/
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy, float ox, float oy);

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

} // love_opengl

#endif // LOVE_MOD_OPENGL_H
