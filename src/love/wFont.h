/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-07
**/

#ifndef LOVE_FONT_W
#define LOVE_FONT_W

#include "luax.h"

#include "wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_FONT_BITS = (LOVE_FONT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkfont(L, idx) luax_checktype<Font>(L, 1, "Font", LOVE_WRAP_FONT_BITS)

	int _wrap_Font_getHeight(lua_State * L)
	{
		Font * t = luax_checkfont(L, 1);
		lua_pushnumber(L, t->getHeight());
		return 1;
	}

	int _wrap_Font_getWidth(lua_State * L)
	{
		Font * t = luax_checkfont(L, 1);
		const char * str = luaL_checkstring(L, 2);
		lua_pushnumber(L, t->getWidth(str));
		return 1;
	}

	int _wrap_Font_setLineHeight(lua_State * L)
	{
		Font * t = luax_checkfont(L, 1);
		float h = (float)luaL_checknumber(L, 2);
		t->setLineHeight(h);
		return 0;
	}

	int _wrap_Font_getLineHeight(lua_State * L)
	{
		Font * t = luax_checkfont(L, 1);
		lua_pushnumber(L, t->getLineHeight());
		return 1;
	}

	static const luaL_Reg Font_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getHeight", _wrap_Font_getHeight },
		{ "getWidth", _wrap_Font_getWidth },
		{ "setLineHeight", _wrap_Font_setLineHeight },
		{ "getLineHeight", _wrap_Font_getLineHeight },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_FONT_W
