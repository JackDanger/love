%{#include "Graphics.h"%}

namespace love
{

	class Graphics : public Device
	{
	protected:	
	public:				
		void setBackgroundColor(pColor color);
		void setBackgroundColor(int r, int g, int b);
		void setColor(pColor color);
		void setColor(int r, int g, int b, int a = 255);
		void setFont(pFont font);
		void draw(const char * str, float x, float y) const;
		void draw(const char * str, float x, float y, int wrap, int align = 1);
	};
	
}

// Extensions
%extend love::Graphics 
{
	void draw(const pImage & sprite, float x, float y) const
	{
		sprite->render(x, y);
	}
	
	void draw(const pImage & sprite, float x, float y, float angle, float s = 1.0f) const
	{
		sprite->render(x, y, angle, s, s);
	}
	
	void draw(const pImage & sprite, float x, float y, float angle, float sx, float sy) const
	{
		sprite->render(x, y, angle, sx, sy);
	}
	
	void draw(const pParticlesystem & system) const
	{
		system->render();
	}
	
	void draw(const pParticlesystem & system, float x, float y) const
	{
		system->render(x, y);
	}
}