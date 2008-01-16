#include "OpenGLParticleSystem.h"

#include "using_gl.h"

using std::list;

namespace love
{

	OpenGLParticleSystem::OpenGLParticleSystem()
	{
	}

	OpenGLParticleSystem::~OpenGLParticleSystem()
	{
	}

	void OpenGLParticleSystem::render() const
	{

		// Additive blending
		if(additive)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnable(GL_TEXTURE_2D);

		// Iterate through particles and render
		list<particle>::const_iterator iter;

		for(iter = particles.begin(); iter != particles.end(); iter++ )
		{
			float t = iter->age/iter->life;

			pColor c = color->getColor(t);

			// Set the color
			glColor4ub(c->getRed(), c->getGreen(), c->getBlue(), c->getAlpha());

			// Set the size
			float sd = iter->size.max - iter->size.min;
			float s = iter->size.min + sd * t;
			
			float x = iter->pos.getX();
			float y = iter->pos.getY();

			glPushMatrix();
			glTranslatef(x, y, 0);
			glScalef(s, s, 0);
			glRotatef(iter->angle, 0, 0, 1);
			sprite->render(- sprite->getWidth()/2.0f, - sprite->getHeight()/2.0f);
			glPopMatrix();
			
		}

		// Normal blending
		if(additive)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor3f(1, 1, 1);
	}

	void OpenGLParticleSystem::render(float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		render();
		glPopMatrix();
	}

}// love
