#include "Particlesystem.h"

// LOVE
#include "love_math.h"



// STD
#include <cmath>

using std::list;

namespace love
{

	Particlesystem::Particlesystem() : additive(true), lifetime(-1), age(0), linger(0), spawnBuffer(0)
	{
		// Init members
		fillInterval(direction, 0, 360);
		fillInterval(startSpeed, 100, 200);
		fillInterval(gravity, 0, 0);
		fillInterval(radialAcc, 0, 0);
		fillInterval(tangentialAcc, 0, 0);
		fillInterval(particleLifetime, 1, 2);
		fillInterval(particleSize, 1, 2);
		fillInterval(particleSpin, 0, 0);
		color.reset<AnimatedColor>(new AnimatedColor());

	}

	Particlesystem::~Particlesystem()
	{
	}

	float Particlesystem::getT(particle & p) const
	{
		return p.age/p.life;
	}

	Vector Particlesystem::getPosition(particle & p) const
	{

		// Get gravity.
		Vector gravity(0, p.gravity);

		// Get radial acceleration.
		Vector radial;

		radial = p.pos - pos;
		radial.normalize();
		radial *= p.radialAcc;

		Vector acc = gravity + radial;

		float t = p.age;

		return pos + p.speed * t + acc * t * t;
	}

	void Particlesystem::estimateStart(particle & p)
	{
		// Get gravity.
		Vector gravity(0, p.gravity);

		// Get radial acceleration.
		Vector radial;

		radial = p.direction;
		radial.normalize();
		radial *= p.radialAcc;

		Vector acc = gravity + radial;

		float t = p.age;

		p.angle = p.spin * t;

		p.pos = pos + p.speed * t + acc * t * t;		
	}

	void Particlesystem::displace(particle & p, float dt)
	{
		// Get gravity.
		Vector gravity(0, p.gravity);

		// Get radial acceleration.
		Vector radial = p.pos - pos;
		radial.normalize();

		Vector tangential(-radial.getY(), radial.getX());

		radial *= p.radialAcc;
		tangential *= p.tangentialAcc;

		Vector acc = gravity + radial + tangential;

		p.speed += acc * dt;
		p.pos += p.speed * dt;

	}

	float Particlesystem::getScalar(interval & i) const
	{
		float r = ((float)(rand() % 100))/100.0f;
		return i.min + i.delta * r;
	}

	interval Particlesystem::getInterval(interval & i) const
	{
		interval t;
		t.min = i.min;
		t.max = i.max;
		t.var = i.var;
		t.delta = i.delta;
		return t;
	}

	void Particlesystem::fillInterval(interval & i, float min, float max, float var)
	{
		i.min = min;
		i.max = max;
		i.delta = max - min;
		i.var = var;
	}

	Vector Particlesystem::getDirection(float angle) const
	{
		return Vector(sin(angle * to_rad), cos(angle * to_rad));
	}

	void Particlesystem::spawn(float age)
	{

		// Add one particle
		particle p;
		p.age = age;
		p.angle = 0;

		// Use spread to get random direction
		p.direction = getDirection(getScalar(direction));
		p.direction.normalize();
		p.speed = p.direction;
		p.speed *= getScalar(startSpeed);
		p.life = getScalar(particleLifetime);
		p.gravity = getScalar(gravity);
		p.radialAcc = getScalar(radialAcc);
		p.tangentialAcc = getScalar(tangentialAcc);
		p.spin = getScalar(particleSpin);
		p.size = particleSize;

		// Estimate starting point
		estimateStart(p);

		particles.push_back(p);
	}

	void Particlesystem::setAutostart(bool autoStart)
	{
		if(!autoStart)
			age = lifetime;
	}

	int Particlesystem::getNumParticles() const
	{
		return (int)particles.size();
	}

	const list<particle> & Particlesystem::getParticles() const
	{
		return particles;
	}

	const pSprite & Particlesystem::getSprite() const
	{
		return sprite;
	}

	bool Particlesystem::isAdditive() const
	{
		return additive;
	}

	void Particlesystem::reset()
	{
		age = 0;
		spawnBuffer = 0;
	}

	void Particlesystem::setPosition(float x, float y)
	{
		pos.setX(x);
		pos.setY(y);
	}

	float Particlesystem::getLifetime() const
	{
		return lifetime;
	}

	void Particlesystem::setLifetime(float lifetime)
	{
		this->lifetime = lifetime;
	}

	void Particlesystem::setLinger(float linger)
	{
		this->linger = linger;
	}

	float Particlesystem::getLinger()
	{
		return linger;
	}

	float Particlesystem::getAge() const
	{
		return age;
	}

	bool Particlesystem::isDead() const
	{
		if(lifetime == -1) return false;

		return age >= lifetime + linger;
	}

	bool Particlesystem::isActive() const
	{
		if(lifetime == -1) return false;

		return age >= lifetime;
	}

	void Particlesystem::setSprite(pSprite sprite)
	{
		this->sprite = sprite;
	}

	void Particlesystem::setAdditiveBlending(bool additive)
	{
		this->additive = additive;
	}

	void Particlesystem::setParticlesPerSecond(float particlesPerSecond)
	{
		this->particlesPerSecond = particlesPerSecond;
		this->spawnFreq = 1.0f/particlesPerSecond;
	}


	void Particlesystem::addColor(int r, int g, int b, int a, float time)
	{
		this->color->addColor(r, g, b, a, time);
	}

	void Particlesystem::setDirection(float min, float max, float var)
	{
		fillInterval(direction, min, max, var);
	}

	void Particlesystem::setDirection(float m)
	{
		fillInterval(direction, m, m);
	}

	void Particlesystem::setStartSpeed(float min, float max, float var)
	{
		fillInterval(startSpeed, min, max, var);
	}

	void Particlesystem::setStartSpeed(float m)
	{
		fillInterval(startSpeed, m, m);
	}

	void Particlesystem::setGravity(float min, float max, float var)
	{
		fillInterval(gravity, min, max, var);
	}

	void Particlesystem::setGravity(float m)
	{
		fillInterval(gravity, m, m);
	}

	void Particlesystem::setRadialAcc(float min, float max, float var)
	{
		fillInterval(radialAcc, min, max, var);
	}

	void Particlesystem::setRadialAcc(float m)
	{
		fillInterval(radialAcc, m, m);
	}

	void Particlesystem::setTangentialAcc(float min, float max, float var)
	{
		fillInterval(tangentialAcc, min, max, var);
	}

	void Particlesystem::setTangentialAcc(float m)
	{
		fillInterval(tangentialAcc, m, m);
	}

	void Particlesystem::setParticleLifetime(float min, float max, float var)
	{
		fillInterval(particleLifetime, min, max, var);
	}

	void Particlesystem::setParticleLifetime(float m)
	{
		fillInterval(particleLifetime, m, m);
	}

	void Particlesystem::setParticleSize(float min, float max, float var)
	{
		fillInterval(particleSize, min, max, var);
	}

	void Particlesystem::setParticleSize(float m)
	{
		fillInterval(particleSize, m, m);
	}

	void Particlesystem::setParticleSpin(float min, float max, float var)
	{
		fillInterval(particleSpin, min, max, var);
	}

	void Particlesystem::setParticleSpin(float m)
	{
		fillInterval(particleSpin, m, m);
	}

	void Particlesystem::update(float dt)
	{
		
		spawnBuffer += dt;
		
		// Spawn correct amount of particles
		while(!isActive() && spawnBuffer >= spawnFreq)
		{
			spawnBuffer -= spawnFreq;
			spawn(spawnBuffer);
		}

		// Iterate through particles and update/remove
		list<particle>::iterator iter = particles.begin();


		while(iter != particles.end())
		{

			// Update time
			iter->age += dt;

			// Displace particle
			displace(*iter, dt);
			iter->angle += iter->spin * dt;

			// Lastday reached?
			if(iter->age >= iter->life)
				particles.erase(iter++);	
			else
				++iter;

		}

		// Update particle system age.
		age += dt;
	}


}// love
