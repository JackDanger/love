/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_COLOR_W
#define LOVE_COLOR_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_COLOR_BITS = (LOVE_COLOR_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkcolor(L, idx) luax_checktype<Color>(L, 1, "Color", LOVE_WRAP_COLOR_BITS)

	int _wrap_Color_setRed(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		int arg = luaL_checkinteger(L, 2);
		t->setRed(arg);
		return 0;
	}

	int _wrap_Color_setGreen(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		int arg = luaL_checkinteger(L, 2);
		t->setGreen(arg);
		return 0;
	}

	int _wrap_Color_setBlue(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		int arg = luaL_checkinteger(L, 2);
		t->setBlue(arg);
		return 0;
	}

	int _wrap_Color_setAlpha(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		int arg = luaL_checkinteger(L, 2);
		t->setAlpha(arg);
		return 0;
	}

	int _wrap_Color_getRed(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		lua_pushinteger(L, t->getRed());		
		return 1;
	}

	int _wrap_Color_getGreen(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		lua_pushinteger(L, t->getGreen());		
		return 1;
	}

	int _wrap_Color_getBlue(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		lua_pushinteger(L, t->getBlue());		
		return 1;
	}

	int _wrap_Color_getAlpha(lua_State * L)
	{
		Color * t = luax_checkcolor(L, 1);
		lua_pushinteger(L, t->getAlpha());		
		return 1;
	}

	static const luaL_Reg Color_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setRed", _wrap_Color_setRed },
		{ "setGreen", _wrap_Color_setGreen },
		{ "setBlue", _wrap_Color_setBlue },
		{ "setAlpha", _wrap_Color_setAlpha },
		{ "getRed", _wrap_Color_getRed },
		{ "getGreen", _wrap_Color_getGreen },
		{ "getBlue", _wrap_Color_getBlue },
		{ "getAlpha", _wrap_Color_getAlpha },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_COLOR_W
