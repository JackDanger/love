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