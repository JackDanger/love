#include "Rectangle.h"

namespace love
{

	Rectangle::Rectangle()
	{
		setType(LOVE_TYPE_RECTANGLE);
	}

	Rectangle::Rectangle(float width, float height)
	{
		setType(LOVE_TYPE_RECTANGLE);
		addPoint(0, 0);
		addPoint(0, height);
		addPoint(width, height);
		addPoint(width, 0);
	}

	Rectangle::~Rectangle()
	{
	}

	float Rectangle::getWidth()
	{
		return width;
	}

	float Rectangle::getHeight()
	{
		return height;
	}

}// love