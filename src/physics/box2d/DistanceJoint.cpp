#include "DistanceJoint.h"

// Module
#include "Body.h"

namespace love
{
namespace physics
{
namespace box2d
{
	DistanceJoint::DistanceJoint(Body * body1, Body * body2, b2DistanceJointDef * def)
		: Joint(body1, body2)
	{
		def->Initialize(body1->body, body2->body, def->localAnchor1, def->localAnchor2);
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

	void DistanceJoint::setFrequency(float hz)
	{
		joint->m_frequencyHz = hz;
	}

	float DistanceJoint::getFrequency() const
	{
		return joint->m_frequencyHz;
	}

	void DistanceJoint::setDamping(float d)
	{
		joint->m_dampingRatio = d;
	}

	float DistanceJoint::getDamping() const
	{
		return joint->m_dampingRatio;
	}


} // box2d
} // physics
} // love
