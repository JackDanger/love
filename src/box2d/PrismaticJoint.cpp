#include "PrismaticJoint.h"

// Module
#include "Body.h"

namespace love_box2d
{
	PrismaticJoint::PrismaticJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2PrismaticJointDef * def)
		: Joint(body1, body2)
	{
		def->Initialize(body1->body, body2->body, def->localAnchor2, def->localAxis1);
		def->lowerTranslation = 0.0f;
		def->upperTranslation = 100.0f;
		def->enableLimit = true;
		joint = (b2PrismaticJoint*)createJoint(def);
	}

	PrismaticJoint::~PrismaticJoint()
	{
		destroyJoint(joint);
		joint = 0;
	}

	float PrismaticJoint::getTranslation() const
	{
		return joint->GetJointTranslation();
	}

	float PrismaticJoint::getSpeed() const
	{
		return joint->GetJointSpeed();
	}

	void PrismaticJoint::setMotorEnabled(bool motor)
	{
		return joint->EnableMotor(true);
	}

	bool PrismaticJoint::isMotorEnabled() const
	{
		return joint->IsMotorEnabled();
	}

	void PrismaticJoint::setMaxMotorForce(float force)
	{
		joint->SetMaxMotorForce(force);
	}

	float PrismaticJoint::getMaxMotorForce() const
	{
		return joint->GetMotorForce();
	}

	void PrismaticJoint::setMotorSpeed(float speed)
	{
		joint->SetMotorSpeed(speed);
	}

	float PrismaticJoint::getMotorSpeed() const
	{
		return joint->GetMotorSpeed();
	}

	float PrismaticJoint::getMotorForce() const
	{
		return joint->GetMotorForce();
	}

	void PrismaticJoint::setLimitsEnabled(bool limit)
	{
		joint->EnableLimit(limit);
	}

	bool PrismaticJoint::isLimitsEnabled() const
	{
		return joint->IsLimitEnabled();
	}

	void PrismaticJoint::setUpperLimit(float limit)
	{
		joint->SetLimits(joint->GetLowerLimit(), limit);
	}

	void PrismaticJoint::setLowerLimit(float limit)
	{
		joint->SetLimits(limit, joint->GetUpperLimit());
	}

	void PrismaticJoint::setLimits(float lower, float upper)
	{
		joint->SetLimits(lower, upper);
	}

	float PrismaticJoint::getLowerLimit() const
	{
		return joint->GetLowerLimit();
	}

	float PrismaticJoint::getUpperLimit() const
	{
		return joint->GetUpperLimit();
	}

	int PrismaticJoint::getLimits(lua_State * L)
	{
		lua_pushnumber(L, joint->GetLowerLimit());
		lua_pushnumber(L, joint->GetUpperLimit());
		return 2;
	}


} // love_box2d
