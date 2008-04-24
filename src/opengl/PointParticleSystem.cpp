#include "PointParticleSystem.h"

#include <SDL_opengl.h>
#include <cmath>

namespace love_opengl
{
	PointParticleSystem::PointParticleSystem(pImage sprite, unsigned int buffer)
		: ParticleSystem(sprite, buffer)
	{
	}


	void PointParticleSystem::draw(float x, float y) const
	{
		if(sprite == 0) return; // just in case of failure

		glEnable( GL_POINT_SPRITE );

		sprite->bind();

		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glTexEnvf( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );

		glTranslatef(x,y,0.0f);
		glPointSize( 100 );
		
		/**
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
		**/

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

		glPopAttrib();
		glPopMatrix();

		glDisable( GL_POINT_SPRITE );
	}
}
