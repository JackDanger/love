/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_BODY_H
#define LOVE_PHYSICS_BOX2D_WRAP_BODY_H

// LOVE
#include <common/runtime.h>
#include "Body.h"

namespace love
{
namespace physics
{
namespace box2d
{

	Body * luax_checkbody(lua_State * L, int idx);
	int _wrap_Body_getX(lua_State * L);
	int _wrap_Body_getY(lua_State * L);
	int _wrap_Body_getAngle(lua_State * L);
	int _wrap_Body_getPosition(lua_State * L);
	int _wrap_Body_getVelocity(lua_State * L);
	int _wrap_Body_getWorldCenter(lua_State * L);
	int _wrap_Body_getLocalCenter(lua_State * L);
	int _wrap_Body_getSpin(lua_State * L);
	int _wrap_Body_getMass(lua_State * L);
	int _wrap_Body_getInertia(lua_State * L);
	int _wrap_Body_getAngularDamping(lua_State * L);
	int _wrap_Body_getDamping(lua_State * L);
	int _wrap_Body_applyImpulse(lua_State * L);
	int _wrap_Body_applyTorque(lua_State * L);
	int _wrap_Body_applyForce(lua_State * L);
	int _wrap_Body_setX(lua_State * L);
	int _wrap_Body_setY(lua_State * L);
	int _wrap_Body_setVelocity(lua_State * L);
	int _wrap_Body_setAngle(lua_State * L);
	int _wrap_Body_setSpin(lua_State * L);
	int _wrap_Body_setPosition(lua_State * L);
	int _wrap_Body_setMassFromShapes(lua_State * L);
	int _wrap_Body_setMass(lua_State * L);
	int _wrap_Body_setAngularDamping(lua_State * L);
	int _wrap_Body_setDamping(lua_State * L);
	int _wrap_Body_getWorldPoint(lua_State * L);
	int _wrap_Body_getWorldVector(lua_State * L);
	int _wrap_Body_getLocalPoint(lua_State * L);
	int _wrap_Body_getLocalVector(lua_State * L);
	int _wrap_Body_getVelocityWorldPoint(lua_State * L);
	int _wrap_Body_getVelocityLocalPoint(lua_State * L);
	int _wrap_Body_isBullet(lua_State * L);
	int _wrap_Body_setBullet(lua_State * L);
	int _wrap_Body_isStatic(lua_State * L);
	int _wrap_Body_isDynamic(lua_State * L);
	int _wrap_Body_isFrozen(lua_State * L);
	int _wrap_Body_isSleeping(lua_State * L);
	int _wrap_Body_setAllowSleep(lua_State * L);
	int _wrap_Body_setSleep(lua_State * L);
	int wrap_Body_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_BODY_H
