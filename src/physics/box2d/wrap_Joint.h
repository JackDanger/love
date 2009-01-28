/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_JOINT_H
#define LOVE_PHYSICS_BOX2D_WRAP_JOINT_H

// LOVE
#include "../../wrap.h"
#include "Joint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Joint * luax_checkjoint(lua_State * L, int idx);
	int _wrap_Joint_getType(lua_State * L);
	int _wrap_Joint_getAnchors(lua_State * L);
	int _wrap_Joint_getReactionForce(lua_State * L);
	int _wrap_Joint_getReactionTorque(lua_State * L);
	int _wrap_Joint_setCollideConnected(lua_State * L);
	int _wrap_Joint_getCollideConnected(lua_State * L);
	int wrap_Joint_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_JOINT_H
