/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_PARTICLE_SYSTEM_H
#define LOVE_GRAPHICS_OPENGL_WRAP_PARTICLE_SYSTEM_H

// LOVE
#include "../../luax.h"
#include "../../wrap.h"
#include "wrap_Image.h"
#include "wrap_Color.h"
#include "ParticleSystem.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	ParticleSystem * luax_checkparticlesystem(lua_State * L, int idx);
	int _wrap_ParticleSystem_setSprite(lua_State * L);
	int _wrap_ParticleSystem_setBufferSize(lua_State * L);
	int _wrap_ParticleSystem_setEmissionRate(lua_State * L);
	int _wrap_ParticleSystem_setLifetime(lua_State * L);
	int _wrap_ParticleSystem_setParticleLife(lua_State * L);
	int _wrap_ParticleSystem_setPosition(lua_State * L);
	int _wrap_ParticleSystem_setDirection(lua_State * L);
	int _wrap_ParticleSystem_setSpread(lua_State * L);
	int _wrap_ParticleSystem_setRelativeDirection(lua_State * L);
	int _wrap_ParticleSystem_setSpeed(lua_State * L);
	int _wrap_ParticleSystem_setGravity(lua_State * L);
	int _wrap_ParticleSystem_setRadialAcceleration(lua_State * L);
	int _wrap_ParticleSystem_setTangentialAcceleration(lua_State * L);
	int _wrap_ParticleSystem_setSize(lua_State * L);
	int _wrap_ParticleSystem_setSizeVariation(lua_State * L);
	int _wrap_ParticleSystem_setRotation(lua_State * L);
	int _wrap_ParticleSystem_setSpin(lua_State * L);
	int _wrap_ParticleSystem_setSpinVariation(lua_State * L);
	int _wrap_ParticleSystem_setColor(lua_State * L);
	int _wrap_ParticleSystem_getX(lua_State * L);
	int _wrap_ParticleSystem_getY(lua_State * L);
	int _wrap_ParticleSystem_getDirection(lua_State * L);
	int _wrap_ParticleSystem_getSpread(lua_State * L);
	int _wrap_ParticleSystem_count(lua_State * L);
	int _wrap_ParticleSystem_start(lua_State * L);
	int _wrap_ParticleSystem_stop(lua_State * L);
	int _wrap_ParticleSystem_pause(lua_State * L);
	int _wrap_ParticleSystem_reset(lua_State * L);
	int _wrap_ParticleSystem_isActive(lua_State * L);
	int _wrap_ParticleSystem_isEmpty(lua_State * L);
	int _wrap_ParticleSystem_isFull(lua_State * L);
	int _wrap_ParticleSystem_update(lua_State * L);
	int wrap_ParticleSystem_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_PARTICLE_SYSTEM_H
