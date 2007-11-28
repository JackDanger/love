#include "OpenGLParticleSystem.h"
#include <cmath>
#include "AnimatedColor.h"
#include "love.h"

const float pi = 3.14159265f;
const float to_rad = (pi/180.0f);

namespace love
{

	OpenGLParticleSystem::OpenGLParticleSystem()
	{
	}

	OpenGLParticleSystem::~OpenGLParticleSystem()
	{
	}

	void OpenGLParticleSystem::render()
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
			pAbstractColor c = color->getColor(t);
			glColor4ub(c->getRed(), c->getGreen(), c->getBlue(), c->getAlpha());

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

	void OpenGLParticleSystem::render(float x, float y)
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		render();
		glPopMatrix();
	}


}// love
