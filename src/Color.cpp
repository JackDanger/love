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

	/*void Color::setRed(float value)
	{
		red = (int)(value * 255);
	}

	void Color::setGreen(float value)
	{
		green = (int)(value * 255);
	}

	void Color::setBlue(float value)
	{
		blue = (int)(value * 255);
	}

	void Color::setAlpha(float value)
	{
		alpha = (int)(value * 255);
	}

	void Color::setColor(float red, float green, float blue)
	{
		this->red = (int)(red * 255);
		this->green = (int)(green * 255);
		this->blue = (int)(blue * 255);
	}

	void Color::setColor(float red, float green, float blue, float alpha)
	{
		this->red = (int)(red * 255);
		this->green = (int)(green * 255);
		this->blue = (int)(blue * 255);
		this->alpha = (int)(alpha * 255);
	}*/

	Color Color::getGradient(Color * other, float amount)
	{
		Color temp;
		temp.setRed((int)(other->getRed() + ((this->red - other->getRed()) * amount)));
		temp.setGreen((int)(other->getGreen() + ((this->green - other->getGreen()) * amount)));
		temp.setBlue((int)(other->getBlue() + ((this->blue - other->getBlue()) * amount)));
		temp.setAlpha((int)(other->getAlpha() + ((this->alpha - other->getAlpha()) * amount)));
		return temp;
	}

	void Color::update(float dt)
	{
	}

	void Color::setColor(float t)
	{
	}
}
