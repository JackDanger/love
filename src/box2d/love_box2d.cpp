#include "love_box2d.h"
#include "mod_box2d.h"

// LOVE
#include <love/Core.h>


namespace love_box2d
{
	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.physics [" << "Box2D" << "]" << std::endl;
		
		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.physics [" << "Box2D" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_box2d(s);
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

	pBody newBody(pWorld world, float x, float y, float mass)
	{
		pBody body(new Body(world, b2Vec2(x, y), mass));
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

	int newPolygonShape(lua_State * L)
	{
		int argc = lua_gettop(L);
		love::luax_assert_argc(L, 7);
		pBody b = mod_to_body(L, 1);

		b2PolygonDef def;
		def.vertexCount = (int)(argc-1)/2;
		def.friction = 0.5f;
		def.restitution = 0.1f;
		def.density = 1.0f;

		for(int i = 0;i<def.vertexCount;i++)
		{
			float y = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			float x = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			def.vertices[i].Set(x, y);
		}

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
