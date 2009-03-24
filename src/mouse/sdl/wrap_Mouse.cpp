/**
* Copyright (c) 2006-2009 LOVE Development Team
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
* --> Visit http://love2d.org for more information! (^.^)/
**/

#include "wrap_Mouse.h"

// LOVE
#include "../../luax.h"

namespace love
{
namespace mouse
{
namespace sdl
{
	int _wrap_getX(lua_State * L)
	{
		lua_pushnumber(L, Mouse::getInstance()->getX());
		return 1;
	}

	int _wrap_getY(lua_State * L)
	{
		lua_pushnumber(L, Mouse::getInstance()->getY());
		return 1;
	}

	int _wrap_getPosition(lua_State * L)
	{
		int x, y;
		Mouse::getInstance()->getPosition(&x, &y);
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		return 2;
	}

	int _wrap_setPosition(lua_State * L)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		Mouse::getInstance()->setPosition(x, y);
		return 0;
	}

	int _wrap_isDown(lua_State * L)
	{
		int b = luaL_checkint(L, 1);
		luax_pushboolean(L, Mouse::getInstance()->isDown(b));
		return 1;
	}

	int _wrap_setVisible(lua_State * L)
	{
		bool b = luax_toboolean(L, 1);
		Mouse::getInstance()->setVisible(b);
		return 0;
	}

	int _wrap_isVisible(lua_State * L)
	{
		luax_pushboolean(L, Mouse::getInstance()->isVisible());
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
		return luax_register_module(L, Mouse::getInstance(), wrap_Mouse_functions, 0);
	}


} // sdl
} // mouse
} // love
