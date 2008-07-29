#include "Joint.h"

#include "Body.h"

namespace love_chipmunk
{
	Joint::Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, int jointType)
		: body1(body1), body2(body2), jointType(jointType)
	{
	}

	Joint::~Joint()
	{
	}

	int Joint::getJointType() const
	{
		return jointType;
	}

} // love_chipmunk

