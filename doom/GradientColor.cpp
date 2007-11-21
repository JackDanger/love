#include "GradientColor.h"

namespace love
{
	GradientColor::GradientColor()
	{
		colors.clear();
		positions.clear();
		setType(LOVE_TYPE_GRADIENT_COLOR);
	}

	GradientColor::GradientColor(Color color1, Color color2)
	{
		this->color1 = color1;
		this->color2 = color2;
		setType(LOVE_TYPE_GRADIENT_COLOR);
	}

	GradientColor::~GradientColor()
	{}

	void GradientColor::add(Color newColor)
	{
		add(newColor, -1);
	}

	void GradientColor::add(Color newColor, float position)
	{
		colors.push_back(newColor);

		positions.push_back(position);
	}

	Color GradientColor::getColor(float position)
	{
		int red, green, blue;

		//only two colors are useable right now
		red = (int)(color1.getRed() + ((color2.getRed() - color1.getRed()) * position));
		green = (int)(color1.getGreen() + ((color2.getGreen() - color1.getGreen()) * position));
		blue = (int)(color1.getBlue() + ((color2.getBlue() - color1.getBlue()) * position));

		return Color(red, green, blue);
	}
}
