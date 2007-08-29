#include "BezierParticleSystem.h"

namespace love
{
	
	BezierParticleSystem::BezierParticleSystem() : current(0), precision(200)
	{
	}
	
	BezierParticleSystem::~BezierParticleSystem()
	{
	}

	void BezierParticleSystem::setBezier(const pBezier * bezier)
	{
		this->bezier = (*bezier);
	}

	void BezierParticleSystem::setPrecision(int precision)
	{
		this->precision = precision;
	}

	void BezierParticleSystem::setSpeed(float time)
	{
		speed = time;
	}

	void BezierParticleSystem::update(float dt)
	{

		if(age >= lifetime)
		{
			ParticleSystem::update(dt);
			return;
		}

		// How much t we should move per particle.
		float p = 1.0f/(float)(precision-1);

		// Find current number of particles.
		current = ((age/speed) * (float)precision);

		if(current >= (float)precision - 1)
			current = (float)precision - 2;

		int psize = (int)particles.size();

		while(current > psize)
		{
			spawn(current*p);
			particles.back().pos = bezier != 0 ? bezier->getPoint(current*p) : Vector(0, 0);
			current--;
		}

		// Update particle system age.
		age += dt;

	}
	
	/**
	void BezierParticleSystem::render()
	{

		if(isDead())
			return;

		// Additive blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_TEXTURE_2D);


		sprite->bind();


		int num = precision;
		float p = 1.0f/(float)(num-1);


		for(int i = 0;i<current;i++)
		{

			float t = i*p;

			// Set the color
			color->setColor(t);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());

			// Set the size
			float s = particleSize.min + particleSize.delta * t;
			float a = particleSpin.min + particleSpin.delta * t;
			
			Vector v = bezier != 0 ? bezier->getPoint(t) : Vector(0, 0);
			float x = v.getX();
			float y = v.getY();
					
			// Old: 234 fps


			// Render
			//glVertex2f(ppos.getX(),ppos.getY());
			renderinfo r = sprite->getRenderInfo();
			float xfac = r.width/2.0f;
			float yfac = r.height/2.0f;


		

			glPushMatrix();
			glTranslatef(x, y, 0);
			glScalef(s, s, 0);
			glRotatef(a, 0, 0, 1);

			glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(-xfac,-yfac);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(-xfac,yfac);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(xfac,yfac);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(xfac,-yfac);
			glEnd();

			glPopMatrix();

		}

		// Normal blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	**/

} // love
