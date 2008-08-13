#include "DistanceJoint.h"

// Module
#include "Body.h"
#include "World.h"

// STD
#include <bitset>

namespace love_box2d
{
	DistanceJoint::DistanceJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2DistanceJointDef * def)
		: Joint(body1, body2)
	{
		def->body1 = body1->body;
		def->body2 = body2->body;
		joint = (b2DistanceJoint*)createJoint(def);
	}

	DistanceJoint::~DistanceJoint()
	{
		destroyJoint(joint);
		joint = 0;
	}

	void DistanceJoint::setLength(float length)
	{
		joint->m_length = length;
	}

	float DistanceJoint::getLength() const
	{
		return joint->m_length;
	}

} // love_box2d