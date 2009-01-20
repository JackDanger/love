/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_MOUSE_JOINT_W
#define LOVE_MOUSE_JOINT_W

#include "../luax.h"
#include "../wwrap.h"

#include "wJoint.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_MOUSE_JOINT_BITS = (LOVE_MOUSE_JOINT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkmousejoint(L, idx) luax_checktype<MouseJoint>(L, idx, "MouseJoint", LOVE_WRAP_MOUSE_JOINT_BITS)

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

	static const luaL_Reg MouseJoint_mt[] = {
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

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_MOUSE_JOINT_W
