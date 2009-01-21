/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-15
**/

#ifndef LOVE_VERTEX_BUFFER_W
#define LOVE_VERTEX_BUFFER_W

#include "../luax.h"
#include "../wwrap.h"

#include "wDrawable.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_VERTEX_BUFFER_BITS = (LOVE_VERTEX_BUFFER_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkvertexbuffer(L, idx) luax_checktype<VertexBuffer>(L, idx, "VertexBuffer", LOVE_WRAP_VERTEX_BUFFER_BITS)

	int _wrap_VertexBuffer_setType(lua_State * L)
	{
		VertexBuffer * t = luax_checkvertexbuffer(L, 1);
		int type = luaL_checkint(L, 2);
		t->setType(type);
		return 0;
	}

	int _wrap_VertexBuffer_getType(lua_State * L)
	{
		VertexBuffer * t = luax_checkvertexbuffer(L, 1);
		lua_pushnumber(L, t->getType());
		return 1;
	}

	int _wrap_VertexBuffer_add(lua_State * L)
	{
		VertexBuffer * vb = luax_checkvertexbuffer(L, 1);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float s = (float)luaL_optnumber(L, 4, 0.0f);
		float t = (float)luaL_optnumber(L, 5, 0.0f);
		unsigned char r = (unsigned char)luaL_optnumber(L, 6, 255);
		unsigned char g = (unsigned char)luaL_optnumber(L, 7, 255);
		unsigned char b = (unsigned char)luaL_optnumber(L, 8, 255);
		unsigned char a = (unsigned char)luaL_optnumber(L, 9, 255);
		vb->add(x, y, s, t, r, g, b, a);
		return 0;
	}

	int _wrap_VertexBuffer_clear(lua_State * L)
	{
		VertexBuffer * t = luax_checkvertexbuffer(L, 1);
		t->clear();
		return 0;
	}

	static const luaL_Reg VertexBuffer_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setType", _wrap_VertexBuffer_setType },
		{ "getType", _wrap_VertexBuffer_getType },
		{ "add", _wrap_VertexBuffer_add },
		{ "clear", _wrap_VertexBuffer_clear },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_VERTEX_BUFFER_W
