#include "CircleShape.h"

// Module
#include "Body.h"

namespace love_box2d
{
	CircleShape::CircleShape(boost::shared_ptr<Body> body, b2CircleDef * def)
		: Shape(body)
	{
		shape = body->body->CreateShape(def);
	}

	CircleShape::~CircleShape()
	{
		body->body->DestroyShape(shape);
		shape = 0;
	}

} // love_box2d