/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_WORLD_W
#define LOVE_WORLD_W

#include "luax.h"

#include "wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_WORLD_BITS = (LOVE_WORLD_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkworld(L, idx) luax_checktype<World>(L, idx, "World", LOVE_WRAP_WORLD_BITS)

	int _wrap_World_update(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		float dt = (float)luaL_checknumber(L, 2);
		t->update(dt);
		return 0;
	}

	int _wrap_World_setCallback(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		lua_remove(L, 1);
		return t->setCallback(L);
	}

	int _wrap_World_getCallback(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		lua_remove(L, 1);
		return t->getCallback(L);
	}

	int _wrap_World_setGravity(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setGravity(arg1, arg2);
		return 0;
	}

	int _wrap_World_getGravity(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		lua_remove(L, 1);
		return t->getGravity(L);
	}

	int _wrap_World_setAllowSleep(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		bool b = luax_toboolean(L, 2);
		t->setAllowSleep(b);
		return 0;
	}

	int _wrap_World_isAllowSleep(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		luax_pushboolean(L, t->isAllowSleep());
		return 1;
	}

	int _wrap_World_getBodyCount(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		lua_pushinteger(L, t->getBodyCount());
		return 1;
	}

	int _wrap_World_getJointCount(lua_State * L)
	{
		World * t = luax_checkworld(L, 1);
		lua_pushinteger(L, t->getJointCount());
		return 1;
	}

	static const luaL_Reg World_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "update", _wrap_World_update },
		{ "setCallback", _wrap_World_setCallback },
		{ "getCallback", _wrap_World_getCallback },
		{ "setGravity", _wrap_World_setGravity },
		{ "getGravity", _wrap_World_getGravity },
		{ "setAllowSleep", _wrap_World_setAllowSleep },
		{ "isAllowSleep", _wrap_World_isAllowSleep },
		{ "getBodyCount", _wrap_World_getBodyCount },
		{ "getJointCount", _wrap_World_getJointCount },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_WORLD_W
