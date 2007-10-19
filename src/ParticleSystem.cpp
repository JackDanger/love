#include "ParticleSystem.h"
#include <cmath>
#include "AnimatedColor.h"
#include "love.h"

const float pi = 3.14159265f;
const float to_rad = (pi/180.0f);

namespace love
{

	ParticleSystem::ParticleSystem() : spawnBuffer(0), lifetime(-1), age(0), linger(0), additive(true)
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

	ParticleSystem::~ParticleSystem()
	{
	}

	float ParticleSystem::getT(particle & p) const
	{
		return p.age/p.life;
	}

	Vector ParticleSystem::getPosition(particle & p) const
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

	void ParticleSystem::estimateStart(particle & p)
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

	void ParticleSystem::displace(particle & p, float dt)
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

	float ParticleSystem::getScalar(interval & i) const
	{
		float r = ((float)(rand() % 100))/100.0f;
		return i.min + i.delta * r;
	}

	interval ParticleSystem::getInterval(interval & i) const
	{
		interval t;
		t.min = i.min;
		t.max = i.max;
		t.var = i.var;
		t.delta = i.delta;
		return t;
	}

	void ParticleSystem::fillInterval(interval & i, float min, float max, float var)
	{
		i.min = min;
		i.max = max;
		i.delta = max - min;
		i.var = var;
	}

	Vector ParticleSystem::getDirection(float angle) const
	{
		return Vector(sin(angle * to_rad), cos(angle * to_rad));
	}

	int ParticleSystem::load()
	{
		return LOVE_OK;
	}

	void ParticleSystem::unload()
	{
		
	}

	void ParticleSystem::spawn(float age)
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

	void ParticleSystem::setAutostart(bool autoStart)
	{
		if(!autoStart)
			age = lifetime;
	}

	int ParticleSystem::getNumParticles() const
	{
		return (int)particles.size();
	}

	const list<particle> & ParticleSystem::getParticles() const
	{
		return particles;
	}

	const pSprite & ParticleSystem::getSprite() const
	{
		return sprite;
	}

	const pAnimatedColor & ParticleSystem::getColor() const
	{
		return color;
	}

	bool ParticleSystem::isAdditive() const
	{
		return additive;
	}

	void ParticleSystem::reset()
	{
		age = 0;
		spawnBuffer = 0;
	}

	void ParticleSystem::setPosition(float x, float y)
	{
		pos.setX(x);
		pos.setY(y);
	}

	float ParticleSystem::getLifetime() const
	{
		return lifetime;
	}

	void ParticleSystem::setLifetime(float lifetime)
	{
		this->lifetime = lifetime;
	}

	void ParticleSystem::setLinger(float linger)
	{
		this->linger = linger;
	}

	float ParticleSystem::getLinger()
	{
		return linger;
	}

	float ParticleSystem::getAge() const
	{
		return age;
	}

	bool ParticleSystem::isDead() const
	{
		if(lifetime == -1) return false;

		return age >= lifetime + linger;
	}

	bool ParticleSystem::isActive() const
	{
		if(lifetime == -1) return false;

		return age >= lifetime;
	}

	void ParticleSystem::setSprite(const pSprite * sprite)
	{
		this->sprite = *sprite;
	}

	void ParticleSystem::setSprite(const pAbstractImage * sprite)
	{
		this->sprite = (pSprite)(*sprite);
	}

	void ParticleSystem::setSprite(const pFrameAnimation * sprite)
	{
		this->sprite = (pSprite)(*sprite);
	}

	void ParticleSystem::setAdditiveBlending(bool additive)
	{
		this->additive = additive;
	}

	void ParticleSystem::setParticlesPerSecond(float particlesPerSecond)
	{
		this->particlesPerSecond = particlesPerSecond;
		this->spawnFreq = 1.0f/particlesPerSecond;
	}

	void ParticleSystem::addColor(int r, int g, int b, int a, float time)
	{
		color->addColor(r, g, b, a, time);
	}

	void ParticleSystem::addColor(const pColor * color, float time)
	{
		this->color->addColor(color, time);
	}

	void ParticleSystem::setDirection(float min, float max, float var)
	{
		fillInterval(direction, min, max, var);
	}

	void ParticleSystem::setDirection(float m)
	{
		fillInterval(direction, m, m);
	}

	void ParticleSystem::setStartSpeed(float min, float max, float var)
	{
		fillInterval(startSpeed, min, max, var);
	}

	void ParticleSystem::setStartSpeed(float m)
	{
		fillInterval(startSpeed, m, m);
	}

	void ParticleSystem::setGravity(float min, float max, float var)
	{
		fillInterval(gravity, min, max, var);
	}

	void ParticleSystem::setGravity(float m)
	{
		fillInterval(gravity, m, m);
	}

	void ParticleSystem::setRadialAcc(float min, float max, float var)
	{
		fillInterval(radialAcc, min, max, var);
	}

	void ParticleSystem::setRadialAcc(float m)
	{
		fillInterval(radialAcc, m, m);
	}

	void ParticleSystem::setTangentialAcc(float min, float max, float var)
	{
		fillInterval(tangentialAcc, min, max, var);
	}

	void ParticleSystem::setTangentialAcc(float m)
	{
		fillInterval(tangentialAcc, m, m);
	}

	void ParticleSystem::setParticleLifetime(float min, float max, float var)
	{
		fillInterval(particleLifetime, min, max, var);
	}

	void ParticleSystem::setParticleLifetime(float m)
	{
		fillInterval(particleLifetime, m, m);
	}

	void ParticleSystem::setParticleSize(float min, float max, float var)
	{
		fillInterval(particleSize, min, max, var);
	}

	void ParticleSystem::setParticleSize(float m)
	{
		fillInterval(particleSize, m, m);
	}

	void ParticleSystem::setParticleSpin(float min, float max, float var)
	{
		fillInterval(particleSpin, min, max, var);
	}

	void ParticleSystem::setParticleSpin(float m)
	{
		fillInterval(particleSpin, m, m);
	}

	void ParticleSystem::update(float dt)
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

	void ParticleSystem::render()
	{

		// Additive blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_TEXTURE_2D);

		// Iterate through particles and render
		list<particle>::iterator iter;


		//float quadratic[] =  { 1.0f, 1.0f, 1.0f };
		//glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, quadratic );

		// Query for the max point size supported by the hardware
		//float maxSize = 0.0f;
		//glGetFloatv( GL_POINT_SIZE_MAX, &maxSize );

		// Clamp size to 100.0f or the sprites could get a little too big on some  
		// of the newer graphic cards. My ATI card at home supports a max point 
		// size of 1024.0f!
		//if( maxSize > 100.0f )
		//	maxSize = 100.0f;

		//glPointSize( 32 );

		// The alpha of a point is calculated to allow the fading of points 
		// instead of shrinking them past a defined threshold size. The threshold 
		// is defined by GL_POINT_FADE_THRESHOLD_SIZE_ARB and is not clamped to 
		// the minimum and maximum point sizes.
		//glPointParameterf( GL_POINT_FADE_THRESHOLD_SIZE, 60.0f );

		//glPointParameterf( GL_POINT_SIZE_MIN, 1.0f );
		//glPointParameterf( GL_POINT_SIZE_MAX, maxSize );


		//glTexEnvf( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );
		//glEnable(GL_POINT_SPRITE);	

		sprite->bind();
		//sprite->beginRender();

		for(iter = particles.begin(); iter != particles.end(); iter++ )
		{

			float t = iter->age/iter->life;

			// Set the color
			Color c = color->getColor(t);
			glColor4ub(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());

			// Set the size
			float sd = iter->size.max - iter->size.min;
			float s = iter->size.min + sd * t;
			
			float x = iter->pos.getX();
			float y = iter->pos.getY();
					
			// Old: 234 fps


			// Render
			//glVertex2f(ppos.getX(),ppos.getY());
			renderinfo r = sprite->getRenderInfo();
			float xfac = r.width/2.0f;
			float yfac = r.height/2.0f;


		

			glPushMatrix();
			glTranslatef(x, y, 0);
			glScalef(s, s, 0);
			glRotatef(iter->angle, 0, 0, 1);

			glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(-xfac,-yfac);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(-xfac,yfac);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(xfac,yfac);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(xfac,-yfac);
			glEnd();

			glPopMatrix();
			
			

			/**
			// About 25 fps
			glPushMatrix();
			glTranslatef(ppos.getX(), ppos.getY(), 0);
			glScalef(s, s, 0);
			this->sprite->render();
			glPopMatrix();
			**/
		}

		

		//glDisable(GL_POINT_SPRITE);

		// Normal blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}



}// love
