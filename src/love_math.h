/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MATH_H
#define LOVE_MATH_H

namespace love
{

	// Some constants.
	const float pi = 3.14159265f;
	const float two_pi = 2*pi;
	const float to_rad = (pi/180.0f);

	// 2D-vector.
	struct vec2 { float x, y; };

	/**
	* Finds the closest power-of-two number to i, that is bigger
	* or equal to i. 
	* @param i The number to find the power-of-two number for.
	**/
	int power_of_two(int i);



} // love

#endif // LOVE_MATH_H
