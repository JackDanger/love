#include "GrooveJoint.h"

#include "Body.h"
#include "love_chipmunk.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	GrooveJoint::GrooveJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
		cpVect groove_a, cpVect groove_b, cpVect anchr)
		: Joint(body1, body2, love::JOINT_GROOVE)
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

	int _GrooveJoint_getPoints(lua_State * L)
	{
		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "This method does not take any arguments.");

		// Get the PolygonShape.
		pGrooveJoint p = mod_to_groovejoint(L, 1);

		cpVect pos1 = cpBodyLocal2World(p->grooveJoint->joint.a, p->grooveJoint->grv_a);
		cpVect pos2 = cpBodyLocal2World(p->grooveJoint->joint.a, p->grooveJoint->grv_b);
		cpVect pos3 = cpBodyLocal2World(p->grooveJoint->joint.b, p->grooveJoint->anchr2);

		lua_pushnumber(L, pos1.x);
		lua_pushnumber(L, pos1.y);
		lua_pushnumber(L, pos2.x);
		lua_pushnumber(L, pos2.y);
		lua_pushnumber(L, pos3.x);
		lua_pushnumber(L, pos3.y);

		return 6;
	}

} // love_chipmunk
