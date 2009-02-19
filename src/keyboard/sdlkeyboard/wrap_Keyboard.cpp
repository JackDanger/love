/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

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
