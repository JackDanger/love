#include "Joint.h"

#include "Body.h"

namespace love_chipmunk
{
	Joint::Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2)
		: body1(body1), body2(body2)
	{
	}

	Joint::~Joint()
	{
	}

} // love_chipmunk

