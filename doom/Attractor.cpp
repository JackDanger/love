#include "Attractor.h"
#include "Particle.h"

namespace love
{


	Attractor::Attractor()
	{}

	Attractor::Attractor(float x, float y)
	{
		setX(x);
		setY(y);
		doRender = false;
	}

	Attractor::Attractor(float x, float y, ParticleEmitter * emitter)
	{
		setX(x);
		setY(y);
		particles = emitter;
		doRender = false;
	}

	Attractor::Attractor(float x, float y, ParticleEmitter * emitter, float range, float force)
	{
		setX(x);
		setY(y);
		particles = emitter;
		this->range = range;
		this->force = force;
		doRender = false;
	}

	Attractor::~Attractor()
	{}

	void Attractor::setRange(float range) { this->range = range; }
	void Attractor::setForce(float force) { this->force = force; }

	float Attractor::getRange() { return range; }
	float Attractor::getForce() { return force; }
	float Attractor::getForce(float distance)
	{
		if(distance == 0) return force;

		return force * (range / distance);
	}

	void Attractor::update(float dt)
	{
		Vextor temp;
		float power;
		float tempLength;

		for(int i = 0; i != particles->getCount(); i++)
		{
			temp = this->getPosition() - particles->particleAt(i)->getPosition();
			tempLength = temp.getLength();
			if(tempLength <= range)
			{
				power = getForce(temp.normalize()) * dt;
				particles->particleAt(i)->displacement += (temp * power);
				if(particles->particleAt(i)->displacement.getLength() > (tempLength * 2))
				{
					particles->particleAt(i)->displacement.normalize();
					particles->particleAt(i)->displacement *= tempLength * 2;
				}
			}
		}
	}

	void Attractor::render()
	{

		if(doRender)
		{
			glPushMatrix();
			glColor3ub(255,0,0);
			glBegin(GL_QUADS);
				glVertex2f(getX()-10,getY()+10);
				glVertex2f(getX()+10,getY()+10);
				glVertex2f(getX()+10,getY()-10);
				glVertex2f(getX()-10,getY()-10);
			glEnd();
			glPopMatrix();
		}

	}
}