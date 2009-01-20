/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#ifndef LOVE_MODULE_BOX2D_H
#define LOVE_MODULE_BOX2D_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/luax.h"
#include "../liblove/types.h"

// Module
#include "World.h"
#include "Contact.h"
#include "Body.h"
#include "Shape.h"
#include "CircleShape.h"
#include "PolygonShape.h"
#include "Joint.h"
#include "MouseJoint.h"
#include "DistanceJoint.h"
#include "PrismaticJoint.h"
#include "RevoluteJoint.h"

namespace love
{
namespace box2d
{
	// Standard function.
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* Creates a new World.
	* @param lx Lower bound on the x-axis.
	* @param ly Lower bound on the y-axis.
	* @param ux Upper bound on the x-axis.
	* @param uy Upper bound on the y-axis.
	* @param gx Gravity along x-axis.
	* @param gy Gravity along y-axis.
	* @param sleep Whether the World allows sleep.
	**/
	World * newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);

	/**
	* Creates a new World with with size (w,h).
	* @param w The width of the world.
	* @param h The height of the world.
	**/
	World * newWorld(float w, float h);

	/**
	* Creates a new Body at the specified position.
	* @param world The world to create the Body in.
	* @param x The position along the x-axis.
	* @param x The position along the y-axis.
	* @param m The mass.
	**/
	Body * newBody(World * world, float x, float y, float m);

	/**
	* Creates a new Body at the specified position.
	* @param world The world to create the Body in.
	* @param x The position along the x-axis.
	* @param x The position along the y-axis.
	**/
	Body * newBody(World * world, float x, float y);

	/**
	* Creates a new Body at (0, 0)
	* @param world The world to create the Body in.
	**/
	Body * newBody(World * world);

	/**
	* Creates a new CircleShape at the Body origin.
	* @param body The Body to create the Shape on.
	* @param radius The radius of the circle.
	**/
	CircleShape * newCircleShape(Body * body, float radius);

	/**
	* Creates a new CircleShape at (x,y) in local coorinates.
	* @param body The Body to create the Shape on.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param radius The radius of the circle.
	**/
	CircleShape * newCircleShape(Body * body, float x, float y, float radius);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at the local origin.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	**/
	PolygonShape * newRectangleShape(Body * body, float w, float h);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at (x,y) in local coordinates.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	**/
	PolygonShape * newRectangleShape(Body * body, float x, float y, float w, float h);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at (x,y) in local coordinates.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	* @param angle The angle of the rectangle. (deg)
	**/
	PolygonShape * newRectangleShape(Body * body, float x, float y, float w, float h, float angle);

	/**
	* Creates a new PolygonShape.
	* @param body The body to create this shape on.
	* @param ... A variable number of vertices.
	**/
	int newPolygonShape(lua_State * L);

	/**
	* Creates a new DistanceJoint connecting body1 with body2.
	* @param x1 Anchor1 along the x-axis. (World coordinates)
	* @param y1 Anchor1 along the y-axis. (World coordinates)
	* @param x2 Anchor2 along the x-axis. (World coordinates)
	* @param y2 Anchor2 along the y-axis. (World coordinates)
	**/
	DistanceJoint * newDistanceJoint(Body * body1, Body * body2, float x1, float y1, float x2, float y2);

	/**
	* Creates a new MouseJoint connecting the body with an arbitrary point.
	* @param x Anchor along the x-axis. (World coordinates)
	* @param y Anchor along the y-axis. (World coordinates)
	**/
	MouseJoint * newMouseJoint(Body * body, float x, float y);

	/**
	* Creates a new RevoluteJoint connecting body1 with body2.
	* @param x Anchor along the x-axis. (World coordinates)
	* @param y Anchor along the y-axis. (World coordinates)
	**/
	RevoluteJoint * newRevoluteJoint(Body * body1, Body * body2, float x, float y);

	/**
	* Creates a new PrismaticJoint connecting body1 with body2.
	* @param x World-anchor along the x-axis.
	* @param y World-anchor along the y-axis.
	* @param ax The x-component of the world-axis.
	* @param ay The y-component of the world-axis.
	**/
	PrismaticJoint * newPrismaticJoint(Body * body1, Body * body2, float x, float y, float ax, float ay);


} // box2d
} // love

#endif // LOVE_MODULE_BOX2D_H
