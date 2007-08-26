#include "ParticleEmitter.h"
#include "love.h"

namespace love
{
	ParticleEmitter::ParticleEmitter(lua_State * state, Container<Sprite> * sprites)
	{
		load();
		L = state;
		this->sprites = sprites;
		setType(LOVE_TYPE_PARTICLE_EMITTER);
	}

	ParticleEmitter::ParticleEmitter(float delay, int mode)
	{
		load();
		if(mode != 0)
			this->mode = mode;
		this->delay = delay;
		setType(LOVE_TYPE_PARTICLE_EMITTER);
	}

	ParticleEmitter::~ParticleEmitter()
	{
	}

	ScriptableParticle * ParticleEmitter::addParticle(const char * name, ScriptableParticle * newParticle)
	{
		if(!models.contains(name))
			models.create(name, newParticle);
		return models[name].get();
	}

	ScriptableParticle * ParticleEmitter::addParticle(const char * name)
	{
		if(!models.contains(name))
			models.create(name, new ScriptableParticle(this, 0, ""));
		return models[name].get();
	}

	ScriptableParticle * ParticleEmitter::addParticle(const char * name, const char * script)
	{
		if(!models.contains(name))
		{
			if(L == 0)
				models.create(name, new ScriptableParticle(this, 0, ""));
			else
				models.create(name, new ScriptableParticle(this, L, script));
		}
		return models[name].get();
		return 0;
	}

	ScriptableParticle * ParticleEmitter::getParticle(const char * name)
	{
		if(models.contains(name))
			return models[name].get();
		else
			return 0;
	}

	Sprite * ParticleEmitter::getSprite(const char * name)
	{
		printf("getsprite amount: %d\n", sprites->size());

		if(sprites != 0 && sprites->contains(name))
			return (*sprites)[name].get();
		else
			return 0;
	}

	int ParticleEmitter::getMode()
	{
		return mode;
	}

	float ParticleEmitter::getDelay()
	{
		return delay;
	}

	bool ParticleEmitter::isActive()
	{
		return active;
	}

	void ParticleEmitter::setMode(int mode)
	{
		this->mode = mode;
	}

	void ParticleEmitter::setDelay(float delay)
	{
		this->delay = delay;
	}

	void ParticleEmitter::play()
	{
		active = true;
	}

	void ParticleEmitter::stop()
	{
		active = false;
	}

	void ParticleEmitter::update(float dt)
	{
		for(int i = 0; i < (int)particles.size(); i++)
		{
			if(!particles[i].isAlive())
			{
				particles.erase(particles.begin() + i);
			}
			else
			{
				particles[i].update(dt);
			}
			
		}
		
		elapsed += dt;
		if(active && elapsed >= delay)
		{
			elapsed -= delay;
			int i = 0;

			switch(mode)
			{
			case LOVE_PARTICLE_MODE_RANDOM:
				particle = rand() % models.size();

				for(models.begin(); !models.end(); models.next())
				{
					if(i == particle)
					{
						ScriptableParticle temp = *models.value();

						temp.init();
						particles.push_back(temp);
						break;
					}
					else
						i++;
				}
				break;

			case LOVE_PARTICLE_MODE_BOUNCE:
				for(models.begin(); !models.end(); models.next())
				{
					if(i == particle)
					{
						ScriptableParticle temp = *models.value();

						temp.init();
						particles.push_back(temp);
						break;
					}
					else
						i++;
				}

				if(direction) //the right way
				{
					particle++;
					if(particle == models.size())
					{
						particle = particle - 2; //to avoid emitting the same particle twice
						direction = false;
					}
				}
				else //the wrong way
				{
					particle--;
					if(particle == -1)
					{
						particle = 1; //to avoid emitting the same particle twice
						direction = true;
					}
				}
				break;

			case LOVE_PARTICLE_MODE_ONCE:
				for(models.begin(); !models.end(); models.next())
				{
					if(i == particle)
					{
						ScriptableParticle temp = *models.value();

						temp.init();
						particles.push_back(temp);
						break;
					}
					else
						i++;
				}

				particle++;
				if(particle == models.size())
				{
					particle = 0;
					stop();
				}
				break;

			case LOVE_PARTICLE_MODE_SIMULTANEOUS:
				for(models.begin(); !models.end(); models.next())
				{
					ScriptableParticle temp = *models.value();

					temp.init();
					particles.push_back(temp);
				}
				break;

			case LOVE_PARTICLE_MODE_LOOP:
			default: //just in case of a random number, we use loop
				for(models.begin(); !models.end(); models.next())
				{
					if(i == particle)
					{
						ScriptableParticle temp = *models.value();
						
						temp.init();
						particles.push_back(temp);
						break;
					}
					else
						i++;
				}

				particle++;
				if(particle == models.size())
					particle = 0;
				break;
			}

			Entity::update(dt);
		}
	}

	void ParticleEmitter::render()
	{
		for(unsigned int i = 0; i != particles.size(); i++)
		{
			particles[i].render();
		}
	}

	int ParticleEmitter::load()
	{
		srand((unsigned)time(0));

		L = 0;
		sprites = 0;
		particle = 0;
		mode = LOVE_PARTICLE_MODE_LOOP;
		delay = 0;
		elapsed = 0;
		direction = true;
		active = false;

		Entity::load();

		return LOVE_OK;
	}

	void ParticleEmitter::unload()
	{
		models.clear();
		particles.clear();
	}
}