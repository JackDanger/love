#include "GrooveJoint.h"

#include "Body.h"

namespace love_chipmunk
{
	GrooveJoint::GrooveJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
		cpVect groove_a, cpVect groove_b, cpVect anchr)
		: Joint(body1, body2)
	{
		grooveJoint = cpGrooveJointAlloc();
		cpGrooveJointInit(grooveJoint, body1->body, body2->body, groove_a, groove_b, anchr);
		joint = (cpJoint*)grooveJoint;
		cpSpaceAddJoint(body1->space->space, joint);
	}

	GrooveJoint::~GrooveJoint()
	{
		cpJointFree((cpJoint*)grooveJoint);
		grooveJoint = 0;
	}

} // love_chipmunk
