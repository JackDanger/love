/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_WORLD_H
#define LOVE_PHYSICS_BOX2D_WRAP_WORLD_H

// LOVE
#include "../../wrap.h"
#include "World.h"

namespace love
{
namespace physics
{
namespace box2d
{
	World * luax_checkworld(lua_State * L, int idx);
	int _wrap_World_update(lua_State * L);
	int _wrap_World_setCallback(lua_State * L);
	int _wrap_World_getCallback(lua_State * L);
	int _wrap_World_setGravity(lua_State * L);
	int _wrap_World_getGravity(lua_State * L);
	int _wrap_World_setAllowSleep(lua_State * L);
	int _wrap_World_isAllowSleep(lua_State * L);
	int _wrap_World_getBodyCount(lua_State * L);
	int _wrap_World_getJointCount(lua_State * L);
	int wrap_World_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_WORLD_H
