#include "PolygonShape.h"

#include "Body.h"

namespace love_chipmunk
{
	PolygonShape::PolygonShape(boost::shared_ptr<Body> body)
		: Shape(body)
	{
	}

	PolygonShape::~PolygonShape()
	{
	}

} // love_chipmunk

