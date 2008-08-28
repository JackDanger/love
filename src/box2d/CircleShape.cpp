#include "CircleShape.h"

// Module
#include "Body.h"

namespace love_box2d
{
	CircleShape::CircleShape(boost::shared_ptr<Body> body, b2CircleDef * def)
		: Shape(body), radius(def->radius)
	{
		shape = body->body->CreateShape(def);
		shape->SetUserData((void*)data);
	}

	CircleShape::~CircleShape()
	{
		body->body->DestroyShape(shape);
		shape = 0;
	}

	float CircleShape::getRadius() const
	{
		return radius;
	}

} // love_box2d
