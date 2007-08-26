#include "Circle.h"
#include <cmath>

namespace love
{

	Circle::Circle(float radius)
	{

		setType(LOVE_TYPE_CIRCLE);

		int precision = (int)(radius/2);
		float step = (float)((2*M_PI)/precision);

		for(int i=precision-1;i>=0;i--)
			addPoint(radius * cos(step*i), radius * sin(step*i));

	}

	Circle::~Circle()
	{
	}

	float Circle::getRadius() const
	{
		return radius;
	}


}// love
