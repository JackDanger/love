#include "Body.h"

namespace love_chipmunk
{
	Body::Body(pSpace space, float x, float y, float m, float i) 
		: space(space)
	{
		body = cpBodyNew(m, i);
		body->p = cpv(x, y);

		// Add to space.
		cpSpaceAddBody(space->space, body);
	}

	Body::~Body()
	{
		// Remove from space.
		cpSpaceRemoveBody(space->space, body);
		cpBodyFree(body);
	}

	cpBody * Body::get()
	{
		return body;
	}

	void Body::add(pShape shape)
	{
		shapes.push_back(shape);
	}

	void Body::remove(const pShape & shape)
	{
		shapes.remove(shape);
	}

	float Body::getX()
	{
		return body->p.x;
	}

	float Body::getY()
	{
		return body->p.y;
	}

	float Body::getAngle()
	{
		return body->a;
	}

	void Body::setMass(float m)
	{
		cpBodySetMass(body, m);
	}

	void Body::setMoment(float m)
	{
		cpBodySetMoment(body, m);
	}

	void Body::setAngle(float a)
	{
		cpBodySetAngle(body, a);
	}

	void Body::applyImpulse(float jx, float jy, float rx, float ry)
	{
		cpBodyApplyImpulse(body, cpv(jx, jy), cpv(rx, ry));
	}

	void Body::applyForce(float fx, float fy, float rx, float ry)
	{
		cpBodyApplyForce(body, cpv(fx, fy), cpv(rx, ry));
	}

	void Body::resetForces()
	{
		cpBodyResetForces(body);
	}

} // love_chipmunk

