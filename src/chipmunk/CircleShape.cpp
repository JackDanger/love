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

	int CircleShape::getPoints(lua_State * L)
	{
		love::luax_assert_argc(L, 0);
		lua_pushnumber(L, circleShape->tc.x);
		lua_pushnumber(L, circleShape->tc.y);
		return 2;
	}

} // love_chipmunk
