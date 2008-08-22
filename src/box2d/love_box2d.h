/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_MOD_BOX2D_H
#define LOVE_MOD_BOX2D_H

// LOVE
#include <love/mod.h>

// Box2D
#include <Box2D.h>

// Module.
#include "World.h"
#include "Body.h"
#include "CircleShape.h"
#include "PolygonShape.h"

#include "DistanceJoint.h"
#include "MouseJoint.h"
#include "RevoluteJoint.h"
#include "PrismaticJoint.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_box2d
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

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
	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);

	/**
	* Creates a new World with with size (w,h).
	* @param w The width of the world.
	* @param h The height of the world.
	**/
	pWorld newWorld(float w, float h);

	/**
	* Creates a new Body at the specified position.
	* @param world The world to create the Body in.
	* @param x The position along the x-axis.
	* @param x The position along the y-axis.
	* @param m The mass.
	**/
	pBody newBody(pWorld world, float x, float y, float m);

	/**
	* Creates a new Body at the specified position.
	* @param world The world to create the Body in.
	* @param x The position along the x-axis.
	* @param x The position along the y-axis.
	**/
	pBody newBody(pWorld world, float x, float y);

	/**
	* Creates a new Body at (0, 0)
	* @param world The world to create the Body in.
	**/
	pBody newBody(pWorld world);

	/**
	* Creates a new CircleShape at the Body origin.
	* @param body The Body to create the Shape on.
	* @param radius The radius of the circle.
	**/
	pCircleShape newCircleShape(pBody body, float radius);

	/**
	* Creates a new CircleShape at (x,y) in local coorinates.
	* @param body The Body to create the Shape on.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param radius The radius of the circle.
	**/
	pCircleShape newCircleShape(pBody body, float x, float y, float radius);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at the local origin.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	**/
	pPolygonShape newRectangleShape(pBody body, float w, float h);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at (x,y) in local coordinates.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	**/
	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h);

	/**
	* Shorthand for creating rectangluar PolygonShapes. The rectangle
	* will be created at (x,y) in local coordinates.
	* @param x The offset along the x-axis.
	* @param y The offset along the y-axis.
	* @param w The width of the rectangle.
	* @param h The height of the rectangle.
	* @param angle The angle of the rectangle. (deg)
	**/
	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h, float angle);

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
	pDistanceJoint newDistanceJoint(pBody body1, pBody body2, float x1, float y1, float x2, float y2);

	/**
	* Creates a new MouseJoint connecting the body with an arbitrary point.
	* @param x Anchor along the x-axis. (World coordinates)
	* @param y Anchor along the y-axis. (World coordinates)
	**/
	pMouseJoint newMouseJoint(pBody body, float x, float y);

	/**
	* Creates a new RevoluteJoint connecting body1 with body2.
	* @param x Anchor along the x-axis. (World coordinates)
	* @param y Anchor along the y-axis. (World coordinates)
	**/
	pRevoluteJoint newRevoluteJoint(pBody body1, pBody body2, float x, float y);

	/**
	* Creates a new PrismaticJoint connecting body1 with body2.
	* @param x World-anchor along the x-axis.
	* @param y World-anchor along the y-axis.
	* @param ax The x-component of the world-axis.
	* @param ay The y-component of the world-axis.
	**/
	pPrismaticJoint newPrismaticJoint(pBody body1, pBody body2, float x, float y, float ax, float ay);

} // love_box2d

#endif // LOVE_MOD_BOX2D_H
