#include "Entity.h"

namespace love
{

	Entity::Entity()
	{
		setType(LOVE_TYPE_ENTITY);
	}

	Entity::~Entity()
	{
	}

	float Entity::getX()
	{
		return position.getX();
	}

	void Entity::setX(float x)
	{
		position.setX(x);
	}

	float Entity::getY()
	{
		return position.getY();
	}

	void Entity::setY(float y)
	{
		position.setY(y);
	}

	void Entity::xMove(float dx)
	{
		position = Vextor(position.getX() + dx, position.getY());
	}

	void Entity::yMove(float dy)
	{
		position = Vextor(position.getX(), position.getY() + dy);
	}

	void Entity::move(const Vextor & dv)
	{
		position += dv;
	}

	const Vextor & Entity::getPosition() const
	{
		return position;
	}

	void Entity::setPosition(const Vextor & v)
	{
		position = v;
	}

	void Entity::setPosition(float x, float y)
	{
		position = Vextor(x, y);
	}

	const Vextor & Entity::getDisplacement()
	{
		return displacement;
	}

	void Entity::setDisplacement(Vextor displacement)
	{
		this->displacement = displacement;
	}

	void Entity::addImpulse(const Vextor & i)
	{
	}

	void Entity::clearImpulse()
	{
	}

	void Entity::move()
	{
	}

}//love