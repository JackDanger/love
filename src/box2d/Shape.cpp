#include "Shape.h"

// Module
#include "Body.h"

namespace love_box2d
{
	Shape::Shape(boost::shared_ptr<Body> body)
		: body(body)
	{
	}

	Shape::~Shape()
	{
	}

} // love_box2d