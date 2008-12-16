/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#ifndef LOVE_PHYSICS_W
#define LOVE_PHYSICS_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wWorld.h"
#include "wContact.h"
#include "wBody.h"
#include "wShape.h"
#include "wCircleShape.h"
#include "wPolygonShape.h"
#include "wJoint.h"
#include "wMouseJoint.h"
#include "wDistanceJoint.h"
#include "wPrismaticJoint.h"
#include "wRevoluteJoint.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	
	int _wrap_newWorld(lua_State * L)
	{
		if(lua_gettop(L) == 2)
		{
			float x = (float)luaL_checknumber(L, 1);
			float y = (float)luaL_checknumber(L, 2);
			World * w = newWorld(x, y);
			luax_newtype(L, "World", LOVE_WRAP_WORLD_BITS, (void*)w);
			return 1;
		}
		else if(lua_gettop(L) == 6)
		{
			float lx = (float)luaL_checknumber(L, 1);
			float ly = (float)luaL_checknumber(L, 2);
			float ux = (float)luaL_checknumber(L, 3);
			float uy = (float)luaL_checknumber(L, 4);
			float gx = (float)luaL_checknumber(L, 5);
			float gy = (float)luaL_checknumber(L, 6);
			bool sleep = luax_toboolean(L, 7);
			World * w = newWorld(lx, ly, ux, uy, gx, gy, sleep);
			luax_newtype(L, "World", LOVE_WRAP_WORLD_BITS, (void*)w);
			return 1;
		}
		else
			return luaL_error(L, "Incorrect number of parameters");
	}

	int _wrap_newBody(lua_State * L)
	{
		World * world = luax_checktype<World>(L, 1, "World", LOVE_WRAP_WORLD_BITS);
		float x = (float)luaL_optnumber(L, 2, 0.0);
		float y = (float)luaL_optnumber(L, 3, 0.0);
		float m = (float)luaL_optnumber(L, 4, 1.0);
		Body * body = newBody(world, x, y, m);
		luax_newtype(L, "Body", LOVE_WRAP_BODY_BITS, (void*)body);
		return 1;
	}

	int _wrap_newCircleShape(lua_State * L)
	{
		Body * body = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		int top = lua_gettop(L);

		if(top == 2)
		{
			float radius = (float)luaL_checknumber(L, 2);
			CircleShape * shape = newCircleShape(body, radius);
			luax_newtype(L, "CircleShape", LOVE_WRAP_CIRCLE_SHAPE_BITS, (void*)shape);
			return 1;
		}
		else if(top == 4)
		{
			float x = (float)luaL_checknumber(L, 2);
			float y = (float)luaL_checknumber(L, 3);
			float radius = (float)luaL_checknumber(L, 4);
			CircleShape * shape = newCircleShape(body, x, y, radius);
			luax_newtype(L, "CircleShape", LOVE_WRAP_CIRCLE_SHAPE_BITS, (void*)shape);
			return 1;
		}
		else
			return luaL_error(L, "Incorrect number of parameters");
	}

	int _wrap_newRectangleShape(lua_State * L)
	{
		Body * body = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		int top = lua_gettop(L);

		if(top == 3)
		{
			float w = (float)luaL_checknumber(L, 2);
			float h = (float)luaL_checknumber(L, 3);
			PolygonShape * shape = newRectangleShape(body, w, h);
			luax_newtype(L, "PolygonShape", LOVE_WRAP_POLYGON_SHAPE_BITS, (void*)shape);
			return 1;
		}
		else if(top == 5 || top == 6)
		{
			float x = (float)luaL_checknumber(L, 2);
			float y = (float)luaL_checknumber(L, 3);
			float w = (float)luaL_checknumber(L, 4);
			float h = (float)luaL_checknumber(L, 5);
			float angle = (float)luaL_optnumber(L, 6, 0);
			PolygonShape * shape = newRectangleShape(body, x, y, w, h, 0);
			luax_newtype(L, "PolygonShape", LOVE_WRAP_POLYGON_SHAPE_BITS, (void*)shape);
			return 1;
		}
		else
			return luaL_error(L, "Incorrect number of parameters");
	}

	// newPolygonShape

	int _wrap_newDistanceJoint(lua_State * L)
	{
		Body * body1 = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		Body * body2 = luax_checktype<Body>(L, 2, "Body", LOVE_WRAP_BODY_BITS);
		float x1 = (float)luaL_checknumber(L, 3);
		float y1 = (float)luaL_checknumber(L, 4);
		float x2 = (float)luaL_checknumber(L, 5);
		float y2 = (float)luaL_checknumber(L, 6);
		DistanceJoint * j = newDistanceJoint(body1, body2, x1, y1, x2, y2);
		luax_newtype(L, "PolygonShape", LOVE_WRAP_DISTANCE_JOINT_BITS, (void*)j);
		return 1;
	}

	int _wrap_newMouseJoint(lua_State * L)
	{
		Body * body = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		MouseJoint * j = newMouseJoint(body, x, y);
		luax_newtype(L, "MouseJoint", LOVE_WRAP_MOUSE_JOINT_BITS, (void*)j);
		return 1;
	}

	int _wrap_newRevoluteJoint(lua_State * L)
	{
		Body * body1 = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		Body * body2 = luax_checktype<Body>(L, 2, "Body", LOVE_WRAP_BODY_BITS);
		float x = (float)luaL_checknumber(L, 3);
		float y = (float)luaL_checknumber(L, 4);
		RevoluteJoint * j = newRevoluteJoint(body1, body2, x, y);
		luax_newtype(L, "RevoluteJoint", LOVE_WRAP_REVOLUTE_JOINT_BITS, (void*)j);
		return 1;
	}

	int _wrap_newPrismaticJoint(lua_State * L)
	{
		Body * body1 = luax_checktype<Body>(L, 1, "Body", LOVE_WRAP_BODY_BITS);
		Body * body2 = luax_checktype<Body>(L, 2, "Body", LOVE_WRAP_BODY_BITS);
		float x = (float)luaL_checknumber(L, 3);
		float y = (float)luaL_checknumber(L, 4);
		float ax = (float)luaL_checknumber(L, 5);
		float ay = (float)luaL_checknumber(L, 6);
		PrismaticJoint * j = newPrismaticJoint(body1, body2, x, y, ax, ay);
		luax_newtype(L, "PrismaticJoint", LOVE_WRAP_PRISMATIC_JOINT_BITS, (void*)j);
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "newWorld", _wrap_newWorld },
		{ "newBody", _wrap_newBody },
		{ "newCircleShape", _wrap_newCircleShape },
		{ "newRectangleShape", _wrap_newRectangleShape },
		{ "newPolygonShape", newPolygonShape },
		{ "newDistanceJoint", _wrap_newDistanceJoint },
		{ "newMouseJoint", _wrap_newMouseJoint },
		{ "newRevoluteJoint", _wrap_newRevoluteJoint },
		{ "newPrismaticJoint", _wrap_newPrismaticJoint },
		{ 0, 0 },
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "physics", module_fn);

		luax_register_type(L, "World", World_mt);
		luax_register_type(L, "Contact", Contact_mt);
		luax_register_type(L, "Body", Body_mt);

		luax_register_type(L, "Shape", Shape_mt);
		luax_register_type(L, "CircleShape", CircleShape_mt);
		luax_register_type(L, "PolygonShape", PolygonShape_mt);

		luax_register_type(L, "Joint", Joint_mt);
		luax_register_type(L, "MouseJoint", MouseJoint_mt);
		luax_register_type(L, "DistanceJoint", DistanceJoint_mt);
		luax_register_type(L, "PrismaticJoint", PrismaticJoint_mt);
		luax_register_type(L, "RevoluteJoint", RevoluteJoint_mt);
		return 0;
	}

} // LOVE_WRAP_NAMESPACE
} // love

#endif // LOVE_PHYSICS_W
