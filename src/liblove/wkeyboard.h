/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_KEYBOARD_W
#define LOVE_KEYBOARD_W

// LOVE
#include "luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error "LOVE_WRAP_NAMESPACE must be defined."
#endif

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, isDown(b));
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "isDown", _wrap_isDown },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "keyboard", module_fn);
		return 0;
	}

}
}

#endif // LOVE_KEYBOARD_W
