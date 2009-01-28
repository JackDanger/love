/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_PRISMATIC_JOINT_H
#define LOVE_PHYSICS_BOX2D_WRAP_PRISMATIC_JOINT_H

// LOVE
#include "../../wrap.h"
#include "wrap_Joint.h"
#include "PrismaticJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	PrismaticJoint * luax_checkprismaticjoint(lua_State * L, int idx);
	int _wrap_PrismaticJoint_getTranslation(lua_State * L);
	int _wrap_PrismaticJoint_getSpeed(lua_State * L);
	int _wrap_PrismaticJoint_setMotorEnabled(lua_State * L);
	int _wrap_PrismaticJoint_isMotorEnabled(lua_State * L);
	int _wrap_PrismaticJoint_setMaxMotorForce(lua_State * L);
	int _wrap_PrismaticJoint_getMaxMotorForce(lua_State * L);
	int _wrap_PrismaticJoint_setMotorSpeed(lua_State * L);
	int _wrap_PrismaticJoint_getMotorSpeed(lua_State * L);
	int _wrap_PrismaticJoint_getMotorForce(lua_State * L);
	int _wrap_PrismaticJoint_setLimitsEnabled(lua_State * L);
	int _wrap_PrismaticJoint_isLimitsEnabled(lua_State * L);
	int _wrap_PrismaticJoint_setUpperLimit(lua_State * L);
	int _wrap_PrismaticJoint_setLowerLimit(lua_State * L);
	int _wrap_PrismaticJoint_setLimits(lua_State * L);
	int _wrap_PrismaticJoint_getLowerLimit(lua_State * L);
	int _wrap_PrismaticJoint_getUpperLimit(lua_State * L);
	int _wrap_PrismaticJoint_getLimits(lua_State * L);
	int wrap_PrismaticJoint_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_PRISMATIC_JOINT_H
