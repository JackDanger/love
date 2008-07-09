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
	
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size);
	pParticleSystem newParticleSystem(pImage sprite, unsigned int size, int mode);
	
	void setCaption(const char * caption);
	
	int getWidth();
	int getHeight();
	bool isCreated();
	
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
	
	float getLineWidth();
	int getLineStyle();
	
	void setFont( pFont font );
	pFont getFont();
	
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
	void oldQuad( int type, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4 );
	void circle( int type, float x, float y, float radius, int points = 10 );
}

%native(getModes) int love_opengl::getModes(lua_State * L);

%luacode{
love.graphics = mod_opengl
}
