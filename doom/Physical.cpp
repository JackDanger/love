#include "Physical.h"

namespace love
{

	float Physical::VERY_SMALL = 0.0001f;

	Physical::Physical()
	{
	}

	Physical::~Physical()
	{
	}

	bool Physical::isMovable()
	{
		return (inverseMass != 0);
	}

	float Physical::getFriction(){ return friction; }
	void Physical::setFriction(float friction){ this->friction = friction; }
 
	float Physical::getRestitution(){ return restitution; }
	void Physical::setRestitution(float restitution){ this->restitution = restitution; }

	float Physical::getGlue(){ return glue; }
	void Physical::setGlue(float glue){ this->glue = glue; }

	float Physical::getMass(){ return mass; }
	void Physical::setMass(float mass)
	{ 
		this->mass			= (mass < VERY_SMALL) ? 0.0f : mass; 
		this->inverseMass	= (mass < VERY_SMALL) ? 0.0f : 1 / mass;
	}

	float Physical::getInverseMass(){ return this->inverseMass; }
}