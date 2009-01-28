/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_POLYGON_SHAPE_H
#define LOVE_PHYSICS_BOX2D_WRAP_POLYGON_SHAPE_H

// LOVE
#include "../../wrap.h"
#include "wrap_Shape.h"
#include "PolygonShape.h"

namespace love
{
namespace physics
{
namespace box2d
{
	PolygonShape * luax_checkpolygonshape(lua_State * L, int idx);
	int _wrap_PolygonShape_getPoints(lua_State * L);
	int wrap_PolygonShape_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_POLYGON_SHAPE_H
