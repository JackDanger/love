/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_MOUSE_JOINT_H
#define LOVE_PHYSICS_BOX2D_WRAP_MOUSE_JOINT_H

// LOVE
#include "../../wrap.h"
#include "wrap_Joint.h"
#include "MouseJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	MouseJoint * luax_checkmousejoint(lua_State * L, int idx);
	int _wrap_MouseJoint_setTarget(lua_State * L);
	int _wrap_MouseJoint_getTarget(lua_State * L);
	int _wrap_MouseJoint_setMaxForce(lua_State * L);
	int _wrap_MouseJoint_getMaxForce(lua_State * L);
	int wrap_MouseJoint_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_MOUSE_JOINT_H
