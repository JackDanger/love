/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_DRAWABLE_W
#define LOVE_DRAWABLE_W

#include "luax.h"

#include "wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkdrawable(L, idx) luax_checktype<Drawable>(L, idx, "Drawable", LOVE_DRAWABLE_BITS)

	int _wrap_Drawable_setOffset(lua_State * L)
	{
		Drawable * t = luax_checkdrawable(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		t->setOffset(x, y);
		return 0;
	}

	int _wrap_Drawable_getOffset(lua_State * L)
	{
		Drawable * t = luax_checkdrawable(L, 1);
		lua_pushnumber(L, t->getOffsetX());
		lua_pushnumber(L, t->getOffsetY());
		return 2;
	}

	static const luaL_Reg Drawable_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setOffset", _wrap_Drawable_setOffset },
		{ "getOffset", _wrap_Drawable_getOffset },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_DRAWABLE_W
