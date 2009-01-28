/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_SHAPE_H
#define LOVE_PHYSICS_BOX2D_WRAP_SHAPE_H

// LOVE
#include "../../wrap.h"
#include "Shape.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Shape * luax_checkshape(lua_State * L, int idx);
	int _wrap_Shape_getType(lua_State * L);
	int _wrap_Shape_setFriction(lua_State * L);
	int _wrap_Shape_setRestitution(lua_State * L);
	int _wrap_Shape_setDensity(lua_State * L);
	int _wrap_Shape_setSensor(lua_State * L);
	int _wrap_Shape_getFriction(lua_State * L);
	int _wrap_Shape_getRestituion(lua_State * L);
	int _wrap_Shape_getDensity(lua_State * L);
	int _wrap_Shape_isSensor(lua_State * L);
	int _wrap_Shape_getBody(lua_State * L);
	int _wrap_Shape_testPoint(lua_State * L);
	int _wrap_Shape_testSegment(lua_State * L);
	int _wrap_Shape_setCategoryBits(lua_State * L);
	int _wrap_Shape_getCategoryBits(lua_State * L);
	int _wrap_Shape_setMaskBits(lua_State * L);
	int _wrap_Shape_getMaskBits(lua_State * L);
	int _wrap_Shape_setCategory(lua_State * L);
	int _wrap_Shape_getCategory(lua_State * L);
	int _wrap_Shape_setMask(lua_State * L);
	int _wrap_Shape_getMask(lua_State * L);
	int _wrap_Shape_setData(lua_State * L);
	int _wrap_Shape_getData(lua_State * L);
	int _wrap_Shape_getBoundingBox(lua_State * L);
	int wrap_Shape_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_SHAPE_H
