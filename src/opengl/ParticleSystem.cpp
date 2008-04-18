#include "ParticleSystem.h"

#include <SDL_opengl.h>

namespace love_opengl
{
	//
	// Struct constructor.
	//

	particle::particle()
	{
		// position
		position[0] = 0.0f;
		position[1] = 0.0f;

		// random direction
		direction[0] = (10000 - rand()%20000)/100.0f;
		direction[1] = (10000 - rand()%20000)/100.0f;

		// random colour
		color[0] = 0.8f;
		color[1] = rand()%15000/20000.0f;
		color[2] = 0.1f;

		// random lifespan
		life = rand()%30000/9500.0f;
	}

	//
	// Class functions.
	//

	ParticleSystem::ParticleSystem(unsigned int buffer) : start(0), last(0), end(0), shoot(0)
	{
		setBufferSize(buffer);
	}

	ParticleSystem::~ParticleSystem()
	{}

	void ParticleSystem::add()
	{
		if(!isFull())
		{
			*last = particle();
			last++;
		}
	}

	void ParticleSystem::remove(particle * p)
	{
		if(!isEmpty())
		{
			*p = *(--last);
		}
	}

	void ParticleSystem::setBufferSize(unsigned int size)
	{
		// delete previous data
		delete [] start;

		last = start = new particle[size];

		end = start + size;
	}

	unsigned int ParticleSystem::getBufferSize() const
	{
		return (unsigned int)(end - start);
	}

	int ParticleSystem::count() const
	{
		return (int)(last - start);
	}

	bool ParticleSystem::isEmpty() const
	{
		return start == last;
	}

	bool ParticleSystem::isFull() const
	{
		return last == end;
	}

	void ParticleSystem::draw(float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x,y,0.0f);

		glDisable(GL_TEXTURE_2D);

		glVertexPointer(2, GL_FLOAT, sizeof(particle), start->position);
		glColorPointer(3, GL_FLOAT, sizeof(particle), start->color);

		// Enable vertex arrays (for great justice, etc).
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// This. Is. Speed.
		glDrawArrays(GL_POINTS, 0, (GLsizei)(last-start));

		// Disable vertex arrays and clear color buffer to remove "footprint".
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glColor4ub(255,255,255,255);

		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	void ParticleSystem::update(float dt)
	{
		// traverse all particles and update
		particle * p = start;

		while(p!=last)
		{
			// decrease lifespan
			p->life -= dt;

			// if we have life left
			if(p->life > 0)
			{
				// apply gravity
				p->direction[1] += 100*dt;
	
				// modify position
				p->position[0] += dt * p->direction[0];
				p->position[1] += dt * p->direction[1];
	
				p->color[0] *= (float)(1-0.3*dt);
				p->color[1] *= (float)(1-0.3*dt);
				p->color[2] *= (float)(1-0.3*dt);
	
				// goto next particle
				p++;
			}
			else
			{
				remove(p);

				if(p >= last)
					return;
			} // else
		} // while

		int val = rand()%1000;
		for(int i=0;i!=val;++i)
			add();

		shoot += dt;
		if(shoot >= 3)
		{
			//printf("Particles: %d   FPS: %d\n", last-start, getFPS());
			shoot -= 3;
		}
	}
}
