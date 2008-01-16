#include "love_math.h"

#include <cmath>

namespace love
{

	int power_of_two(int i)
	{
		// @todo Less "while", more awesome.
		// float exp = log(value) / log(2) // etc
		int temp = 1;
		while(temp < i)
			temp *= 2;
		return temp;
	}

} // love
