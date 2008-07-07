#include "SegmentShape.h"

#include "Body.h"

namespace love_chipmunk
{
	SegmentShape::SegmentShape(boost::shared_ptr<Body> body)
		: Shape(body)
	{
	}

	SegmentShape::~SegmentShape()
	{
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

	DynamicSegmentShape::DynamicSegmentShape(boost::shared_ptr<Body> body, float x1, float y1, float x2, float y2)
		: SegmentShape(body)
	{
		segmentShape = cpSegmentShapeAlloc();
		cpSegmentShapeInit(segmentShape, body->body, cpv(x1, y1), cpv(x2, y2), 1.0f);
		shape = (cpShape*)segmentShape;
		shape->e = 0.5f;
		shape->u = 0.5f;
		cpSpaceAddShape(body->space->space, shape);
	}

	DynamicSegmentShape::~DynamicSegmentShape()
	{
		cpSpaceRemoveShape(body->space->space, (cpShape*)segmentShape);
		cpShapeFree((cpShape*)segmentShape);
		segmentShape = 0;
	}

} // love_chipmunk

