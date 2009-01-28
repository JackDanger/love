/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#include "wrap_PrismaticJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	PrismaticJoint * luax_checkprismaticjoint(lua_State * L, int idx)
	{
		return luax_checktype<PrismaticJoint>(L, idx, "PrismaticJoint", LOVE_PHYSICS_PRISMATIC_JOINT_BITS);
	}

	int _wrap_PrismaticJoint_getTranslation(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getTranslation());
		return 1;
	}

	int _wrap_PrismaticJoint_getSpeed(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getSpeed());
		return 1;
	}

	int _wrap_PrismaticJoint_setMotorEnabled(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setMotorEnabled(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_isMotorEnabled(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		luax_pushboolean(L, t->isMotorEnabled());
		return 1;
	}

	int _wrap_PrismaticJoint_setMaxMotorForce(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setMaxMotorForce(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_getMaxMotorForce(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getMaxMotorForce());
		return 1;
	}

	int _wrap_PrismaticJoint_setMotorSpeed(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setMotorSpeed(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_getMotorSpeed(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getMotorSpeed());
		return 1;
	}

	int _wrap_PrismaticJoint_getMotorForce(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getMotorForce());
		return 1;
	}

	int _wrap_PrismaticJoint_setLimitsEnabled(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setLimitsEnabled(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_isLimitsEnabled(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		luax_pushboolean(L, t->isLimitsEnabled());
		return 1;
	}

	int _wrap_PrismaticJoint_setUpperLimit(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setUpperLimit(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_setLowerLimit(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setLowerLimit(arg1);
		return 0;
	}

	int _wrap_PrismaticJoint_setLimits(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setLimits(arg1, arg2);
		return 0;
	}

	int _wrap_PrismaticJoint_getLowerLimit(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getLowerLimit());
		return 1;
	}

	int _wrap_PrismaticJoint_getUpperLimit(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_pushnumber(L, t->getUpperLimit());
		return 1;
	}

	int _wrap_PrismaticJoint_getLimits(lua_State * L)
	{
		PrismaticJoint * t = luax_checkprismaticjoint(L, 1);
		lua_remove(L, 1);
		return t->getLimits(L);
	}

	static const luaL_Reg wrap_PrismaticJoint_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getTranslation", _wrap_PrismaticJoint_getTranslation },
		{ "getSpeed", _wrap_PrismaticJoint_getSpeed },
		{ "setMotorEnabled", _wrap_PrismaticJoint_setMotorEnabled },
		{ "isMotorEnabled", _wrap_PrismaticJoint_isMotorEnabled },
		{ "setMaxMotorForce", _wrap_PrismaticJoint_setMaxMotorForce },
		{ "getMaxMotorForce", _wrap_PrismaticJoint_getMaxMotorForce },
		{ "setMotorSpeed", _wrap_PrismaticJoint_setMotorSpeed },
		{ "getMotorSpeed", _wrap_PrismaticJoint_getMotorSpeed },
		{ "getMotorForce", _wrap_PrismaticJoint_getMotorForce },
		{ "setLimitsEnabled", _wrap_PrismaticJoint_setLimitsEnabled },
		{ "isLimitsEnabled", _wrap_PrismaticJoint_isLimitsEnabled },
		{ "setUpperLimit", _wrap_PrismaticJoint_setUpperLimit },
		{ "setLowerLimit", _wrap_PrismaticJoint_setLowerLimit },
		{ "setLimits", _wrap_PrismaticJoint_setLimits },
		{ "getLowerLimit", _wrap_PrismaticJoint_getLowerLimit },
		{ "getUpperLimit", _wrap_PrismaticJoint_getUpperLimit },
		{ "getLimits", _wrap_PrismaticJoint_getLimits },
		// From Joint.
		{ "getType", _wrap_Joint_getType },
		{ "getAnchors", _wrap_Joint_getAnchors },
		{ "getReactionForce", _wrap_Joint_getReactionForce },
		{ "getReactionTorque", _wrap_Joint_getReactionTorque },
		{ "setCollideConnected", _wrap_Joint_setCollideConnected },
		{ "getCollideConnected", _wrap_Joint_getCollideConnected },
		{ 0, 0 }
	};

	int wrap_PrismaticJoint_open(lua_State * L)
	{
		luax_register_type(L, "PrismaticJoint", wrap_PrismaticJoint_functions);
		return 0;
	}

} // box2d
} // physics
} // love
