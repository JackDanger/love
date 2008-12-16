/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-15
**/

#ifndef LOVE_IMAGE_DATA_TYPE_W
#define LOVE_IMAGE_DATA_TYPE_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_IMAGE_DATA_BITS = (LOVE_IMAGE_DATA_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkimagedata(L, idx) luax_checktype<ImageData>(L, idx, "ImageData", LOVE_IMAGE_DATA_BITS)

	int _wrap_ImageData_getWidth(lua_State * L)
	{
		ImageData * t = luax_checkimagedata(L, 1);
		lua_pushinteger(L, t->getWidth());
		return 1;
	}

	int _wrap_ImageData_getHeight(lua_State * L)
	{
		ImageData * t = luax_checkimagedata(L, 1);
		lua_pushinteger(L, t->getHeight());
		return 1;
	}

	int _wrap_ImageData_getPixel(lua_State * L)
	{
		ImageData * t = luax_checkimagedata(L, 1);
		int x = luaL_checkint(L, 2);
		int y = luaL_checkint(L, 3);
		rgba c = t->getPixel(x, y);
		lua_pushnumber(L, c.r);
		lua_pushnumber(L, c.g);
		lua_pushnumber(L, c.b);
		lua_pushnumber(L, c.a);
		return 4;
	}

	int _wrap_ImageData_setPixel(lua_State * L)
	{
		ImageData * t = luax_checkimagedata(L, 1);
		int x = luaL_checkint(L, 2);
		int y = luaL_checkint(L, 3);
		rgba c;
		c.r = luaL_checkint(L, 4);
		c.g = luaL_checkint(L, 5);
		c.b = luaL_checkint(L, 6);
		c.a = luaL_checkint(L, 7);
		t->setPixel(x, y, c);
		return 0;
	}

	int _wrap_ImageData_mapPixel(lua_State * L)
	{
		ImageData * t = luax_checkimagedata(L, 1);

		if(!lua_isfunction(L, 2))
			return luaL_error(L, "Function expected");
		
		int w = t->getWidth();
		int h = t->getHeight();

		for(int i = 0; i < w; i++)
		{
			for(int j = 0; j < h; j++)
			{
				lua_pushvalue(L, 2);
				lua_pushnumber(L, i);
				lua_pushnumber(L, j);
				rgba c = t->getPixel(i, j);
				lua_pushnumber(L, c.r);
				lua_pushnumber(L, c.g);
				lua_pushnumber(L, c.b);
				lua_pushnumber(L, c.a);
				lua_call(L, 6, 4);
				c.r = luaL_optint(L, -4, 0);
				c.g = luaL_optint(L, -3, 0);
				c.b = luaL_optint(L, -2, 0);
				c.a = luaL_optint(L, -1, 0);
				t->setPixel(i, j, c);
				lua_pop(L, 4);
			}
		}
		return 0;
	}

	static const luaL_Reg ImageData_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getWidth", _wrap_ImageData_getWidth },
		{ "getHeight", _wrap_ImageData_getHeight },
		{ "getPixel", _wrap_ImageData_getPixel },
		{ "setPixel", _wrap_ImageData_setPixel },
		{ "mapPixel", _wrap_ImageData_mapPixel },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_IMAGE_DATA_TYPE_W
