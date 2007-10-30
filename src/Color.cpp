#include "Color.h"

namespace love
{
	Color::Color()
	{
		red = blue = green = alpha = 255;
	}

	Color::Color(int code)
	{
		red = (code & 0xFF0000) >> 16;
		green = (code & 0x00FF00) >> 8;
		blue = code & 0x0000FF;
		alpha = 255;
	}

	Color::Color(int red, int green, int blue, int alpha)
	{
		this->red		= red;
		this->green		= green;
		this->blue		= blue;
		this->alpha		= alpha;
	}

	/*Color::Color(float red, float green, float blue, float alpha)
	{
		this->red = (int)(red * 255);
		this->green = (int)(green * 255);
		this->blue = (int)(blue * 255);
		this->alpha = (int)(alpha * 255);
	}*/

	Color::~Color()
	{}

	void Color::update(float dt)
	{}

	void Color::setColor(float t)
	{}
}
