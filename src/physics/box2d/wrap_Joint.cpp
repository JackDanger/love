/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

// LOVE
#include "wrap_Joint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Joint * luax_checkjoint(lua_State * L, int idx)
	{
		return luax_checktype<Joint>(L, idx, "Joint", LOVE_PHYSICS_JOINT_BITS);
	}

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

	static const luaL_Reg wrap_Joint_functions[] = {
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

	int wrap_Joint_open(lua_State * L)
	{
		luax_register_type(L, "Joint", wrap_Joint_functions);
		return 0;
	}

} // box2d
} // physics
} // love
