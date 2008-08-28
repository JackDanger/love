#include "MouseJoint.h"

// Module
#include "Body.h"
#include "World.h"

namespace love_box2d
{
	MouseJoint::MouseJoint(boost::shared_ptr<Body> body1, b2MouseJointDef * def)
		: Joint(body1)
	{
		def->body1 = body1->world->world->GetGroundBody();
		def->body2 = body1->body;
		def->maxForce = 1000.0f * body1->body->GetMass();
		joint = (b2MouseJoint*)createJoint(def);
	}

	MouseJoint::~MouseJoint()
	{
		destroyJoint(joint);
		joint = 0;
	}

	void MouseJoint::setTarget(float x, float y)
	{
		joint->SetTarget(b2Vec2(x, y));
	}

	int MouseJoint::getTarget(lua_State * L)
	{
		lua_pushnumber(L, joint->m_target.x);
		lua_pushnumber(L, joint->m_target.y);
		return 2;
	}

	void MouseJoint::setMaxForce(float force)
	{
		joint->m_maxForce = force;
	}

	float MouseJoint::getMaxForce() const
	{
		return joint->m_maxForce;
	}


} // love_box2d
