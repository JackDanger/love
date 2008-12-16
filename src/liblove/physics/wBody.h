/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_BODY_W
#define LOVE_BODY_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_BODY_BITS = (LOVE_BODY_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkbody(L, idx) luax_checktype<Body>(L, idx, "Body", LOVE_WRAP_BODY_BITS)

	int _wrap_Body_getX(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getX());
		return 1;
	}

	int _wrap_Body_getY(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getY());
		return 1;
	}

	int _wrap_Body_getAngle(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getAngle());
		return 1;
	}

	int _wrap_Body_getPosition(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getPosition(L);
	}

	int _wrap_Body_getVelocity(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getVelocity(L);
	}

	int _wrap_Body_getWorldCenter(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getWorldCenter(L);
	}

	int _wrap_Body_getLocalCenter(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getLocalCenter(L);
	}

	int _wrap_Body_getSpin(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getSpin());
		return 1;
	}

	int _wrap_Body_getMass(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getMass());
		return 1;
	}

	int _wrap_Body_getInertia(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getInertia());
		return 1;
	}

	int _wrap_Body_getAngularDamping(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getAngularDamping());
		return 1;
	}

	int _wrap_Body_getDamping(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		lua_pushnumber(L, t->getDamping());
		return 1;
	}

	int _wrap_Body_applyImpulse(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float jx = (float)luaL_checknumber(L, 2);
		float jy = (float)luaL_checknumber(L, 3);
		float rx = (float)luaL_optnumber(L, 4, 0);
		float ry = (float)luaL_optnumber(L, 5, 0);
		t->applyImpulse(jx, jy, rx, ry);
		return 0;
	}

	int _wrap_Body_applyTorque(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg = (float)luaL_checknumber(L, 2);
		t->applyTorque(arg);
		return 0;
	}

	int _wrap_Body_applyForce(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float fx = (float)luaL_checknumber(L, 2);
		float fy = (float)luaL_checknumber(L, 3);
		float rx = (float)luaL_optnumber(L, 4, 0);
		float ry = (float)luaL_optnumber(L, 5, 0);
		t->applyForce(fx, fy, rx, ry);
		return 0;
	}

	int _wrap_Body_setX(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setX(arg1);
		return 0;
	}

	int _wrap_Body_setY(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setY(arg1);
		return 0;
	}

	int _wrap_Body_setVelocity(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setVelocity(arg1, arg2);
		return 0;
	}

	int _wrap_Body_setAngle(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setAngle(arg1);
		return 0;
	}

	int _wrap_Body_setSpin(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setSpin(arg1);
		return 0;
	}

	int _wrap_Body_setPosition(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setPosition(arg1, arg2);
		return 0;
	}

	int _wrap_Body_setMassFromShapes(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		t->setMassFromShapes();
		return 0;
	}

	int _wrap_Body_setMass(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float m = (float)luaL_checknumber(L, 4);
		float i = (float)luaL_checknumber(L, 5);
		t->setMass(x, y, m, i);
		return 0;
	}

	int _wrap_Body_setAngularDamping(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setAngularDamping(arg1);
		return 0;
	}

	int _wrap_Body_setDamping(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setDamping(arg1);
		return 0;
	}

	int _wrap_Body_getWorldPoint(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getWorldPoint(L);
	}

	int _wrap_Body_getWorldVector(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getWorldVector(L);
	}

	int _wrap_Body_getLocalPoint(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getLocalPoint(L);
	}

	int _wrap_Body_getLocalVector(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getLocalVector(L);
	}

	int _wrap_Body_getVelocityWorldPoint(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getVelocityWorldPoint(L);
	}

	int _wrap_Body_getVelocityLocalPoint(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		return t->getVelocityLocalPoint(L);
	}

	int _wrap_Body_isBullet(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		luax_pushboolean(L, t->isBullet());
		return 1;
	}

	int _wrap_Body_setBullet(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		bool b = luax_toboolean(L, 2);
		t->setBullet(b);
		return 0;
	}

	int _wrap_Body_isStatic(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		luax_pushboolean(L, t->isStatic());
		return 1;
	}

	int _wrap_Body_isDynamic(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		luax_pushboolean(L, t->isDynamic());
		return 1;
	}

	int _wrap_Body_isFrozen(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		luax_pushboolean(L, t->isFrozen());
		return 1;
	}

	int _wrap_Body_isSleeping(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		luax_pushboolean(L, t->isSleeping());
		return 1;
	}

	int _wrap_Body_setAllowSleep(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		bool b = luax_toboolean(L, 2);
		t->setAllowSleep(b);
		return 0;
	}

	int _wrap_Body_setSleep(lua_State * L)
	{
		Body * t = luax_checkbody(L, 1);
		bool b = luax_toboolean(L, 2);
		t->setSleep(b);
		return 0;
	}

	static const luaL_Reg Body_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },

		{ "getX", _wrap_Body_getX },
		{ "getY", _wrap_Body_getY },
		{ "getAngle", _wrap_Body_getAngle },
		{ "getPosition", _wrap_Body_getPosition },
		{ "getVelocity", _wrap_Body_getVelocity },
		{ "getWorldCenter", _wrap_Body_getWorldCenter },
		{ "getLocalCenter", _wrap_Body_getLocalCenter },
		{ "getSpin", _wrap_Body_getSpin },
		{ "getMass", _wrap_Body_getMass },
		{ "getInertia", _wrap_Body_getInertia },
		{ "getAngularDamping", _wrap_Body_getAngularDamping },
		{ "getDamping", _wrap_Body_getDamping },
		{ "applyImpulse", _wrap_Body_applyImpulse },
		{ "applyTorque", _wrap_Body_applyTorque },
		{ "applyForce", _wrap_Body_applyForce },
		{ "setX", _wrap_Body_setX },
		{ "setY", _wrap_Body_setY },
		{ "setVelocity", _wrap_Body_setVelocity },
		{ "setAngle", _wrap_Body_setAngle },
		{ "setSpin", _wrap_Body_setSpin },
		{ "setPosition", _wrap_Body_setPosition },
		{ "setMassFromShapes", _wrap_Body_setMassFromShapes },
		{ "setMass", _wrap_Body_setMass },
		{ "setAngularDamping", _wrap_Body_setAngularDamping },
		{ "setDamping", _wrap_Body_setDamping },
		{ "getWorldPoint", _wrap_Body_getWorldPoint },
		{ "getWorldVector", _wrap_Body_getWorldVector },
		{ "getLocalPoint", _wrap_Body_getLocalPoint },
		{ "getLocalVector", _wrap_Body_getLocalVector },
		{ "getVelocityWorldPoint", _wrap_Body_getVelocityWorldPoint },
		{ "getVelocityLocalPoint", _wrap_Body_getVelocityLocalPoint },
		{ "isBullet", _wrap_Body_isBullet },
		{ "setBullet", _wrap_Body_setBullet },
		{ "isStatic", _wrap_Body_isStatic },
		{ "isDynamic", _wrap_Body_isDynamic },
		{ "isFrozen", _wrap_Body_isFrozen },
		{ "isSleeping", _wrap_Body_isSleeping },
		{ "setAllowSleep", _wrap_Body_setAllowSleep },
		{ "setSleep", _wrap_Body_setSleep },

		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_BODY_W
