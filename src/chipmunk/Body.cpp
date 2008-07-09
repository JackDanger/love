#include "Body.h"

namespace love_chipmunk
{

	Body::Body(pSpace space, float x, float y, float m, float i, bool dynamic)
		: space(space), dynamic(dynamic)
	{
		body = cpBodyNew(m, i);
		body->p = cpv(x, y);

		if(dynamic)
			cpSpaceAddBody(space->space, body);
	}

	Body::~Body()
	{
		if(dynamic)
			cpSpaceRemoveBody(space->space, body);
		shapes.clear();
		cpBodyFree(body);
	}

	cpBody * Body::get()
	{
		return body;
	}

	void Body::addShape(pShape s)
	{
		shapes.push_back(s);
	}

	void Body::removeShape(pShape s)
	{
		shapes.remove(s);
	}

	bool Body::isDynamic() const
	{
		return dynamic;
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

	void Body::dampedSpring(boost::shared_ptr<Body> & b, const pVector & anchr1, 
		const pVector & anchr2, float rlen, float k, float dmp, float dt)
	{
		cpDampedSpring(body, b->body, anchr1->v, anchr2->v, rlen, k, dmp, dt);
	}

} // love_chipmunk

