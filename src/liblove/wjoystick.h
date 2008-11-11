/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_JOYSTICK_W
#define LOVE_JOYSTICK_W

// LOVE
#include "luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error "LOVE_WRAP_NAMESPACE must be defined."
#endif

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_getNumJoysticks(lua_State * L)
	{
		lua_pushinteger(L, getNumJoysticks());
		return 1;
	}

	int _wrap_getName(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushstring(L, getName(index));
		return 1;
	}
	
	int _wrap_open(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		luax_pushboolean(L, open(index));
		return 1;
	}

	int _wrap_isOpen(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		luax_pushboolean(L, isOpen(index));
		return 1;
	}

	int _wrap_getNumAxes(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, getNumAxes(index));
		return 1;
	}

	int _wrap_getNumBalls(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, getNumBalls(index));
		return 1;
	}

	int _wrap_getNumButtons(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, getNumButtons(index));
		return 1;
	}

	int _wrap_getNumHats(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, getNumHats(index));
		return 1;
	}

	int _wrap_getAxis(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int axis = luaL_checkint(L, 2);
		lua_pushnumber(L, getAxis(index, axis));
		return 1;
	}

	// getAxes

	// getBall

	int _wrap_isDown(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int button = luaL_checkint(L, 2);
		luax_pushboolean(L, isDown(index, button));
		return 1;
	}

	int _wrap_getHat(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int hat = luaL_checkint(L, 2);
		lua_pushinteger(L, getHat(index, hat));
		return 1;
	}

	int _wrap_close(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		close(index);
		return 0;
	}
	
	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "getNumJoysticks", _wrap_getNumJoysticks },
		{ "getName", _wrap_getName },
		{ "open", _wrap_open },
		{ "isOpen", _wrap_isOpen },
		{ "getNumAxes", _wrap_getNumAxes },
		{ "getNumBalls", _wrap_getNumBalls },
		{ "getNumButtons", _wrap_getNumButtons },
		{ "getNumHats", _wrap_getNumHats },
		{ "getAxis", _wrap_getAxis },

		{ "getAxes", getAxes },
		{ "getBall", getBall },

		{ "isDown", _wrap_isDown },
		{ "getHat", _wrap_getHat },
		{ "close", _wrap_close },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "joystick", module_fn);
		return 0;
	}

} // LOVE_WRAP_NAMESPACE
} // love

#endif // LOVE_JOYSTICK_W