/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
**/

#ifndef LOVE_PARTICLE_SYSTEM_W
#define LOVE_PARTICLE_SYSTEM_W

#include "luax.h"

#include "wwrap.h"

#include "wImage.h"
#include "wDrawable.h"
#include "wColor.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_PARTICLE_SYSTEM_BITS = (LOVE_PARTICLE_SYSTEM_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkparticlesystem(L, idx) luax_checktype<ParticleSystem>(L, idx, "ParticleSystem", LOVE_WRAP_PARTICLE_SYSTEM_BITS)

	int _wrap_ParticleSystem_setSprite(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		Image * i = luax_checkimage(L, 2);
		t->setSprite(i);
		return 0;
	}

	int _wrap_ParticleSystem_setBufferSize(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		int arg1 = luaL_checkint(L, 2);
		t->setBufferSize((unsigned int)arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setEmissionRate(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		int arg1 = luaL_checkint(L, 2);
		t->setEmissionRate((unsigned int)arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setLifetime(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setLifetime(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setParticleLife(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setParticleLife(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setPosition(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_checknumber(L, 3);
		t->setPosition(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setDirection(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setDirection(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setSpread(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setSpread(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setRelativeDirection(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		bool arg1 = (bool)luax_toboolean(L, 2);
		t->setRelativeDirection(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setSpeed(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		t->setSpeed(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setGravity(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		t->setGravity(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setRadialAcceleration(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		t->setRadialAcceleration(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setTangentialAcceleration(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		t->setTangentialAcceleration(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setSize(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		float arg3 = (float)luaL_optnumber(L, 3, 0);
		t->setSize(arg1, arg2, arg3);
		return 0;
	}

	int _wrap_ParticleSystem_setSizeVariation(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setSizeVariation(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setRotation(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		t->setRotation(arg1, arg2);
		return 0;
	}

	int _wrap_ParticleSystem_setSpin(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		float arg2 = (float)luaL_optnumber(L, 3, arg1);
		float arg3 = (float)luaL_optnumber(L, 3, 0);
		t->setSpin(arg1, arg2, arg3);
		return 0;
	}

	int _wrap_ParticleSystem_setSpinVariation(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setSpinVariation(arg1);
		return 0;
	}

	int _wrap_ParticleSystem_setColor(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		Color * start = luax_checkcolor(L, 2);
		Color * end = (lua_gettop(L) == 3) ? luax_checkcolor(L, 3) : start;
		t->setColor(start, end);
		return 0;
	}

	int _wrap_ParticleSystem_getX(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		lua_pushnumber(L, t->getX());
		return 1;
	}

	int _wrap_ParticleSystem_getY(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		lua_pushnumber(L, t->getY());
		return 1;
	}

	int _wrap_ParticleSystem_getDirection(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		lua_pushnumber(L, t->getDirection());
		return 1;
	}

	int _wrap_ParticleSystem_getSpread(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		lua_pushnumber(L, t->getSpread());
		return 1;
	}

	int _wrap_ParticleSystem_count(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		lua_pushnumber(L, t->count());
		return 1;
	}

	int _wrap_ParticleSystem_start(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		t->start();
		return 0;
	}

	int _wrap_ParticleSystem_stop(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		t->stop();
		return 0;
	}

	int _wrap_ParticleSystem_pause(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		t->pause();
		return 0;
	}

	int _wrap_ParticleSystem_reset(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		t->reset();
		return 0;
	}

	int _wrap_ParticleSystem_isActive(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		luax_pushboolean(L, t->isActive());
		return 1;
	}

	int _wrap_ParticleSystem_isEmpty(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		luax_pushboolean(L, t->isEmpty());
		return 1;
	}

	int _wrap_ParticleSystem_isFull(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		luax_pushboolean(L, t->isFull());
		return 1;
	}

	int _wrap_ParticleSystem_update(lua_State * L)
	{
		ParticleSystem * t = luax_checkparticlesystem(L, 1);
		float dt = (float)luaL_checknumber(L, 2);
		t->update(dt);
		return 0;
	}

	static const luaL_Reg ParticleSystem_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },

		{ "setSprite", _wrap_ParticleSystem_setSprite },
		{ "setBufferSize", _wrap_ParticleSystem_setBufferSize },
		{ "setEmissionRate", _wrap_ParticleSystem_setEmissionRate },
		{ "setLifeTime", _wrap_ParticleSystem_setLifetime },
		{ "setParticleLife", _wrap_ParticleSystem_setParticleLife },
		{ "setPosition", _wrap_ParticleSystem_setPosition },
		{ "setDirection", _wrap_ParticleSystem_setDirection },
		{ "setSpread", _wrap_ParticleSystem_setSpread },
		{ "setRelativeDirection", _wrap_ParticleSystem_setRelativeDirection },
		{ "setSpeed", _wrap_ParticleSystem_setSpeed },
		{ "setGravity", _wrap_ParticleSystem_setGravity },
		{ "setRadialAcceleration", _wrap_ParticleSystem_setRadialAcceleration },
		{ "setTangentialAcceleration", _wrap_ParticleSystem_setTangentialAcceleration },
		{ "setSize", _wrap_ParticleSystem_setSize },
		{ "setSizeVariation", _wrap_ParticleSystem_setSizeVariation },
		{ "setRotation", _wrap_ParticleSystem_setRotation },
		{ "setSpin", _wrap_ParticleSystem_setSpin },
		{ "setSpinVariation", _wrap_ParticleSystem_setSpinVariation },
		{ "setColor", _wrap_ParticleSystem_setColor },
		{ "getX", _wrap_ParticleSystem_getX },
		{ "getY", _wrap_ParticleSystem_getY },
		{ "getDirection", _wrap_ParticleSystem_getDirection },
		{ "getSpread", _wrap_ParticleSystem_getSpread },
		{ "count", _wrap_ParticleSystem_count },
		{ "start", _wrap_ParticleSystem_start },
		{ "stop", _wrap_ParticleSystem_stop },
		{ "pause", _wrap_ParticleSystem_pause },
		{ "reset", _wrap_ParticleSystem_reset },
		{ "isActive", _wrap_ParticleSystem_isActive },
		{ "isEmpty", _wrap_ParticleSystem_isEmpty },
		{ "isFull", _wrap_ParticleSystem_isFull },
		{ "update", _wrap_ParticleSystem_update },

		// From drawable.
		{ "setOffset", _wrap_Drawable_setOffset },
		{ "getOffset", _wrap_Drawable_getOffset },
		{ 0, 0 }
	};

} // love
} // LOVE_PARTICLE_SYSTEM_W

#endif // LOVE_IMAGE_W
