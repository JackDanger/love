#include "CircleShape.h"

#include "Body.h"

namespace love_chipmunk
{
	CircleShape::CircleShape(boost::shared_ptr<Body> body)
		: Shape(body)
	{ }

	CircleShape::~CircleShape()
	{ }

	DynamicCircleShape::DynamicCircleShape(boost::shared_ptr<Body> body, float r)
		: CircleShape(body)
	{
		circleShape = cpCircleShapeAlloc();
		cpCircleShapeInit(circleShape, body->get(), r, cpvzero);
		shape = (cpShape*)circleShape;
		shape->e = 0.5f;
		shape->u = 0.5f;
		cpSpaceAddShape(body->space->space, shape);
	}

	DynamicCircleShape::~DynamicCircleShape()
	{
		cpSpaceRemoveShape(body->space->space, (cpShape*)circleShape);
		cpShapeFree((cpShape*)circleShape);
		circleShape = 0;
	}

} // love_chipmunk
