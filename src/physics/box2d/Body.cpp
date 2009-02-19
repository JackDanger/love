/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "Body.h"

#include "../../math.h"

#include "World.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Body::Body(World * world, b2Vec2 p, float m)
		: world(world)
	{
		world->retain();
		b2BodyDef def;
		def.position = p;
		def.massData.mass = m;
		body = world->world->CreateBody(&def);
	}

	Body::~Body()
	{
		world->world->DestroyBody(body);
		world->release();
		body = 0;
	}

	float Body::getX()
	{
		return body->GetPosition().x;
	}

	float Body::getY()
	{
		return body->GetPosition().y;
	}

	int Body::getPosition(lua_State * L)
	{
		return pushVector(L, body->GetPosition());
	}

	int Body::getVelocity(lua_State * L)
	{
		return pushVector(L, body->GetLinearVelocity());
	}

	float Body::getAngle()
	{
		return LOVE_TODEG(body->GetAngle());
	}

	int Body::getWorldCenter(lua_State * L)
	{
		return pushVector(L, body->GetWorldCenter());
	}

	int Body::getLocalCenter(lua_State * L)
	{
		return pushVector(L, body->GetLocalCenter());
	}

	float Body::getSpin() const
	{
		return LOVE_TODEG(body->GetAngularVelocity());
	}

	float Body::getMass() const
	{
		return body->GetMass();
	}

	float Body::getInertia() const
	{
		return body->GetInertia();
	}

	float Body::getAngularDamping() const
	{
		return body->m_angularDamping;
	}

	float Body::getDamping() const
	{
		return body->m_linearDamping;
	}

	void Body::applyImpulse(float jx, float jy)
	{
		body->ApplyImpulse(b2Vec2(jx, jy), body->GetWorldCenter());
	}

	void Body::applyImpulse(float jx, float jy, float rx, float ry)
	{
		body->ApplyImpulse(b2Vec2(jx, jy), b2Vec2(rx, rx));
	}

	void Body::applyTorque(float t)
	{
		body->ApplyTorque(t);
	}

	void Body::applyForce(float fx, float fy, float rx, float ry)
	{
		body->ApplyForce(b2Vec2(fx, fy), b2Vec2(rx, rx));
	}

	void Body::applyForce(float fx, float fy)
	{
		applyForce(fx, fy, 0, 0);
	}

	void Body::setX(float x)
	{
		body->SetXForm(b2Vec2(x, getY()), getAngle());
	}

	void Body::setY(float y)
	{
		body->SetXForm(b2Vec2(getX(), y), getAngle());
	}

	void Body::setVelocity(float x, float y)
	{
		body->SetLinearVelocity(b2Vec2(x, y));
	}

	void Body::setAngle(float d)
	{
		body->SetXForm(body->GetPosition(), LOVE_TORAD(d));
	}

	void Body::setSpin(float r)
	{
		body->SetAngularVelocity(LOVE_TORAD(r));
	}

	void Body::setPosition(float x, float y)
	{
		body->SetXForm(b2Vec2(x, y), body->GetAngle());
	}

	void Body::setAngularDamping(float d)
	{
		body->m_angularDamping = d;
	}

	void Body::setDamping(float d)
	{
		body->m_linearDamping = d;
	}

	void Body::setMassFromShapes()
	{
		body->SetMassFromShapes();
	}

	void Body::setMass(float x, float y, float m, float i)
	{
		b2MassData massData;
		massData.center.Set(x, y);
		massData.mass = m;
		massData.I = i;
		body->SetMass(&massData);
	}

	int Body::getWorldPoint(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetWorldPoint(v));
	}

	int Body::getWorldVector(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetWorldVector(v));
	}

	int Body::getLocalPoint(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetLocalPoint(v));
	}

	int Body::getLocalVector(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetLocalVector(v));
	}

	int Body::getVelocityWorldPoint(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetLinearVelocityFromWorldPoint(v));
	}

	int Body::getVelocityLocalPoint(lua_State * L)
	{
		b2Vec2 v = getVector(L);
		return pushVector(L, body->GetLinearVelocityFromLocalPoint(v));
	}

	bool Body::isBullet() const
	{
		return body->IsBullet();
	}

	void Body::setBullet(bool bullet)
	{
		return body->SetBullet(bullet);
	}

	bool Body::isStatic() const
	{
		return body->IsStatic();
	}

	bool Body::isDynamic() const
	{
		return body->IsDynamic();
	}

	bool Body::isFrozen() const
	{
		return body->IsFrozen();
	}

	bool Body::isSleeping() const
	{
		return body->IsSleeping();
	}

	void Body::setAllowSleep(bool allow)
	{
		body->AllowSleeping(true);
	}

	void Body::setSleep(bool sleep)
	{
		if(sleep)
			body->PutToSleep();
		else
			body->WakeUp();
	}

	b2Vec2 Body::getVector(lua_State * L)
	{
		love::luax_assert_argc(L, 2, 2);
		b2Vec2 v((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2));
		lua_pop(L, 2);
		return v;
	}

	int Body::pushVector(lua_State * L, const b2Vec2 & v)
	{
		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
		return 2;
	}

} // box2d
} // physics
} // love
