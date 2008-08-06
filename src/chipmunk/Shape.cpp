#include "Shape.h"

#include "Body.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	Shape::Shape(boost::shared_ptr<Body> body)
		: body(body)
	{
	}

	Shape::~Shape()
	{
	}

	void Shape::remove()
	{
		cpSpaceRemoveShape(body->space->space, shape);
	}

	void Shape::setType(unsigned long type)
	{
		shape->collision_type = type;
	}

	unsigned long Shape::getType() const
	{
		return shape->collision_type;
	}

	void Shape::setGroup(unsigned long group)
	{
		shape->group = group;
	}

	unsigned long Shape::getGroup() const
	{
		return shape->group;
	}

	void Shape::setLayers(unsigned long layers)
	{
		shape->layers = layers;
	}

	unsigned long Shape::getLayers() const
	{
		return shape->layers;
	}
	
	void Shape::setElasticity(float e)
	{
		shape->e = e;
	}

	float Shape::getElasticity() const
	{
		return shape->e;
	}

	void Shape::setFriction(float u)
	{
		shape->u = u;
	}

	float Shape::getFriction() const
	{
		return shape->u;
	}

	void Shape::setSurfaceVelocity(float x, float y)
	{
		shape->surface_v = cpv(x, y);
	}

	int Shape::setData(lua_State * L)
	{
		love::luax_assert_argc(L, 1);
		ref.reset<love::Reference>(new love::Reference(L, -1));
		return 0;
	}

	int Shape::getData(lua_State * L)
	{
		love::luax_assert_argc(L, 0);
		
		if(ref != 0)
			ref->push();
		else
			lua_pushnil(L);

		return 1;
	}

	int Shape::getPosition(lua_State * L)
	{
		love::luax_assert_argc(L, 0);
		lua_pushnumber(L, shape->body->p.x);
		lua_pushnumber(L, shape->body->p.y);
		return 2;
	}

	int Shape::getBoundingBox(lua_State * L)
	{
		love::luax_assert_argc(L, 0);
		lua_pushnumber(L, shape->bb.t);
		lua_pushnumber(L, shape->bb.r);
		lua_pushnumber(L, shape->bb.b);
		lua_pushnumber(L, shape->bb.l);
		return 4;
	}

} // love_chipmunk

