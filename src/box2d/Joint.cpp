#include "Joint.h"

// Module
#include "Body.h"
#include "World.h"

// STD
#include <bitset>

// Boost
#include <boost/any.hpp>

namespace love_box2d
{

	Joint::Joint(boost::shared_ptr<Body> body1)
		: body1(body1), world(body1->world)
	{
	}

	Joint::Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2)
		: body1(body1), body2(body2), world(body1->world)
	{
	}

	Joint::~Joint()
	{
		joint = 0;
	}

	int Joint::getType() const
	{
		switch(joint->GetType())
		{
		case e_revoluteJoint: 
			return love::JOINT_DISTANCE;
		case e_prismaticJoint: 
			return love::JOINT_PRISMATIC;
		case e_distanceJoint: 
			return love::JOINT_DISTANCE;
		case e_pulleyJoint: 
			return love::JOINT_PULLEY;
		case e_mouseJoint: 
			return love::JOINT_MOUSE;
		case e_gearJoint: 
			return love::JOINT_GEAR;
		default:
			return -1;
		}
	}

	int Joint::getAnchors(lua_State * L)
	{
		lua_pushnumber(L, joint->GetAnchor1().x);
		lua_pushnumber(L, joint->GetAnchor1().y);
		lua_pushnumber(L, joint->GetAnchor2().x);
		lua_pushnumber(L, joint->GetAnchor2().y);
		return 4;
	}

	int Joint::getReactionForce(lua_State * L)
	{
		b2Vec2 v = joint->GetReactionForce();
		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
		return 2;
	}

	float Joint::getReactionTorque()
	{
		return joint->GetReactionTorque();
	}

	void Joint::setCollideConnected(bool collide)
	{
		joint->m_collideConnected = collide;
	}

	bool Joint::getCollideConnected() const
	{
		return joint->m_collideConnected;
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
