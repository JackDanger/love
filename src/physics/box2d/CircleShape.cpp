#include "CircleShape.h"

// Module
#include "Body.h"

namespace love
{
namespace physics
{
namespace box2d
{
	CircleShape::CircleShape(Body * body, b2CircleDef * def)
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

} // box2d
} // physics
} // love
