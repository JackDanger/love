/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-15
**/

#include "wrap_SpriteBatch.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	SpriteBatch * luax_checkspritebatch(lua_State * L, int idx)
	{
		return luax_checktype<SpriteBatch>(L, idx, "SpriteBatch", LOVE_GRAPHICS_SPRITE_BATCH_BITS); 
	}

	int _wrap_SpriteBatch_add(lua_State * L)
	{
		SpriteBatch * t = luax_checkspritebatch(L, 1);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		t->add(x, y, angle, sx, sy, ox, oy);
		return 0;
	}

	int _wrap_SpriteBatch_clear(lua_State * L)
	{
		SpriteBatch * t = luax_checkspritebatch(L, 1);
		t->clear();
		return 0;
	}

	static const luaL_Reg wrap_SpriteBatch_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "add", _wrap_SpriteBatch_add },
		{ "clear", _wrap_SpriteBatch_clear },
		{ 0, 0 }
	};

	int wrap_SpriteBatch_open(lua_State * L)
	{
		luax_register_type(L, "SpriteBatch", wrap_SpriteBatch_functions);
		return 0;
	}

} // opengl
} // graphics
} // love