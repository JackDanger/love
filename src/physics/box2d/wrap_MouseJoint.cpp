/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#include "wrap_MouseJoint.h"

namespace love
{
namespace physics
{
namespace box2d
{
	MouseJoint * luax_checkmousejoint(lua_State * L, int idx)
	{
		return luax_checktype<MouseJoint>(L, idx, "MouseJoint", LOVE_PHYSICS_MOUSE_JOINT_BITS);
	}

	int _wrap_MouseJoint_setTarget(lua_State * L)
	{
		MouseJoint * t = luax_checkmousejoint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		t->setTarget(x, y);
		return 0;
	}

	int _wrap_MouseJoint_getTarget(lua_State * L)
	{
		MouseJoint * t = luax_checkmousejoint(L, 1);
		lua_remove(L, 1);
		return t->getTarget(L);
	}

	int _wrap_MouseJoint_setMaxForce(lua_State * L)
	{
		MouseJoint * t = luax_checkmousejoint(L, 1);
		float f = (float)luaL_checknumber(L, 2);
		t->setMaxForce(f);
		return 0;
	}

	int _wrap_MouseJoint_getMaxForce(lua_State * L)
	{
		MouseJoint * t = luax_checkmousejoint(L, 1);
		lua_pushnumber(L, t->getMaxForce());
		return 1;
	}

	static const luaL_Reg wrap_MouseJoint_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setTarget", _wrap_MouseJoint_setTarget },
		{ "getTarget", _wrap_MouseJoint_getTarget },
		{ "setMaxForce", _wrap_MouseJoint_setMaxForce },
		{ "getMaxForce", _wrap_MouseJoint_getMaxForce },
		// From Joint.
		{ "getType", _wrap_Joint_getType },
		{ "getAnchors", _wrap_Joint_getAnchors },
		{ "getReactionForce", _wrap_Joint_getReactionForce },
		{ "getReactionTorque", _wrap_Joint_getReactionTorque },
		{ "setCollideConnected", _wrap_Joint_setCollideConnected },
		{ "getCollideConnected", _wrap_Joint_getCollideConnected },
		{ 0, 0 }
	};

	int wrap_MouseJoint_open(lua_State * L)
	{
		luax_register_type(L, "MouseJoint", wrap_MouseJoint_functions);
		return 0;
	}

} // box2d
} // physics
} // love
