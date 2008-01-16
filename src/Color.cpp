#include "Color.h"

#include <string>

namespace love
{
	Color::Color(int r, int g, int b, int a) 
		: red(r), green(g), blue(b), alpha(a)
	{
	}

	Color::~Color()
	{
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

} // love

