/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_REVOLUTE_JOINT_W
#define LOVE_REVOLUTE_JOINT_W

#include "../luax.h"
#include "../wwrap.h"

#include "wJoint.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_REVOLUTE_JOINT_BITS = (LOVE_REVOLUTE_JOINT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkrevolutejoint(L, idx) luax_checktype<RevoluteJoint>(L, idx, "RevoluteJoint", LOVE_WRAP_REVOLUTE_JOINT_BITS)

	int _wrap_RevoluteJoint_getAngle(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getAngle());
		return 1;
	}

	int _wrap_RevoluteJoint_getSpeed(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getSpeed());
		return 1;
	}

	int _wrap_RevoluteJoint_setMotorEnabled(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setMotorEnabled(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_isMotorEnabled(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		luax_pushboolean(L, t->isMotorEnabled());
		return 1;
	}

	int _wrap_RevoluteJoint_setMaxMotorTorque(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setMaxMotorTorque(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_getMaxMotorTorque(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getMaxMotorTorque());
		return 1;
	}

	int _wrap_RevoluteJoint_setMotorSpeed(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setMotorSpeed(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_getMotorSpeed(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getMotorSpeed());
		return 1;
	}

	int _wrap_RevoluteJoint_getMotorTorque(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getMotorTorque());
		return 1;
	}

	int _wrap_RevoluteJoint_setLimitsEnabled(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setLimitsEnabled(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_isLimitsEnabled(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		luax_pushboolean(L, t->isLimitsEnabled());
		return 1;
	}

	int _wrap_RevoluteJoint_setUpperLimit(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setUpperLimit(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_setLowerLimit(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setLowerLimit(arg1);
		return 0;
	}

	int _wrap_RevoluteJoint_setLimits(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setLimits(arg1, arg2);
		return 0;
	}

	int _wrap_RevoluteJoint_getLowerLimit(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getLowerLimit());
		return 1;
	}

	int _wrap_RevoluteJoint_getUpperLimit(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_pushnumber(L, t->getUpperLimit());
		return 1;
	}

	int _wrap_RevoluteJoint_getLimits(lua_State * L)
	{
		RevoluteJoint * t = luax_checkrevolutejoint(L, 1);
		lua_remove(L, 1);
		return t->getLimits(L);
	}

	static const luaL_Reg RevoluteJoint_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },

		{ "getAngle", _wrap_RevoluteJoint_getAngle },
		{ "getSpeed", _wrap_RevoluteJoint_getSpeed },
		{ "setMotorEnabled", _wrap_RevoluteJoint_setMotorEnabled },
		{ "isMotorEnabled", _wrap_RevoluteJoint_isMotorEnabled },
		{ "setMaxMotorTorque", _wrap_RevoluteJoint_setMaxMotorTorque },
		{ "getMaxMotorTorque", _wrap_RevoluteJoint_getMaxMotorTorque },
		{ "setMotorSpeed", _wrap_RevoluteJoint_setMotorSpeed },
		{ "getMotorSpeed", _wrap_RevoluteJoint_getMotorSpeed },
		{ "getMotorTorque", _wrap_RevoluteJoint_getMotorTorque },
		{ "setLimitsEnabled", _wrap_RevoluteJoint_setLimitsEnabled },
		{ "isLimitsEnabled", _wrap_RevoluteJoint_isLimitsEnabled },
		{ "setUpperLimit", _wrap_RevoluteJoint_setUpperLimit },
		{ "setLowerLimit", _wrap_RevoluteJoint_setLowerLimit },
		{ "setLimits", _wrap_RevoluteJoint_setLimits },
		{ "getLowerLimit", _wrap_RevoluteJoint_getLowerLimit },
		{ "getUpperLimit", _wrap_RevoluteJoint_getUpperLimit },
		{ "getLimits", _wrap_RevoluteJoint_getLimits },

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

#endif // LOVE_REVOLUTE_JOINT_W
