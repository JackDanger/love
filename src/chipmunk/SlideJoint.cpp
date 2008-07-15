#include "SlideJoint.h"

#include "Body.h"

namespace love_chipmunk
{
	SlideJoint::SlideJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
		cpVect anchr1, cpVect anchr2, float min, float max)
		: Joint(body1, body2)
	{
		slideJoint = cpSlideJointAlloc();
		cpSlideJointInit(slideJoint, body1->body, body2->body, anchr1, anchr2, min, max);
		joint = (cpJoint*)slideJoint;
		cpSpaceAddJoint(body1->space->space, joint);
	}

	SlideJoint::~SlideJoint()
	{
		cpJointFree((cpJoint*)slideJoint);
		slideJoint = 0;
	}

} // love_chipmunk
