/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/
#ifndef LOVE_TIMER_H
#define LOVE_TIMER_H

// LOVE
#include "Module.h"

namespace love
{
	
	// Function typedefs.
	typedef float (*fptr_getDelta)();

	/**
	* Audio module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Timer : public Module
	{
	public:

		// Member function pointers.
		fptr_void step;
		fptr_getDelta getDelta;

		// From Module.
		bool extra(const std::string & so);

	};
}

#endif // LOVE_TIMER_H
