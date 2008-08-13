#include "Joint.h"

// Module
#include "Body.h"
#include "World.h"

// STD
#include <bitset>

namespace love_box2d
{

	Joint::Joint(boost::shared_ptr<Body> body1)
		: world(body1->world), body1(body1)
	{
	}

	Joint::Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2)
		: world(body1->world), body1(body1), body2(body2)
	{
	}

	Joint::~Joint()
	{
		joint = 0;
	}

	int Joint::getAnchors(lua_State * L)
	{
		lua_pushnumber(L, joint->GetAnchor1().x);
		lua_pushnumber(L, joint->GetAnchor1().y);
		lua_pushnumber(L, joint->GetAnchor2().x);
		lua_pushnumber(L, joint->GetAnchor2().y);
		return 4;
	}

	b2Joint * Joint::createJoint(b2JointDef * def)
	{
		joint = world->world->CreateJoint(def);
		return joint;
	}

	void Joint::destroyJoint(b2Joint * joint)
	{
		world->world->DestroyJoint(joint);
	}
		

} // love_box2d