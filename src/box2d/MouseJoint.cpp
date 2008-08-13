#include "MouseJoint.h"

// Module
#include "Body.h"
#include "World.h"

// STD
#include <bitset>

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

} // love_box2d