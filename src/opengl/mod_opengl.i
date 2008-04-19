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
%include TrueTypeFont.i

%include Sprite.i
%include Image.i
%include Animation.i
%include ParticleSystem.i

namespace love_opengl
{

	// Display mode control.
	bool checkMode(int width, int height, bool fullscreen = true);
	bool setMode(int width, int height, bool fullscreen = true,	bool vsync = true, int fsaa = 0);
	bool toggleFullscreen();

	pColor newColor( int r, int g, int b, int a = 255 );
	pImage newImage(int image);
	pImage newImage(const char * filename);
	pImage newImage(const char * filename, int mode);
	pFont newFont(const char * filename, int size);
	pFont newFont(int f, int size);
	pFont newImageFont(const char * filename, const char * glyphs, float spacing = 1);
	
	pAnimation newAnimation(pImage image);
	pAnimation newAnimation(pImage image, float fw, float fh, float delay, int num = 0);
	pAnimation newAnimation(const char * filename);
	pAnimation newAnimation(const char * filename, float fw, float fh, float delay, int num = 0);
	
	pParticleSystem newParticleSystem(unsigned int size);
	
	int getWidth();
	int getHeight();
	
	void setColor( int r, int g, int b, int a = 255);
	void setColor(const pColor & color);
	void setBackgroundColor( int r, int g, int b );
	void setBackgroundColor( const pColor & color );
	
	void setBlendMode( int mode );
	void setColorMode ( int mode );
	
	void setLine( float width, int type = 0 );
	
	void setFont( pFont font );
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
	void line( float x1, float y1, float x2, float y2 );
	void triangle( int type, float x1, float y1, float x2, float y2, float x3, float y3 );
	void quad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 );
	void circle( int type, float x, float y, float radius, int points = 10 );
	
	// Console.
	void print(const char * str);	
	
}

%native(getModes) int love_opengl::getModes(lua_State * L);