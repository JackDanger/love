/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-07
**/

// LOVE
#include "wrap_Font.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	// This macro makes checking for the correct type slightly more compact.
	Font * luax_checkfont(lua_State * L, int idx)
	{
		return luax_checktype<Font>(L, idx, "Font", LOVE_GRAPHICS_FONT_BITS);
	}

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

	static const luaL_Reg wrap_Font_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getHeight", _wrap_Font_getHeight },
		{ "getWidth", _wrap_Font_getWidth },
		{ "setLineHeight", _wrap_Font_setLineHeight },
		{ "getLineHeight", _wrap_Font_getLineHeight },
		{ 0, 0 }
	};

	int wrap_Font_open(lua_State * L)
	{
		luax_register_type(L, "Font", wrap_Font_functions);
		return 0;
	}

} // opengl
} // graphics
} // love
