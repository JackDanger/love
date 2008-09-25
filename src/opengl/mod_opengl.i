%module mod_opengl

%{
#include <boost/shared_ptr.hpp>
#include "love_opengl.h"
using namespace love_opengl;
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%include Color.i

%include Font.i
%include Sprite.i
%include Image.i
%include Animation.i
%include ParticleSystem.i

namespace love_opengl
{
	bool feature(int f);

	// Display mode control.
	bool checkMode(int width, int height, bool fullscreen);
	bool setMode(int width, int height, bool fullscreen, bool vsync, int fsaa);
	bool toggleFullscreen();

	pColor newColor( int r, int g, int b, int a = 255 );

	pImage newImagev(void * ptr, int mode = love::IMAGE_NORMAL);
	pImage newImagei(int image);
	
	pFont newFontv(void * ptr, int size = 12);
	pFont newFonti(int f, int size = 12);
	
	pFont newImageFontv(void * ptr, const char * glyphs, float spacing = 1);
	
	pAnimation newAnimation(pImage image);
	pAnimation newAnimation(pImage image, float fw, float fh, float delay, int num = 0);
	// TODO: RESTORE pAnimation newAnimation(const char * filename);
	// TODO: RESTORE pAnimation newAnimation(const char * filename, float fw, float fh, float delay, int num = 0);
	
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size);
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size, int mode);
	
	void setCaption(const char * caption);
	
	int getWidth();
	int getHeight();
	bool isCreated();
	
	void setScissor();
	void setScissor(int x, int y, int width, int height);
	
	void setColor( int r, int g, int b, int a = 255);
	void setColor(const pColor & color);
	pColor getColor();
	
	void setBackgroundColor( int r, int g, int b );
	void setBackgroundColor( const pColor & color );
	pColor getBackgroundColor();
	
	void setBlendMode( int mode );
	void setColorMode ( int mode );
	
	int getBlendMode();
	int getColorMode();
	
	void setLineWidth( float width );
	void setLineStyle( int style );
	void setLine( float width, int style = 0 );
	void setLineStipple();
	void setLineStipple(unsigned short pattern, int repeat = 1);
	
	float getLineWidth();
	int getLineStyle();
	// int getLineStipple(lua_State * L);
	
	void setPointSize( float size );
	void setPointStyle( int style );
	void setPoint( float size, int style );
	float getPointSize();
	int getPointStyle();
	int getMaxPointSize();
	
	void setFontf( pFont font );
	void setFonti( int font, int size = 12 );
	// pFont getFont(); // (Now native)
	
	void draw( const char * str, float x, float y );
	void draw( const char * str, float x, float y, float angle );
	void draw( const char * str, float x, float y, float angle, float s );
	void draw( const char * str, float x, float y, float angle, float sx, float sy );
	void drawf( const char * str, float x, float y, float wrap, int align = 0 );
	
	// Image
	void draw( const pImage & sprite, float x, float y );
	void draw( const pImage & sprite, float x, float y , float angle);
	void draw( const pImage & sprite, float x, float y , float angle, float s);
	void draw( const pImage & sprite, float x, float y , float angle, float sx, float sy);
	
	// Animation
	void draw( const pAnimation & sprite, float x, float y );
	void draw( const pAnimation & sprite, float x, float y, float angle);
	void draw( const pAnimation & sprite, float x, float y, float angle, float s);
	void draw( const pAnimation & sprite, float x, float y, float angle, float sx, float sy);
	
	// Subsprite.
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h );
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle);
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float s);
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy);
	void draws( const pImage & sprite, float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy, float ox, float oy);
	
	// Particle System
	void draw( const pParticleSystem & system, float x, float y);
	
	// Primitives.
	void point( float x, float y );
	void line( float x1, float y1, float x2, float y2 );
	void triangle( int type, float x1, float y1, float x2, float y2, float x3, float y3 );
	void rectangle( int type, float x, float y, float w, float h );
	void quad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 );
	void circle( int type, float x, float y, float radius, int points = 10 );
	
	void push();
	void pop();
	void rotate(float r);
	void scale(float x, float y = 1.0f);
	void translate(float x, float y);
	
	// Screenshot
	void screenshotv(void * ptr);
}

%native(getModes) int love_opengl::getModes(lua_State * L);
%native(getScissor) int love_opengl::getScissor(lua_State * L);
%native(polygon) int love_opengl::polygon(lua_State * L);
%native(polygong) int love_opengl::polygong(lua_State * L);
%native(getFont) int love_opengl::getFont(lua_State * L);
%native(getLineStipple) int love_opengl::getLineStipple(lua_State * L);

%luacode{
love.graphics = mod_opengl
mod_opengl = nil


function love.graphics.newImage(a, mode)
	mode = mode or love.image_normal
	if type(a) == "string" then
		local file = love.filesystem.newFile(a)
		return love.graphics.newImagev(file, mode)
	elseif type(a) == "number" then
		return love.graphics.newImagei(a, mode)
	else
		return error("Incorrect parameter type: expected string or number.")
	end
end

function love.graphics.newFont(a, size)
	size = size or 12
	if type(a) == "string" then
		local file = love.filesystem.newFile(a)
		return love.graphics.newFontv(file, size)
	elseif type(a) == "number" then
		return love.graphics.newFonti(a, size)
	else
		return error("Incorrect parameter type: expected string or number.")
	end	
end

function love.graphics.newImageFont(a, glyphs, spacing)
	spacing = spacing or 1
	if type(a) == "string" and type(glyphs) == "string" then
		local file = love.filesystem.newFile(a)
		return love.graphics.newImageFontv(file, glyphs, spacing)
	else
		return error("Incorrect parameter type: expected string.")
	end	
end

function love.graphics.setFont(a, size)
	size = size or 12
	if type(a) == "userdata" then
		love.graphics.setFontf(a)
	elseif type(a) == "string" then
		local font = love.graphics.newFont(a, size)
		love.graphics.setFontf(font)
	elseif type(a) == "number" then
		local font = love.graphics.newFont(a, size)
		love.graphics.setFontf(font)
	else
		return error("Incorrect parameter type: expected string or Font.")
	end		
end

function love.graphics.screenshot(a)
		if type(a) == "string" then
			local file = love.filesystem.newFile(a, love.file_write)
			love.graphics.screenshotv(file)
		else
			return error("Incorrect parameter type. Expected string.")
		end
end

}
