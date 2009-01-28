/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Keyboard module using the SDL's input abstraction.
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_KEYBOARD_SDLKEYBOARD_KEYBOARD_H
#define LOVE_KEYBOARD_SDLKEYBOARD_KEYBOARD_H

// LOVE
#include "../../luax.h"

namespace love
{
namespace keyboard
{
namespace sdlkeyboard
{
	class Keyboard
	{
	private:
		static Keyboard * _instance;
	protected:
		Keyboard();
	public:

		static Keyboard * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		/**
		* Checks whether a certain key is down or not.
		* @param key A key identifier.
		**/
		bool isDown(int key) const;

	}; // Keyboard

} // sdlkeyboard
} // keyboard
} // love

#endif // LOVE_KEYBOARD_SDLKEYBOARD_KEYBOARD_H