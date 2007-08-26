#include "Entity.h"
#include "love.h"

namespace love
{
	Entity::Entity()
	{
		setType(LOVE_TYPE_ENTITY);
	}

	Entity::~Entity()
	{
	}

	void Entity::init()
	{
	}

	float Entity::getX()
	{
		return position.getX();
	}

	float Entity::getY()
	{
		return position.getY();
	}

	float Entity::getZ()
	{
		return z;
	}

	void Entity::setX(float x)
	{
		position.setX(x);
	}

	void Entity::setY(float y)
	{
		position.setY(y);
	}

	void Entity::setZ(float z)
	{
		this->z = z;
	}

	Vextor* Entity::getPosition()
	{
		return &position;
	}

	float Entity::getXPosition()
	{
		return position.getX();
	}

	float Entity::getYPosition()
	{
		return position.getY();
	}

	float Entity::getZPosition()
	{
		return z;
	}

	void Entity::setPosition(Vextor * newPosition)
	{
		this->position = *newPosition;
	}

	void Entity::setPosition(float x, float y)
	{
		position.setX(x);
		position.setY(y);
	}

	void Entity::setXPosition(float x)
	{
		position.setX(x);
	}

	void Entity::setYPosition(float y)
	{
		position.setY(y);
	}

	void Entity::setZPosition(float z)
	{
		this->z = z;
	}

	Vextor* Entity::getVelocity()
	{
		return &velocity;
	}

	float Entity::getXVelocity()
	{
		return velocity.getX();
	}

	float Entity::getYVelocity()
	{
		return velocity.getY();
	}

	void Entity::setVelocity(Vextor * newVelocity)
	{
		this->velocity = *newVelocity;
	}

	void Entity::setVelocity(float x, float y)
	{
		velocity.setX(x);
		velocity.setY(y);
	}

	void Entity::setXVelocity(float x)
	{
		velocity.setX(x);
	}

	void Entity::setYVelocity(float y)
	{
		velocity.setY(y);
	}

	Vextor* Entity::getAcceleration()
	{
		return &acceleration;
	}

	float Entity::getXAcceleration()
	{
		return acceleration.getX();
	}

	float Entity::getYAcceleration()
	{
		return acceleration.getY();
	}

	void Entity::setAcceleration(Vextor * newAcceleration)
	{
		this->acceleration = *newAcceleration;
	}

	void Entity::setAcceleration(float x, float y)
	{
		acceleration.setX(x);
		acceleration.setY(y);
	}

	void Entity::setXAcceleration(float x)
	{
		acceleration.setX(x);
	}

	void Entity::setYAcceleration(float y)
	{
		acceleration.setY(y);
	}

	float Entity::getOrientation()
	{
		return orientation;
	}

	void Entity::setOrientation(float orientation)
	{
		this->orientation = orientation;
	}

	void Entity::update(float dt)
	{
		velocity += acceleration * dt;
		position += velocity * dt;
	}

	int Entity::load()
	{
		orientation = 0;
		z = 0;

		return LOVE_OK;
	}

	void Entity::unload()
	{
	}
}
