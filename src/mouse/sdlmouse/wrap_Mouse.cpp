/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_MOUSE_SDLMOUSE_WRAP_MOUSE_H
#define LOVE_MOUSE_SDLMOUSE_WRAP_MOUSE_H

// LOVE
#include "../../luax.h"

// sdlmouse
#include "Mouse.h"

namespace love
{
namespace mouse
{
namespace sdlmouse
{
	int _wrap_getX(lua_State * L)
	{
		lua_pushnumber(L, Mouse::__getinstance()->getX());
		return 1;
	}

	int _wrap_getY(lua_State * L)
	{
		lua_pushnumber(L, Mouse::__getinstance()->getY());
		return 1;
	}

	int _wrap_getPosition(lua_State * L)
	{
		int x, y;
		Mouse::__getinstance()->getPosition(&x, &y);
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		return 2;
	}

	int _wrap_setPosition(lua_State * L)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		Mouse::__getinstance()->setPosition(x, y);
		return 0;
	}

	int _wrap_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, Mouse::__getinstance()->isDown(b));
		return 1;
	}

	int _wrap_setVisible(lua_State * L)
	{
		bool b = luax_toboolean(L, 1);
		Mouse::__getinstance()->setVisible(b);
		return 0;
	}

	int _wrap_isVisible(lua_State * L)
	{
		luax_pushboolean(L, Mouse::__getinstance()->isVisible());
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg wrap_Mouse_functions[] = {
		{ "getX", _wrap_getX },
		{ "getY", _wrap_getY },
		{ "setPosition", _wrap_setPosition },
		{ "isDown", _wrap_isDown },
		{ "setVisible", _wrap_setVisible },
		{ "isVisible", _wrap_isVisible },
		{ "getPosition", _wrap_getPosition },
		{ 0, 0 }
	};

	int wrap_Mouse_open(lua_State * L)
	{
		luax_register_module(L, "mouse", wrap_Mouse_functions);
		return 0;
	}

} // sdlmouse
} // mouse
} // love

#endif // LOVE_MOUSE_SDLMOUSE_WRAP_MOUSE_H
