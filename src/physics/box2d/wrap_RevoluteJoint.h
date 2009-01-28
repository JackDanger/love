/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_REVOLUTE_JOINT_H
#define LOVE_PHYSICS_BOX2D_WRAP_REVOLUTE_JOINT_H

// LOVE
#include "../../wrap.h"
#include "wrap_Joint.h"
#include "RevoluteJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	RevoluteJoint * luax_checkrevolutejoint(lua_State * L, int idx);
	int _wrap_RevoluteJoint_getAngle(lua_State * L);
	int _wrap_RevoluteJoint_getSpeed(lua_State * L);
	int _wrap_RevoluteJoint_setMotorEnabled(lua_State * L);
	int _wrap_RevoluteJoint_isMotorEnabled(lua_State * L);
	int _wrap_RevoluteJoint_setMaxMotorTorque(lua_State * L);
	int _wrap_RevoluteJoint_getMaxMotorTorque(lua_State * L);
	int _wrap_RevoluteJoint_setMotorSpeed(lua_State * L);
	int _wrap_RevoluteJoint_getMotorSpeed(lua_State * L);
	int _wrap_RevoluteJoint_getMotorTorque(lua_State * L);
	int _wrap_RevoluteJoint_setLimitsEnabled(lua_State * L);
	int _wrap_RevoluteJoint_isLimitsEnabled(lua_State * L);
	int _wrap_RevoluteJoint_setUpperLimit(lua_State * L);
	int _wrap_RevoluteJoint_setLowerLimit(lua_State * L);
	int _wrap_RevoluteJoint_setLimits(lua_State * L);
	int _wrap_RevoluteJoint_getLowerLimit(lua_State * L);
	int _wrap_RevoluteJoint_getUpperLimit(lua_State * L);
	int _wrap_RevoluteJoint_getLimits(lua_State * L);
	int wrap_RevoluteJoint_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_REVOLUTE_JOINT_H
