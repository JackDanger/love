#include "SegmentShape.h"

#include "Body.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	SegmentShape::SegmentShape(boost::shared_ptr<Body> body, cpVect v1, cpVect v2)
		: Shape(body)
	{
		segmentShape = cpSegmentShapeAlloc();
		cpSegmentShapeInit(segmentShape, body->body, v1, v2, 1.0f);
		shape = (cpShape*)segmentShape;
		shape->e = 0.5f;
		shape->u = 0.5f;

		if(body->isDynamic())
			cpSpaceAddShape(body->space->space, shape);
		else
			cpSpaceAddStaticShape(body->space->space, shape);
	}

	SegmentShape::~SegmentShape()
	{
		if(body->isDynamic())
			cpSpaceRemoveShape(body->space->space, (cpShape*)segmentShape);
		else
			cpSpaceRemoveStaticShape(body->space->space, (cpShape*)segmentShape);

		cpShapeFree((cpShape*)segmentShape);
		segmentShape = 0;
	}

	int _SegmentShape_setData(lua_State * L)
	{
		if(lua_gettop(L) != 2) return luaL_error(L, "Incorrect number of parameters.");
		pSegmentShape p = mod_to_segmentshape(L, 1);
		lua_getglobal(L, "love");
		lua_getfield(L, -1, "refs");
		lua_pushvalue(L, -3);
		int ref = luaL_ref(L, -2);
		p->setData(ref);
		return 0;
	}

	int _SegmentShape_getData(lua_State * L)
	{
		if(lua_gettop(L) != 1) return luaL_error(L, "Incorrect number of parameters.");
		pSegmentShape p = mod_to_segmentshape(L, 1);

		int ref = p->getData();

		if(ref==LUA_REFNIL)
			return 0;

		lua_getglobal(L, "love");
		lua_getfield(L, -1, "refs");
		lua_rawgeti(L, -1, ref);
		return 1;
	}

	int _SegmentShape_getPoints(lua_State * L)
	{
		if(lua_gettop(L) != 1) return luaL_error(L, "Incorrect number of parameters.");
		pSegmentShape p = mod_to_segmentshape(L, 1);

		lua_pushnumber(L, p->segmentShape->ta.x);
		lua_pushnumber(L, p->segmentShape->ta.y);
		lua_pushnumber(L, p->segmentShape->tb.x);
		lua_pushnumber(L, p->segmentShape->tb.y);
		return 4;
	}

} // love_chipmunk

