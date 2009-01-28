/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#include "wrap_Joystick.h"

// LOVE
#include "Joystick.h"

namespace love
{
namespace joystick
{
namespace sdljoystick
{
	int _wrap_getNumJoysticks(lua_State * L)
	{
		lua_pushinteger(L, Joystick::__getinstance()->getNumJoysticks());
		return 1;
	}

	int _wrap_getName(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushstring(L, Joystick::__getinstance()->getName(index));
		return 1;
	}
	
	int _wrap_open(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		luax_pushboolean(L, Joystick::__getinstance()->open(index));
		return 1;
	}

	int _wrap_isOpen(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		luax_pushboolean(L, Joystick::__getinstance()->isOpen(index));
		return 1;
	}

	int _wrap_getNumAxes(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, Joystick::__getinstance()->getNumAxes(index));
		return 1;
	}

	int _wrap_getNumBalls(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, Joystick::__getinstance()->getNumBalls(index));
		return 1;
	}

	int _wrap_getNumButtons(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, Joystick::__getinstance()->getNumButtons(index));
		return 1;
	}

	int _wrap_getNumHats(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		lua_pushinteger(L, Joystick::__getinstance()->getNumHats(index));
		return 1;
	}

	int _wrap_getAxis(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int axis = luaL_checkint(L, 2);
		lua_pushnumber(L, Joystick::__getinstance()->getAxis(index, axis));
		return 1;
	}

	int _wrap_getAxes(lua_State * L)
	{
		return Joystick::__getinstance()->getAxes(L);
	}

	int _wrap_getBall(lua_State * L)
	{
		return Joystick::__getinstance()->getBall(L);
	}

	int _wrap_isDown(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int button = luaL_checkint(L, 2);
		luax_pushboolean(L, Joystick::__getinstance()->isDown(index, button));
		return 1;
	}

	int _wrap_getHat(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		int hat = luaL_checkint(L, 2);
		lua_pushinteger(L, Joystick::__getinstance()->getHat(index, hat));
		return 1;
	}

	int _wrap_close(lua_State * L)
	{
		int index = luaL_checkint(L, 1);
		Joystick::__getinstance()->close(index);
		return 0;
	}
	
	// List of functions to wrap.
	static const luaL_Reg wrap_Joystick_functions[] = {
		{ "getNumJoysticks", _wrap_getNumJoysticks },
		{ "getName", _wrap_getName },
		{ "open", _wrap_open },
		{ "isOpen", _wrap_isOpen },
		{ "getNumAxes", _wrap_getNumAxes },
		{ "getNumBalls", _wrap_getNumBalls },
		{ "getNumButtons", _wrap_getNumButtons },
		{ "getNumHats", _wrap_getNumHats },
		{ "getAxis", _wrap_getAxis },

		{ "getAxes", _wrap_getAxes },
		{ "getBall", _wrap_getBall },

		{ "isDown", _wrap_isDown },
		{ "getHat", _wrap_getHat },
		{ "close", _wrap_close },
		{ 0, 0 }
	};

	int wrap_Joystick_open(lua_State * L)
	{
		luax_register_module(L, "joystick", wrap_Joystick_functions);
		return 0;
	}

} // sdljoystick
} // joystick
} // love
