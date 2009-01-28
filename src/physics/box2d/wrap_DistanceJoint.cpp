/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#include "wrap_DistanceJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	DistanceJoint * luax_checkdistancejoint(lua_State * L, int idx)
	{
		return luax_checktype<DistanceJoint>(L, idx, "DistanceJoint", LOVE_PHYSICS_DISTANCE_JOINT_BITS);
	}

	int _wrap_DistanceJoint_setLength(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setLength(arg1);
		return 0;
	}

	int _wrap_DistanceJoint_getLength(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		lua_pushnumber(L, t->getLength());
		return 1;
	}

	int _wrap_DistanceJoint_setFrequency(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setFrequency(arg1);
		return 0;
	}

	int _wrap_DistanceJoint_getFrequency(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		lua_pushnumber(L, t->getFrequency());
		return 1;
	}

	int _wrap_DistanceJoint_setDamping(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setDamping(arg1);
		return 0;
	}

	int _wrap_DistanceJoint_getDamping(lua_State * L)
	{
		DistanceJoint * t = luax_checkdistancejoint(L, 1);
		lua_pushnumber(L, t->getDamping());
		return 1;
	}

	static const luaL_Reg wrap_DistanceJoint_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setLength", _wrap_DistanceJoint_setLength },
		{ "getLength", _wrap_DistanceJoint_getLength },
		{ "setFrequency", _wrap_DistanceJoint_setFrequency },
		{ "getFrequency", _wrap_DistanceJoint_getFrequency },
		{ "setDamping", _wrap_DistanceJoint_setDamping },
		{ "getDamping", _wrap_DistanceJoint_getDamping },
		// From Joint.
		{ "getType", _wrap_Joint_getType },
		{ "getAnchors", _wrap_Joint_getAnchors },
		{ "getReactionForce", _wrap_Joint_getReactionForce },
		{ "getReactionTorque", _wrap_Joint_getReactionTorque },
		{ "setCollideConnected", _wrap_Joint_setCollideConnected },
		{ "getCollideConnected", _wrap_Joint_getCollideConnected },
		{ 0, 0 }
	};

	int wrap_DistanceJoint_open(lua_State * L)
	{
		luax_register_type(L, "DistanceJoint", wrap_DistanceJoint_functions);
		return 0; 
	}

} // box2d
} // physics
} // love
