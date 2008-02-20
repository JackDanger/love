%{
#include "using_graphics.h"
#include "Graphics.h"
%}

namespace love
{

	class Graphics : public Device
	{
	protected:	
	public:				
		void setBackgroundColor(int r, int g, int b);
		void setColor(int r, int g, int b, int a = 255);
		void draw(const char * str, float x, float y) const;
		void draw(const char * str, float x, float y, int wrap, int align = 1) const;
		void drawLine(float xpos, float ypos, float x1, float y1, float x2, float y2, float lineWidth = 1) const;
		void drawTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth = 1) const;
		void fillTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3) const;
		void drawQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth = 1) const;
		void fillQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;
		void drawCircle(float xpos, float ypos, float radius, float points = 10, float lineWidth = 1) const;
		void fillCircle(float xpos, float ypos, float radius, float points = 10) const;
		virtual void setBlendMode(int mode);
		void setColorMode(int mode);
		int getWidth() const;
		int getHeight() const;
	};
	
}

// Extensions
%extend love::Graphics 
{

	void setBackgroundColor(const pColor * color) 
	{
		self->setBackgroundColor(*color);
	}
	
	void setColor(const pColor * color)
	{
		self->setColor(*color);
	}
	
	void setFont(const pFont * font)
	{
		self->setFont(*font);
	}

	/**
	* Image
	**/

	void draw(const pImage * sprite, float x, float y)
	{
		(*sprite)->render(x, y);
	}
	
	void draw(const pImage * sprite, float x, float y, float angle, float s = 1.0f)
	{
		(*sprite)->render(x, y, angle, s, s);
	}
	
	void draw(const pImage * sprite, float x, float y, float angle, float sx, float sy)
	{
		(*sprite)->render(x, y, angle, sx, sy);
	}
	
	void drawSection( const pImage * sprite, float x, float y, float w, float h )
	{
		(*sprite)->render(x, y, w, h);
	}
	
	/**
	* Animation
	**/

	void draw(const pAnimation * sprite, float x, float y)
	{
		(*sprite)->render(x, y);
	}
	
	void draw(const pAnimation * sprite, float x, float y, float angle, float s = 1.0f)
	{
		(*sprite)->render(x, y, angle, s, s);
	}
	
	void draw(const pAnimation * sprite, float x, float y, float angle, float sx, float sy)
	{
		(*sprite)->render(x, y, angle, sx, sy);
	}

	/**
	* Particlesystem
	**/

	void draw(const pParticlesystem * system)
	{
		(*system)->render();
	}
	
	void draw(const pParticlesystem * system, float x, float y)
	{
		(*system)->render(x, y);
	}
	
}