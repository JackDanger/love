/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#include "love_box2d.h"

#include "../liblove/math.h"

#include "graham/GrahamScanConvexHull.h"

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE box2d
#define LOVE_WRAP_BITS LOVE_BOX2D_BITS
#include "../liblove/physics/wphysics.h"

namespace love
{
namespace box2d
{

	int luainfo(lua_State * L)
	{
		luax_register_info(L,
			"box2d",
			"physics",
			"Box2D Physics Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		luareg(L);
		luax_register_gc(L, "box2d", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		return 0;
	}


	World * newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep)
	{
		b2AABB aabb;
		aabb.lowerBound.Set(lx, ly);
		aabb.upperBound.Set(ux, uy);
		return new World(aabb, b2Vec2(gx, gy), sleep);
	}

	World * newWorld(float w, float h)
	{
		return newWorld(-w, -h, w, h, 0, 0, true);
	}

	Body * newBody(World * world, float x, float y, float mass)
	{
		return new Body(world, b2Vec2(x, y), mass);
	}

	Body * newBody(World * world, float x, float y)
	{
		return new Body(world, b2Vec2(x, y), 1);
	}

	Body * newBody(World * world)
	{
		return new Body(world, b2Vec2(0, 0), 1);
	}

	CircleShape * newCircleShape(Body * body, float radius)
	{
		return newCircleShape(body, 0, 0, radius);
	}

	CircleShape * newCircleShape(Body * body, float x, float y, float radius)
	{
		b2CircleDef def;
		def.density = 1.0f;
		def.localPosition.Set(x, y);
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.radius = radius;
		return new CircleShape(body, &def);
	}

	PolygonShape * newRectangleShape(Body * body, float w, float h)
	{
		return newRectangleShape(body, 0, 0, w, h, 0);
	}

	PolygonShape * newRectangleShape(Body * body, float x, float y, float w, float h)
	{
		return newRectangleShape(body, x, y, w, h, 0);
	}

	PolygonShape * newRectangleShape(Body * body, float x, float y, float w, float h, float angle)
	{
		b2PolygonDef def;
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.density = 1.0f;
		def.SetAsBox(w/2.0f, h/2.0f, b2Vec2(x, y), LOVE_TORAD(angle));
		return new PolygonShape(body, &def);
	}

	int newPolygonShape(lua_State * L)
	{
		int argc = lua_gettop(L);
		int vcount = (int)(argc-1)/2;
		// 1 body + 3 vertices
		love::luax_assert_argc(L, 1 + (2 * 3));

		Body * b = luax_checktype<Body>(L, 1, "Body", LOVE_BODY_BITS | LOVE_BOX2D_BITS);

		b2PolygonDef def;
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.density = 1.0f;

		std::vector<point2d> points(def.vertexCount);
		std::vector<point2d> convex_hull;

		for(int i = 0;i<vcount;i++)
		{
			float x = (float)lua_tonumber(L, -2);
			float y = (float)lua_tonumber(L, -1);
			point2d tmp(x, y);
			points.push_back(tmp);
			lua_pop(L, 2);
		}

		// Compute convex hull.
		GrahamScanConvexHull()(points, convex_hull);

		def.vertexCount = (int32)convex_hull.size();

		if(def.vertexCount < 3)
			return luaL_error(L, "Polygon degenerated to less than three points.");

		for(int i = 0;i<def.vertexCount;i++)
			def.vertices[def.vertexCount-i-1].Set((float)convex_hull[i].x, (float)convex_hull[i].y);

		PolygonShape * p = new PolygonShape(b, &def);

		luax_newtype(L, "PolygonShape", LOVE_POLYGON_SHAPE_BITS | LOVE_BOX2D_BITS, (void*)p);

		return 1;
	}

	DistanceJoint * newDistanceJoint(Body * body1, Body * body2, float x1, float y1, float x2, float y2)
	{
		b2DistanceJointDef def;
		def.localAnchor1.Set(x1, y1);
		def.localAnchor2.Set(x2, y2);
		return new DistanceJoint(body1, body2, &def);
	}

	MouseJoint * newMouseJoint(Body * body, float x, float y)
	{
		b2MouseJointDef def;
		def.target.Set(x, y);
		return new MouseJoint(body, &def);
	}

	RevoluteJoint * newRevoluteJoint(Body * body1, Body * body2, float x, float y)
	{
		b2RevoluteJointDef def;
		def.localAnchor1.Set(x, y);
		return new RevoluteJoint(body1, body2, &def);
	}

	PrismaticJoint * newPrismaticJoint(Body * body1, Body * body2, float x, float y, float ax, float ay)
	{
		b2PrismaticJointDef def;
		
		// Using these as temporal storage.
		def.localAnchor2.Set(x, y);
		def.localAxis1.Set(ax, ay);

		return new PrismaticJoint(body1, body2, &def);
	}

} // box2d
} // love
