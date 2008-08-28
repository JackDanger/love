#include "Contact.h"

namespace love_box2d
{
	Contact::Contact(const b2ContactPoint * point)
		: point(*point)
	{
	}

	Contact::~Contact()
	{
	}

	int Contact::getPosition(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		lua_pushnumber(L, point.position.x);
		lua_pushnumber(L, point.position.y);
		return 2;
	}

	int Contact::getVelocity(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		lua_pushnumber(L, point.velocity.x);
		lua_pushnumber(L, point.velocity.y);
		return 2;
	}

	int Contact::getNormal(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		lua_pushnumber(L, point.normal.x);
		lua_pushnumber(L, point.normal.y);
		return 2;
	}

	float Contact::getSeparation() const
	{
		return point.separation;
	}

	float Contact::getFriction() const
	{
		return point.friction;
	}

	float Contact::getRestitution() const
	{
		return point.restitution;
	}


} // love_box2d
