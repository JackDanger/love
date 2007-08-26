#include "AbstractColor.h"

namespace love
{
	AbstractColor::AbstractColor()
	{
		red = blue = green = alpha = 255;
	}

	AbstractColor::~AbstractColor()
	{
	}

	int AbstractColor::getRed() const
	{
		return red;
	}

	int AbstractColor::getGreen() const
	{
		return green;
	}

	int AbstractColor::getBlue() const
	{
		return blue;
	}

	int AbstractColor::getAlpha() const
	{
		return alpha;
	}

	int AbstractColor::getCode() const
	{
		return (blue | (green << 8) | (red << 16));
	}

	void AbstractColor::setColor(int red, int green, int blue, int alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

}
