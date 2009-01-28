/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_KEYBOARD_SDLKEYBOARD_WRAP_KEYBOARD_H
#define LOVE_KEYBOARD_SDLKEYBOARD_WRAP_KEYBOARD_H

// LOVE
#include "../../luax.h"

// sdlkeyboard
#include "Keyboard.h"

namespace love
{
namespace keyboard
{
namespace sdlkeyboard
{
	int _wrap_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, Keyboard::__getinstance()->isDown(b));
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg wrap_Keyboard_functions[] = {
		{ "isDown", _wrap_isDown },
		{ 0, 0 }
	};

	int wrap_Keyboard_open(lua_State * L)
	{
		luax_register_module(L, "keyboard", wrap_Keyboard_functions);
		return 0;
	}

} // sdlkeyboard
} // keyboard
} // love

#endif // LOVE_KEYBOARD_SDLKEYBOARD_WRAP_KEYBOARD_H
