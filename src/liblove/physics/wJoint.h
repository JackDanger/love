/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_JOINT_W
#define LOVE_JOINT_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_JOINT_BITS = (LOVE_JOINT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkjoint(L, idx) luax_checktype<Joint>(L, idx, "Joint", LOVE_WRAP_JOINT_BITS)

	int _wrap_Joint_getType(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		lua_pushinteger(L, t->getType());
		return 1;
	}

	int _wrap_Joint_getAnchors(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		lua_remove(L, 1);
		return t->getAnchors(L);
	}

	int _wrap_Joint_getReactionForce(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		lua_remove(L, 1);
		return t->getReactionForce(L);
	}

	int _wrap_Joint_getReactionTorque(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		lua_pushnumber(L, t->getReactionTorque());
		return 1;
	}

	int _wrap_Joint_setCollideConnected(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setCollideConnected(arg1);
		return 0;
	}

	int _wrap_Joint_getCollideConnected(lua_State * L)
	{
		Joint * t = luax_checkjoint(L, 1);
		luax_pushboolean(L, t->getCollideConnected());
		return 1;
	}

	static const luaL_Reg Joint_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getType", _wrap_Joint_getType },
		{ "getAnchors", _wrap_Joint_getAnchors },
		{ "getReactionForce", _wrap_Joint_getReactionForce },
		{ "getReactionTorque", _wrap_Joint_getReactionTorque },
		{ "setCollideConnected", _wrap_Joint_setCollideConnected },
		{ "getCollideConnected", _wrap_Joint_getCollideConnected },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_JOINT_W
