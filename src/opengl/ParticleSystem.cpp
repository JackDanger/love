#include "ParticleSystem.h"

#include <SDL_opengl.h>
#include <cmath>

namespace love_opengl
{
	//
	// Struct constructor.
	//

	particle::particle()
	{
		// life
		lifetime = 0;
		life = 0;

		// position
		position[0] = 0.0f;
		position[1] = 0.0f;

		// direction
		direction = 0;

		// speed
		speed[0] = 0;
		speed[1] = 0;

		// acceleration
		gravity = 0;
		radialAcceleration = 0;
		tangentialAcceleration = 0;

		// size
		size = 1.0f;
		sizeStart = 1.0f;
		sizeEnd = 1.0f;

		// rotation
		rotation = 0.0f;
		rotationStart = 0.0f;
		rotationEnd = 0.0f;

		// random colour
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;
	}

	//
	// Class functions.
	//

	ParticleSystem::ParticleSystem(pImage sprite, unsigned int buffer) : pStart(0), pLast(0), pEnd(0), active(true), emissionRate(0),
															lifetime(-1), life(0), particleLifeMin(0), particleLifeMax(0),
															direction(0), spread(0), speedMin(0), speedMax(0), gravityMin(0),
															gravityMax(0), radialAccelerationMin(0), radialAccelerationMax(0),
															tangentialAccelerationMin(0), tangentialAccelerationMax(0),
															sizeStart(1), sizeEnd(1), sizeVariation(0), rotationStart(0),
															rotationEnd(0), rotationVariation(0)
	{
		this->sprite = sprite;
		colorStart.reset(new Color(255,255,255,255));
		colorEnd.reset(new Color(255,255,255,255));
		setBufferSize(buffer);
	}

	ParticleSystem::~ParticleSystem()
	{
		if(pStart != 0)
			delete [] pStart;
	}

	void ParticleSystem::add()
	{
		if(!isFull())
		{
			*pLast = particle();

			float min,max;

			min = particleLifeMin;
			max = particleLifeMax;
			if(min == max)
				pLast->life = min;
			else
				pLast->life = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
			pLast->lifetime = pLast->life;

			min = direction - spread;
			max = direction + spread;
			pLast->direction = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

			min = speedMin;
			max = speedMax;
			float speed = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
			pLast->speed[0] = (0 * cos(pLast->direction)) - (speed * sin(pLast->direction));
			pLast->speed[1] = -( (0 * sin(pLast->direction)) + (speed * cos(pLast->direction)) );

			min = gravityMin;
			max = gravityMax;
			pLast->gravity = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

			min = radialAccelerationMin;
			max = radialAccelerationMax;
			pLast->radialAcceleration = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

			min = tangentialAccelerationMin;
			max = tangentialAccelerationMax;
			pLast->tangentialAcceleration = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

			min = sizeStart;
			max = sizeStart + ((sizeEnd - sizeStart) * sizeVariation);
			pLast->sizeStart = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
			pLast->sizeEnd = sizeEnd;
			pLast->size = pLast->sizeStart;

			min = rotationStart;
			max = rotationStart + ((rotationEnd - rotationStart) * rotationVariation);
			pLast->rotationStart = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
			pLast->rotationEnd = rotationEnd;
			pLast->rotation = pLast->rotationStart;

			pLast->color[0] = (float)colorStart->getRed() / 255;
			pLast->color[1] = (float)colorStart->getGreen() / 255;
			pLast->color[2] = (float)colorStart->getBlue() / 255;
			pLast->color[3] = (float)colorStart->getAlpha() / 255;
			
			pLast++;
		}
	}

	void ParticleSystem::remove(particle * p)
	{
		if(!isEmpty())
		{
			*p = *(--pLast);
		}
	}

	void ParticleSystem::setBufferSize(unsigned int size)
	{
		// delete previous data
		delete [] pStart;

		pLast = pStart = new particle[size];

		pEnd = pStart + size;
	}

	void ParticleSystem::setEmissionRate(int rate)
	{
		emissionRate = rate;
	}

	void ParticleSystem::setLifetime(float life)
	{
		this->life = lifetime = life;
	}

	void ParticleSystem::setParticleLife(float min, float max)
	{
		particleLifeMin = min;
		if(max == 0)
			particleLifeMax = min;
		else
			particleLifeMax = max;
	}

	void ParticleSystem::setDirection(float direction, float spread)
	{
		this->direction = direction;
		this->spread = spread;
	}

	void ParticleSystem::setSpeed(float min, float max)
	{
		speedMin = min;
		if(max == 0)
			speedMax = min;
		else
			speedMax = max;
	}

	void ParticleSystem::setGravity(float min, float max)
	{
		gravityMin = min;
		if(max == 0)
			gravityMax = min;
		else
			gravityMax = max;
	}

	void ParticleSystem::setRadialAcceleration(float min, float max)
	{
		radialAccelerationMin = min;
		if(max == 0)
			radialAccelerationMax = min;
		else
			radialAccelerationMax = max;
	}

	void ParticleSystem::setTangentialAcceleration(float min, float max)
	{
		tangentialAccelerationMin = min;
		if(max == 0)
			tangentialAccelerationMax = min;
		else
			tangentialAccelerationMax = max;
	}

	void ParticleSystem::setSize(float size)
	{
		sizeStart = size;
		sizeEnd = size;
	}

	void ParticleSystem::setSize(float start, float end)
	{
		sizeStart = start;
		sizeEnd = end;
	}

	void ParticleSystem::setSize(float start, float end, float variation)
	{
		sizeStart = start;
		sizeEnd = end;
		sizeVariation = variation;
	}

	void ParticleSystem::setSizeVariation(float variation)
	{
		sizeVariation = variation;
	}

	void ParticleSystem::setRotation(float rotation)
	{
		rotationStart = rotation;
		rotationEnd = rotation;
	}

	void ParticleSystem::setRotation(float start, float end)
	{
		rotationStart = start;
		rotationEnd = end;
	}

	void ParticleSystem::setRotation(float start, float end, float variation)
	{
		rotationStart = start;
		rotationEnd = end;
		rotationVariation = variation;
	}

	void ParticleSystem::setRotationVariation(float variation)
	{
		rotationVariation = variation;
	}

	void ParticleSystem::setColor(pColor color)
	{
		colorStart = color;
		colorEnd = color;
	}

	void ParticleSystem::setColor(pColor start, pColor end)
	{
		colorStart = start;
		colorEnd = end;
	}

	int ParticleSystem::count() const
	{
		return (int)(pLast - pStart);
	}

	void ParticleSystem::start()
	{
		active = true;
	}

	void ParticleSystem::stop()
	{
		active = false;
		life = lifetime;
	}

	void ParticleSystem::pause()
	{
		active = false;
	}

	void ParticleSystem::reset()
	{
		pLast = pStart;
		life = lifetime;
	}

	bool ParticleSystem::isActive() const
	{
		return active;
	}

	bool ParticleSystem::isEmpty() const
	{
		return pStart == pLast;
	}

	bool ParticleSystem::isFull() const
	{
		return pLast == pEnd;
	}

	void ParticleSystem::draw(float x, float y) const
	{
		if(sprite == 0) return; // just in case of failure

		glPushMatrix();

		glTranslatef(x,y,0.0f);

		particle * p = pStart;
		while(p != pLast)
		{
			glPushMatrix();

			glColor4f(p->color[0],p->color[1],p->color[2],p->color[3]);
			glTranslatef(p->position[0],p->position[1],0.0f);
			glRotatef(p->rotation * 57.29578f, 0.0f, 0.0f, 1.0f); // rad * (180 / pi)
			glScalef(p->size,p->size,1.0f);
			sprite->draw(0,0);

			glPopMatrix();
			p++;
		}

		/**
		OLD CODE
		glDisable(GL_TEXTURE_2D);

		glVertexPointer(2, GL_FLOAT, sizeof(particle), pStart->position);
		glColorPointer(4, GL_FLOAT, sizeof(particle), pStart->color);
	
		// Enable vertex arrays (for great justice, etc).
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		// This. Is. Speed.
		glDrawArrays(GL_POINTS, 0, (GLsizei)(pLast - pStart));
		
		// Disable vertex arrays and clear color buffer to remove "footprint".
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glEnable(GL_TEXTURE_2D);
		*/

		glColor4ub(255,255,255,255);

		glPopMatrix();
	}

	void ParticleSystem::update(float dt)
	{
		// Traverse all particles and update.
		particle * p = pStart;

		// Make some more particles.
		if(active)
		{
			int particles = (int)(emissionRate * dt);
			for(int i = 0; i != particles; i++)
				add();

			life -= dt;
			if(lifetime != -1 && life < 0)
				stop();
		}

		while(p != pLast)
		{
			// Decrease lifespan.
			p->life -= dt;

			if(p->life > 0)
			{
				// Apply gravity.
				p->speed[1] += p->gravity * dt;

				// Apply radial and tangential acceleration.
				p->speed[0] += ((p->tangentialAcceleration * dt) * cos(p->direction)) - ((-p->radialAcceleration * dt) * sin(p->direction));
				p->speed[1] += -( ((p->tangentialAcceleration * dt) * sin(p->direction)) + ((-p->radialAcceleration * dt) * cos(p->direction)) );

				// Modify position.
				p->position[0] += p->speed[0] * dt;
				p->position[1] += p->speed[1] * dt;

				const float t = p->life / p->lifetime;

				// Change size.
				p->size = p->sizeEnd - ((p->sizeEnd - p->sizeStart) * t);

				// Rotate.
				p->rotation = p->rotationEnd - ((p->rotationEnd - p->rotationStart) * t);

				// Update color.
				p->color[0] = (float)(colorEnd->getRed()*(1.0f-t) + colorStart->getRed() * t)/255.0f;
				p->color[1] = (float)(colorEnd->getGreen()*(1.0f-t) + colorStart->getGreen() * t)/255.0f;
				p->color[2] = (float)(colorEnd->getBlue()*(1.0f-t) + colorStart->getBlue() * t)/255.0f;
				p->color[3] = (float)(colorEnd->getAlpha()*(1.0f-t) + colorStart->getAlpha() * t)/255.0f;
	
				// Next particle.
				p++;
			}
			else
			{
				remove(p);

				if(p >= pLast)
					return;
			} // else
		} // while
	}
}
