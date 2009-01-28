/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_PHYSICS_H
#define LOVE_PHYSICS_BOX2D_WRAP_PHYSICS_H

// LOVE
#include "../../wrap.h"
#include "wrap_World.h"
#include "wrap_Contact.h"
#include "wrap_Body.h"
#include "wrap_Shape.h"
#include "wrap_CircleShape.h"
#include "wrap_PolygonShape.h"
#include "wrap_Joint.h"
#include "wrap_MouseJoint.h"
#include "wrap_DistanceJoint.h"
#include "wrap_PrismaticJoint.h"
#include "wrap_RevoluteJoint.h"
#include "Physics.h"

namespace love
{
namespace physics
{
namespace box2d
{
	int _wrap_newWorld(lua_State * L);
	int _wrap_newBody(lua_State * L);
	int _wrap_newCircleShape(lua_State * L);
	int _wrap_newRectangleShape(lua_State * L);
	int _wrap_newPolygonShape(lua_State * L);;
	int _wrap_newDistanceJoint(lua_State * L);
	int _wrap_newMouseJoint(lua_State * L);
	int _wrap_newRevoluteJoint(lua_State * L);
	int _wrap_newPrismaticJoint(lua_State * L);
	int wrap_Physics_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_PHYSICS_H
