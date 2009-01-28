#include "Color.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Color::Color() 
		: red(255), green(255), blue(255), alpha(255)
	{
	}

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

} // opengl
} // graphics
} // love
