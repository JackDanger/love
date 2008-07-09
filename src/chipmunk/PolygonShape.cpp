#include "PolygonShape.h"

#include "Body.h"

namespace love_chipmunk
{
	PolygonShape::PolygonShape(boost::shared_ptr<Body> body, cpVect * verts, int num)
		: Shape(body), verts(verts)
	{
		polygonShape = cpPolyShapeAlloc();
		cpPolyShapeInit(polygonShape, body->body, num, verts, cpvzero);
		shape = (cpShape*)polygonShape;
		shape->e = 0.5f;
		shape->u = 0.5f;

		if(body->isDynamic())
			cpSpaceAddShape(body->space->space, shape);
		else
			cpSpaceAddStaticShape(body->space->space, shape);	
	}

	PolygonShape::~PolygonShape()
	{
		if(verts != 0)
		{
			verts = 0;
			delete [] verts;
		}

		if(body->isDynamic())
			cpSpaceRemoveShape(body->space->space, (cpShape*)polygonShape);
		else
			cpSpaceRemoveStaticShape(body->space->space, (cpShape*)polygonShape);

		cpShapeFree((cpShape*)polygonShape);
		polygonShape = 0;
	}

} // love_chipmunk

