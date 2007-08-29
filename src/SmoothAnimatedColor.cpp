#include "SmoothAnimatedColor.h"
#include <cmath>

namespace love
{

	SmoothAnimatedColor::SmoothAnimatedColor(Container<Color> * colors) : AnimatedColor()
	{
	}

	SmoothAnimatedColor::~SmoothAnimatedColor()
	{
	}

	float SmoothAnimatedColor::map(float t)
	{

		//float temp = -10*pow(t, 3) + 15 *t*t - 4*t;

		//if(temp < 0) temp = 0;
		//if(temp > 1) temp = 1;

		return -2*pow(t, 3) + 3 * t * t;
	}


}// love
