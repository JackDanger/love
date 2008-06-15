#include "ParticleSystem.h"

#include <SDL_opengl.h>
#include <cmath>

namespace love_opengl
{

	float calculate_variation(float inner, float outer, float var)
	{
		float low = inner - (outer/2.0f)*var;
		float high = inner + (outer/2.0f)*var;
		float r = (rand() / (float(RAND_MAX)+1));
		return low*(1-r)+high*r;
	}


	ParticleSystem::ParticleSystem(pImage sprite, unsigned int buffer) : pStart(0), pLast(0), pEnd(0), active(true), emissionRate(0),
															emitCounter(0), lifetime(-1), life(0), particleLifeMin(0), particleLifeMax(0),
															direction(0), spread(0), relative(false), speedMin(0), speedMax(0), gravityMin(0),
															gravityMax(0), radialAccelerationMin(0), radialAccelerationMax(0),
															tangentialAccelerationMin(0), tangentialAccelerationMax(0),
															sizeStart(1), sizeEnd(1), sizeVariation(0), spinStart(0),
															spinEnd(0), spinVariation(0)
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
		if(isFull()) return;
		
		float min,max;

		min = particleLifeMin;
		max = particleLifeMax;
		if(min == max)
			pLast->life = min;
		else
			pLast->life = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
		pLast->lifetime = pLast->life;

		pLast->position = position;

		min = direction - spread/2.0f;
		max = direction + spread/2.0f;
		pLast->direction = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

		min = speedMin;
		max = speedMax;
		float speed = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;
		pLast->speed = love::Vector(cos(pLast->direction), sin(pLast->direction));
		pLast->speed *= speed;

		min = gravityMin;
		max = gravityMax;
		pLast->gravity = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

		min = radialAccelerationMin;
		max = radialAccelerationMax;
		pLast->radialAcceleration = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

		min = tangentialAccelerationMin;
		max = tangentialAccelerationMax;
		pLast->tangentialAcceleration = (rand() / (float(RAND_MAX)+1)) * (max - min) + min;

		pLast->sizeStart = calculate_variation(sizeStart, sizeEnd, sizeVariation);
		pLast->sizeEnd = calculate_variation(sizeEnd, sizeStart, sizeVariation);
		pLast->size = pLast->sizeStart;

		pLast->spinStart = calculate_variation(spinStart, spinEnd, spinVariation);
		pLast->spinEnd = calculate_variation(spinEnd, spinStart, spinVariation);
		pLast->rotation = 0;

		pLast->color[0] = (float)colorStart->getRed() / 255;
		pLast->color[1] = (float)colorStart->getGreen() / 255;
		pLast->color[2] = (float)colorStart->getBlue() / 255;
		pLast->color[3] = (float)colorStart->getAlpha() / 255;
			
		pLast++;
	}

	void ParticleSystem::remove(particle * p)
	{
		if(!isEmpty())
		{
			*p = *(--pLast);
		}
	}

	void ParticleSystem::setSprite(pImage sprite)
	{
		this->sprite = sprite;
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

	void ParticleSystem::setPosition(float x, float y)
	{
		//if(relative)
			//direction = atan2(y, x) - atan2(position[1], position[0]);
		//	direction = atan2(y - position[1], x - position[0]) - (3.14159265/2);
		position = love::Vector(x, y);
	}

	void ParticleSystem::setDirection(float direction)
	{
		this->direction = direction*(float)M_TORAD;
	}

	void ParticleSystem::setSpread(float spread)
	{
		this->spread = spread*(float)M_TORAD;
	}

	void ParticleSystem::setRelativeDirection(bool relative)
	{
		this->relative = relative;
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

	void ParticleSystem::setSpin(float spin)
	{
		spinStart = spin*(float)M_TORAD;
		spinEnd = spin*(float)M_TORAD;
	}

	void ParticleSystem::setSpin(float start, float end)
	{
		spinStart = start*(float)M_TORAD;
		spinEnd = end*(float)M_TORAD;
	}

	void ParticleSystem::setSpin(float start, float end, float variation)
	{
		spinStart = start*(float)M_TORAD;
		spinEnd = end*(float)M_TORAD;
		spinVariation = variation*(float)M_TORAD;
	}

	void ParticleSystem::setSpinVariation(float variation)
	{
		spinVariation = variation*(float)M_TORAD;
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

	float ParticleSystem::getDirection()
	{
		return direction;
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
		emitCounter = 0;
	}

	void ParticleSystem::pause()
	{
		active = false;
	}

	void ParticleSystem::reset()
	{
		pLast = pStart;
		life = lifetime;
		emitCounter = 0;
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
		glPushAttrib(GL_CURRENT_BIT);

		glTranslatef(x,y,0.0f);

		particle * p = pStart;
		while(p != pLast)
		{
			glPushMatrix();

			glColor4f(p->color[0],p->color[1],p->color[2],p->color[3]);
			glTranslatef(p->position.getX(),p->position.getY(),0.0f);
			glRotatef(p->rotation * 57.29578f, 0.0f, 0.0f, 1.0f); // rad * (180 / pi)
			glScalef(p->size,p->size,1.0f);
			sprite->draw(0,0);

			glPopMatrix();
			p++;
		}

		glPopAttrib();
		glPopMatrix();
	}

	void ParticleSystem::update(float dt)
	{
		// Traverse all particles and update.
		particle * p = pStart;

		// Make some more particles.
		if(active)
		{
			float rate = 1.0f / emissionRate; // the amount of time between each particle emit
			emitCounter += dt;
			while(emitCounter > rate)
			{
				add();
				emitCounter -= rate;
			}
			/*int particles = (int)(emissionRate * dt);
			for(int i = 0; i != particles; i++)
				add();*/

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

				// Temp variables.
				love::Vector radial, tangential, gravity(0, p->gravity);

				// Get vector from particle center to particle.
				radial = p->position - position;
				radial.normalize();
				tangential = radial;

				// Resize radial acceleration.
				radial *= p->radialAcceleration;

				// Calculate tangential acceleration.
				{
					float a = tangential.getX();
					tangential.setX(-tangential.getY());
					tangential.setY(a);
				}

				// Resize tangential.
				tangential *= p->tangentialAcceleration;

				// Update position.
				p->speed += (radial+tangential+gravity)*dt;

				// Modify position.
				p->position += p->speed * dt;

				const float t = p->life / p->lifetime;

				// Change size.
				p->size = p->sizeEnd - ((p->sizeEnd - p->sizeStart) * t);

				// Rotate.
				p->rotation += (p->spinStart*(1-t) + p->spinEnd*t)*dt;

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
