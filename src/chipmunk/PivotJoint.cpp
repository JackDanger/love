#include "PivotJoint.h"

#include "Body.h"
#include "love_chipmunk.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	PivotJoint::PivotJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
		cpVect pivot)
		: Joint(body1, body2, love::JOINT_PIVOT)
	{
		pivotJoint = cpPivotJointAlloc();
		cpPivotJointInit(pivotJoint, body1->body, body2->body, pivot);
		joint = (cpJoint*)pivotJoint;
		cpSpaceAddJoint(body1->space->space, joint);
	}

	PivotJoint::~PivotJoint()
	{
		cpJointFree((cpJoint*)pivotJoint);
		pivotJoint = 0;
	}

	int _PivotJoint_getPoint(lua_State * L)
	{
		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "The method does not take any arguments.");

		// Get the PolygonShape.
		pPivotJoint p = mod_to_pivotjoint(L, 1);

		cpVect pos = cpBodyLocal2World(p->pivotJoint->joint.a, p->pivotJoint->anchr1);

		lua_pushnumber(L, pos.x);
		lua_pushnumber(L, pos.y);

		return 2;
	}

} // love_chipmunk
