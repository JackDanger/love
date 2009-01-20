/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_DISTANCE_JOINT_W
#define LOVE_DISTANCE_JOINT_W

#include "../luax.h"
#include "../wwrap.h"

#include "wJoint.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_DISTANCE_JOINT_BITS = (LOVE_DISTANCE_JOINT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkdistancejoint(L, idx) luax_checktype<DistanceJoint>(L, idx, "DistanceJoint", LOVE_WRAP_DISTANCE_JOINT_BITS)

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

	static const luaL_Reg DistanceJoint_mt[] = {
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

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_DISTANCE_JOINT_W
