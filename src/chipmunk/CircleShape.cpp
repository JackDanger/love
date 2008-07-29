#include "CircleShape.h"

#include "Body.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	CircleShape::CircleShape(boost::shared_ptr<Body> body, float r, float x, float y)
		: Shape(body)
	{ 
		circleShape = cpCircleShapeAlloc();
		cpCircleShapeInit(circleShape, body->get(), r, cpv(x, y));
		shape = (cpShape*)circleShape;
		shape->e = 0.5f;
		shape->u = 0.5f;

		if(body->isDynamic())
			cpSpaceAddShape(body->space->space, shape);
		else
			cpSpaceAddStaticShape(body->space->space, shape);		
	}

	CircleShape::~CircleShape()
	{ 
		if(body->isDynamic())
			cpSpaceRemoveShape(body->space->space, (cpShape*)circleShape);
		else
			cpSpaceRemoveStaticShape(body->space->space, (cpShape*)circleShape);

		cpShapeFree((cpShape*)circleShape);
		circleShape = 0;
	}

	int _CircleShape_setData(lua_State * L)
	{
		if(lua_gettop(L) != 2) return luaL_error(L, "Incorrect number of parameters.");
		pCircleShape p = mod_to_circleshape(L, 1);
		lua_getglobal(L, "love");
		lua_getfield(L, -1, "refs");
		lua_pushvalue(L, -3);
		int ref = luaL_ref(L, -2);
		p->setData(ref);
		return 0;
	}

	int _CircleShape_getData(lua_State * L)
	{
		if(lua_gettop(L) != 1) return luaL_error(L, "Incorrect number of parameters.");
		pCircleShape p = mod_to_circleshape(L, 1);

		int ref = p->getData();

		if(ref==LUA_REFNIL)
			return 0;

		lua_getglobal(L, "love");
		lua_getfield(L, -1, "refs");
		lua_rawgeti(L, -1, ref);
		return 1;
	}

	int _CircleShape_getPoint(lua_State * L)
	{
		if(lua_gettop(L) != 1) return luaL_error(L, "Incorrect number of parameters.");
		pCircleShape p = mod_to_circleshape(L, 1);
		lua_pushnumber(L, p->circleShape->tc.x);
		lua_pushnumber(L, p->circleShape->tc.y);
		return 2;
	}

} // love_chipmunk
