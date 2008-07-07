#include "Shape.h"

#include "Body.h"

namespace love_chipmunk
{
	Shape::Shape(boost::shared_ptr<Body> body)
		: body(body)
	{
	}

	Shape::~Shape()
	{
		cpShapeFree(shape);
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


} // love_chipmunk

