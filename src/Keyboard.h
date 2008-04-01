/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_KEYBOARD_H
#define LOVE_KEYBOARD_H

#include "Module.h"

namespace love
{
	// Typedefs.
	typedef bool (*fptr_isDown)(int key);

	/**
	* Keyboard module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Keyboard : public Module
	{
	public:

		// Member functions.
		fptr_isDown isDown;

		// From Module.
		bool extra(const std::string & so);
	};
}

#endif // LOVE_KEYBOARD_H
