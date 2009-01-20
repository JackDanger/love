/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_MOUSE_W
#define LOVE_MOUSE_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error "LOVE_WRAP_NAMESPACE must be defined."
#endif

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_getX(lua_State * L)
	{
		lua_pushnumber(L, getX());
		return 1;
	}

	int _wrap_getY(lua_State * L)
	{
		lua_pushnumber(L, getY());
		return 1;
	}

	int _wrap_setPosition(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		setPosition(x, y);
		return 0;
	}

	int _wrap_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, isDown(b));
		return 1;
	}

	int _wrap_setVisible(lua_State * L)
	{
		bool b = luax_toboolean(L, 1);
		setVisible(b);
		return 0;
	}

	int _wrap_isVisible(lua_State * L)
	{
		luax_pushboolean(L, isVisible());
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "getX", _wrap_getX },
		{ "getY", _wrap_getY },
		{ "setPosition", _wrap_setPosition },
		{ "isDown", _wrap_isDown },
		{ "setVisible", _wrap_setVisible },
		{ "isVisible", _wrap_isVisible },
		{ "getPosition", getPosition },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "mouse", module_fn);
		return 0;
	}

}
}

#endif // LOVE_MOUSE_W
