#include "SegmentShape.h"

#include "Body.h"

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

	pVector SegmentShape::getFirst()
	{
		pVector v(new Vector(segmentShape->ta));
		return v;
	}

	pVector SegmentShape::getSecond()
	{
		pVector v(new Vector(segmentShape->tb));
		return v;
	}
} // love_chipmunk

