#include "Particle.h"
#include "ParticleEmitter.h"
#include "love.h"

namespace love
{
	Particle::Particle()
	{
		load();
		setType(LOVE_TYPE_PARTICLE);
	}

	Particle::Particle(ParticleEmitter * parent)
	{
		load();
		this->parent = parent;
		setType(LOVE_TYPE_PARTICLE);
	}

	Particle::~Particle()
	{
	}

	float Particle::getLife()
	{
		return life;
	}

	float Particle::getLifetime()
	{
		return lifetime;
	}

	bool Particle::getFade()
	{
		return fade;
	}

	bool Particle::isAlive()
	{
		if(lifetime >= life)
			return false;
		else
			return true;
	}

	void Particle::setLife(float life)
	{
		this->life = life;
	}

	void Particle::setLifetime(float lifetime)
	{
		this->lifetime = lifetime;
	}
	
	void Particle::setFade(bool fade)
	{
		this->fade = fade;
	}

	void Particle::setSprite(Sprite * sprite)
	{
		this->sprite = sprite;
	}

	void Particle::setSprite(const char * name)
	{
		this->sprite = parent->getSprite(name);
	}

	void Particle::init()
	{
		if(parent != 0)
			setPosition(parent->getX(), parent->getY());
	}

	void Particle::update(float dt)
	{
		lifetime += dt;
		if(fade)
		{
			float o = (((life - lifetime) / life) * 255);
			if(o < 0) o = 0;
			this->setOpacity((unsigned char)o);
		}
		VisualEntity::update(dt);
	}

	void Particle::render()
	{
		VisualEntity::render();
	}

	int Particle::load()
	{
		parent = 0;
		life = 0;
		lifetime = 0;
		fade = true;
		VisualEntity::load();

		return LOVE_OK;
	}

	void Particle::unload()
	{
	}
}
