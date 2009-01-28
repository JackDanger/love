/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_DISTANCE_JOINT_H
#define LOVE_PHYSICS_BOX2D_WRAP_DISTANCE_JOINT_H

// LOVE
#include "../../wrap.h"
#include "wrap_Joint.h"
#include "DistanceJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	DistanceJoint * luax_checkdistancejoint(lua_State * L, int idx);
	int _wrap_DistanceJoint_setLength(lua_State * L);
	int _wrap_DistanceJoint_getLength(lua_State * L);
	int _wrap_DistanceJoint_setFrequency(lua_State * L);
	int _wrap_DistanceJoint_getFrequency(lua_State * L);
	int _wrap_DistanceJoint_setDamping(lua_State * L);
	int _wrap_DistanceJoint_getDamping(lua_State * L);
	int wrap_DistanceJoint_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_DISTANCE_JOINT_H
