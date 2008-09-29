#include "love_box2d.h"
#include "mod_box2d.h"

// LOVE
#include <love/Core.h>
#include <love/math.h>

#include "graham/GrahamScanConvexHull.h"

namespace love_box2d
{
	bool module_init(love::Core * core)
	{
		std::cout << "INIT love.physics [" << "Box2D" << "]" << std::endl;
		return true;
	}

	bool module_quit(love::Core * core)
	{
		std::cout << "QUIT love.physics [" << "Box2D" << "]" << std::endl;
		return true;
	}

	bool module_open(love::Core * core)
	{
		luaopen_mod_box2d(core->getL());
		return true;
	}

	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep)
	{
		b2AABB aabb;
		aabb.lowerBound.Set(lx, ly);
		aabb.upperBound.Set(ux, uy);
		pWorld w(new World(aabb, b2Vec2(gx, gy), sleep));
		return w;
	}

	pWorld newWorld(float w, float h)
	{
		return newWorld(-w, -h, w, h, 0, 0, true);
	}

	pBody newBody(pWorld world, float x, float y, float mass)
	{
		pBody body(new Body(world, b2Vec2(x, y), mass));
		return body;
	}

	pBody newBody(pWorld world, float x, float y)
	{
		pBody body(new Body(world, b2Vec2(x, y), 1));
		return body;
	}

	pBody newBody(pWorld world)
	{
		pBody body(new Body(world, b2Vec2(0, 0), 1));
		return body;
	}

	pCircleShape newCircleShape(pBody body, float radius)
	{
		return newCircleShape(body, 0, 0, radius);
	}

	pCircleShape newCircleShape(pBody body, float x, float y, float radius)
	{
		b2CircleDef def;
		def.density = 1.0f;
		def.localPosition.Set(x, y);
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.radius = radius;
		pCircleShape shape(new CircleShape(body, &def));
		return shape;
	}

	pPolygonShape newRectangleShape(pBody body, float w, float h)
	{
		return newRectangleShape(body, 0, 0, w, h, 0);
	}

	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h)
	{
		return newRectangleShape(body, x, y, w, h, 0);
	}

	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h, float angle)
	{
		b2PolygonDef def;
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.density = 1.0f;
		def.SetAsBox(w/2.0f, h/2.0f, b2Vec2(x, y), LOVE_TORAD(angle));
		pPolygonShape p(new PolygonShape(body, &def));
		return p;
	}

	int newPolygonShape(lua_State * L)
	{
		int argc = lua_gettop(L);
		int vcount = (int)(argc-1)/2;
		// 1 body + 3 vertices
		love::luax_assert_argc(L, 1 + (2 * 3));
		pBody b = mod_to_body(L, 1);

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

		pPolygonShape p(new PolygonShape(b, &def));
		mod_push_polygonshape(L, p);

		return 1;
	}

	pDistanceJoint newDistanceJoint(pBody body1, pBody body2, float x1, float y1, float x2, float y2)
	{
		b2DistanceJointDef def;
		def.localAnchor1.Set(x1, y1);
		def.localAnchor2.Set(x2, y2);
		pDistanceJoint j(new DistanceJoint(body1, body2, &def));
		return j;
	}

	pMouseJoint newMouseJoint(pBody body, float x, float y)
	{
		b2MouseJointDef def;
		def.target.Set(x, y);
		pMouseJoint j(new MouseJoint(body, &def));
		return j;
	}

	pRevoluteJoint newRevoluteJoint(pBody body1, pBody body2, float x, float y)
	{
		b2RevoluteJointDef def;
		def.localAnchor1.Set(x, y);
		pRevoluteJoint j(new RevoluteJoint(body1, body2, &def));
		return j;
	}

	pPrismaticJoint newPrismaticJoint(pBody body1, pBody body2, float x, float y, float ax, float ay)
	{
		b2PrismaticJointDef def;
		
		// Using these as temporal storage.
		def.localAnchor2.Set(x, y);
		def.localAxis1.Set(ax, ay);

		pPrismaticJoint j(new PrismaticJoint(body1, body2, &def));
		return j;
	}

} // love_box2d
