#include "Color.h"

#include <string>

namespace love_opengl
{
	Color::Color(int r, int g, int b, int a) 
		: red(r), green(g), blue(b), alpha(a)
	{
	}

	Color::~Color()
	{
	}

	void Color::setRed(int red)
	{
		this->red = red;
	}

	void Color::setGreen(int green)
	{
		this->green = green;
	}

	void Color::setBlue(int blue)
	{
		this->blue = blue;
	}

	void Color::setAlpha(int alpha)
	{
		this->alpha = alpha;
	}

	int Color::getRed() const
	{
		return red;
	}

	int Color::getGreen() const
	{
		return green;
	}

	int Color::getBlue() const
	{
		return blue;
	}

	int Color::getAlpha() const
	{
		return alpha;
	}

	void Color::update(float dt)
	{
		// Nothing happens.
	}

} // love_opengl

