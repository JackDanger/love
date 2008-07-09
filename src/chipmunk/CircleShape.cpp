#include "CircleShape.h"

#include "Body.h"

namespace love_chipmunk
{
	CircleShape::CircleShape(boost::shared_ptr<Body> body, float r)
		: Shape(body)
	{ 
		circleShape = cpCircleShapeAlloc();
		cpCircleShapeInit(circleShape, body->get(), r, cpvzero);
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

} // love_chipmunk
