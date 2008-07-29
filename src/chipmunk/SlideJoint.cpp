#include "SlideJoint.h"

#include "Body.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	SlideJoint::SlideJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
		cpVect anchr1, cpVect anchr2, float min, float max)
		: Joint(body1, body2, love::JOINT_SLIDE)
	{
		slideJoint = cpSlideJointAlloc();
		cpSlideJointInit(slideJoint, body1->body, body2->body, anchr1, anchr2, min, max);
		joint = (cpJoint*)slideJoint;
		cpSpaceAddJoint(body1->space->space, joint);
	}

	SlideJoint::~SlideJoint()
	{
		cpJointFree((cpJoint*)slideJoint);
		slideJoint = 0;
	}

	int _SlideJoint_getPoints(lua_State * L)
	{
		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "This method does not take any arguments.");

		// Get the PolygonShape.
		pSlideJoint p = mod_to_slidejoint(L, 1);

		cpVect pos1 = cpBodyLocal2World(p->slideJoint->joint.a, p->slideJoint->anchr1);
		cpVect pos2 = cpBodyLocal2World(p->slideJoint->joint.b, p->slideJoint->anchr2);

		lua_pushnumber(L, pos1.x);
		lua_pushnumber(L, pos1.y);
		lua_pushnumber(L, pos2.x);
		lua_pushnumber(L, pos2.y);

		return 4;
	}

	int _SlideJoint_getLimits(lua_State * L)
	{
		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "This method does not take any arguments.");

		// Get the PolygonShape.
		pSlideJoint p = mod_to_slidejoint(L, 1);

		lua_pushnumber(L, p->slideJoint->min);
		lua_pushnumber(L, p->slideJoint->max);
		return 2;
	}

} // love_chipmunk
