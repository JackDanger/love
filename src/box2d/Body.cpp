#include "Body.h"

#include "World.h"

namespace love_box2d
{
	Body::Body(boost::shared_ptr<World> world, b2Vec2 p, float m)
		: world(world)
	{
		b2BodyDef def;
		def.position = p;
		def.massData.mass = m;
		body = world->world->CreateBody(&def);
	}

	Body::~Body()
	{
		world->world->DestroyBody(body);
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
		love::luax_assert_argc(L, 0);
		lua_pushnumber(L, body->GetPosition().x);
		lua_pushnumber(L, body->GetPosition().y);
		return 2;
	}

	float Body::getAngle()
	{
		return body->GetAngle();
	}

	void Body::applyImpulse(float jx, float jy)
	{
		body->ApplyImpulse(b2Vec2(jx, jy), body->GetWorldCenter());
	}

	void Body::applyImpulse(float jx, float jy, float rx, float ry)
	{
		body->ApplyImpulse(b2Vec2(jx, jy), b2Vec2(rx, rx));
	}

	void Body::applyForce(float fx, float fy, float rx, float ry)
	{
		body->ApplyForce(b2Vec2(fx, fy), b2Vec2(rx, rx));
	}

	void Body::setX(float x)
	{
		body->SetXForm(b2Vec2(x, getY()), getAngle());
	}

	void Body::setY(float y)
	{
		body->SetXForm(b2Vec2(getX(), y), getAngle());
	}

	void Body::setPosition(float x, float y)
	{
	}

	void Body::setMassFromShapes()
	{
		body->SetMassFromShapes();
	}

} // love_box2d