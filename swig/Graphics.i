%{#include "Graphics.h"%}

namespace love
{

	class Graphics : public Device
	{
	protected:	
	public:				
		void setBackgroundColor(int r, int g, int b);
		void setColor(int r, int g, int b, int a = 255);
		void draw(const char * str, float x, float y) const;
		void draw(const char * str, float x, float y, int wrap, int align = 1);
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