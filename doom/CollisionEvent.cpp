#include "CollisionEvent.h"

namespace love
{

	CollisionEvent::CollisionEvent()
	{
	}

	CollisionEvent::~CollisionEvent()
	{
	}

	const pEntity & CollisionEvent::getFirstEntity() const
	{
		return firstEntity;
	}

	void CollisionEvent::setFirstEntity(pEntity firstEntity)
	{
		this->firstEntity = firstEntity;
	}

	const pEntity & CollisionEvent::getSecondEntity() const
	{
		return secondEntity;
	}

	void CollisionEvent::setSecondEntity(pEntity secondEntity)
	{
		this->secondEntity = secondEntity;
	}

	const Vextor & CollisionEvent::getCollisionPoint() const
	{
		return collisionPoint;
	}

	void CollisionEvent::setCollisionPoint(Vextor collisionPoint)
	{
		this->collisionPoint = collisionPoint;
	}


}// love