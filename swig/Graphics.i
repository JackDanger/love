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
	};
	
}

// Extensions
%extend love::Graphics 
{
	void draw(const pImage & sprite, float x, float y) const
	{
		sprite->render(x - sprite->getWidth()/2.0f, y - sprite->getHeight()/2.0f);
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