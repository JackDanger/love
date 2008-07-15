#include "PinJoint.h"

#include "Body.h"
#include "love_chipmunk.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	PinJoint::PinJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, cpVect anchr1, cpVect anchr2)
		: Joint(body1, body2)
	{
		pinJoint = cpPinJointAlloc();
		cpPinJointInit(pinJoint, body1->body, body2->body, anchr1, anchr2);
		joint = (cpJoint*)pinJoint;
		cpSpaceAddJoint(body1->space->space, joint);
	}

	PinJoint::~PinJoint()
	{
		cpJointFree((cpJoint*)pinJoint);
		pinJoint = 0;
	}

	int _PinJoint_getPoints(lua_State * L)
	{

		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "The method does not take any arguments.");

		// Get the PolygonShape.
		pPinJoint p = mod_to_pinjoint(L, 1);

		cpVect pa = cpBodyLocal2World(p->pinJoint->joint.a, p->pinJoint->anchr1);
		cpVect pb = cpBodyLocal2World(p->pinJoint->joint.b, p->pinJoint->anchr2);

		lua_pushnumber(L, pa.x);
		lua_pushnumber(L, pa.y);
		lua_pushnumber(L, pb.x);
		lua_pushnumber(L, pb.y);

		return 4;
	}

} // love_chipmunk
