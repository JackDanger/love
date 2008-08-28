#include "RevoluteJoint.h"

#include <love/math.h>

// Module
#include "Body.h"

namespace love_box2d
{
	RevoluteJoint::RevoluteJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2RevoluteJointDef * def)
		: Joint(body1, body2)
	{
		def->localAnchor2 = body2->body->GetLocalPoint(def->localAnchor1);
		def->localAnchor1 = body1->body->GetLocalPoint(def->localAnchor1);
		def->body1 = body1->body;
		def->body2 = body2->body;
		joint = (b2RevoluteJoint*)createJoint(def);
	}

	RevoluteJoint::~RevoluteJoint()
	{
		destroyJoint(joint);
		joint = 0;
	}

	float RevoluteJoint::getAngle() const
	{
		return LOVE_TODEG(joint->GetJointAngle());
	}

	float RevoluteJoint::getSpeed() const
	{
		return LOVE_TODEG(joint->GetJointSpeed());
	}

	void RevoluteJoint::setMotorEnabled(bool motor)
	{
		return joint->EnableMotor(motor);
	}

	bool RevoluteJoint::isMotorEnabled() const
	{
		return joint->IsMotorEnabled();
	}

	void RevoluteJoint::setMaxMotorTorque(float torque)
	{
		joint->SetMaxMotorTorque(torque);
	}

	float RevoluteJoint::getMaxMotorTorque() const
	{
		return joint->GetMotorTorque();
	}

	void RevoluteJoint::setMotorSpeed(float speed)
	{
		joint->SetMotorSpeed(LOVE_TORAD(speed));
	}

	float RevoluteJoint::getMotorSpeed() const
	{
		return LOVE_TODEG(joint->GetMotorSpeed());
	}

	float RevoluteJoint::getMotorTorque() const
	{
		return joint->GetMotorTorque();
	}

	void RevoluteJoint::setLimitsEnabled(bool limit)
	{
		joint->EnableLimit(limit);
	}

	bool RevoluteJoint::isLimitsEnabled() const
	{
		return joint->IsLimitEnabled();
	}

	void RevoluteJoint::setUpperLimit(float limit)
	{
		joint->SetLimits(joint->GetLowerLimit(), LOVE_TORAD(limit));
	}

	void RevoluteJoint::setLowerLimit(float limit)
	{
		joint->SetLimits(LOVE_TORAD(limit), joint->GetUpperLimit());
	}

	void RevoluteJoint::setLimits(float lower, float upper)
	{
		joint->SetLimits(LOVE_TORAD(lower), LOVE_TORAD(upper));
	}

	float RevoluteJoint::getLowerLimit() const
	{
		return LOVE_TODEG(joint->GetLowerLimit());
	}

	float RevoluteJoint::getUpperLimit() const
	{
		return LOVE_TODEG(joint->GetUpperLimit());
	}

	int RevoluteJoint::getLimits(lua_State * L)
	{
		lua_pushnumber(L, LOVE_TODEG(joint->GetLowerLimit()));
		lua_pushnumber(L, LOVE_TODEG(joint->GetUpperLimit()));
		return 2;
	}

} // love_box2d
