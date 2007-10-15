#include "OpenGLGraphics.h"
#include "AbstractFileSystem.h"
#include "Core.h"
#include "love.h"
#include "Sprite.h"
#include "Text.h"

namespace love
{
	
	OpenGLGraphics::OpenGLGraphics()
	{
		// default color
		color.reset<Color>(new Color(255, 255, 255, 255));
		background.reset<Color>(new Color(0, 0, 0, 255));
	}
	
	OpenGLGraphics::~OpenGLGraphics()
	{
	}

	int OpenGLGraphics::init()
	{	
		return LOVE_OK;
	}

	void OpenGLGraphics::drawSprite(const pSprite & sprite) const
	{
		// Get info of how to render the sprite.
		renderinfo r = sprite->getRenderInfo();

		glColor4ub(255, 255, 255, 255);

		// Bind the texture.
		sprite->bind();

		glPushMatrix();

		//glRotatef(180, 0, 0, 1);
		glTranslatef(-r.left, -r.top, 0);

		// And render it.
		glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(0,0);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(0,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(r.width,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(r.width,0);
		glEnd();

		glPopMatrix();

	}

	void OpenGLGraphics::drawSprite(const pSprite & sprite, float x, float y) const
	{
		// Get info of how to render the sprite.
		renderinfo r = sprite->getRenderInfo();

		glColor4ub(255, 255, 255, 255);

		// Bind the texture.
		sprite->bind();

		glPushMatrix();
		
		glTranslatef(x, y, 0);
		//glRotatef(180, 0, 0, 1);
		glTranslatef(-r.left, -r.top, 0);

		// And render it.
		glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(0,0);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(0,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(r.width,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(r.width,0);
		glEnd();

		glPopMatrix();
	}

	void OpenGLGraphics::drawSprite(const pSprite & sprite, float x, float y, float width, float height) const
	{
		// Get info of how to render the sprite.
		renderinfo r = sprite->getRenderInfo();

		glColor4ub(255, 255, 255, 255);

		// Bind the texture.
		sprite->bind();

		glPushMatrix();

		glTranslatef(x, y, 0);
		//glRotatef(180, 0, 0, 1);
		glTranslatef(-(width/2), -(height/2), 0);

		// And render it.
		glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(0,0);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(0,height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(width,height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(width,0);
		glEnd();

		glPopMatrix();
	}

	void OpenGLGraphics::drawSprite(const pSprite & sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		// Get info of how to render the sprite.
		renderinfo r = sprite->getRenderInfo();

		glColor4ub(255, 255, 255, 255);

		// Bind the texture.
		sprite->bind();

		glPushMatrix();
		glTranslatef(x, y, 0);
		//glRotatef(180, 0, 0, 1);
		glTranslatef(-r.left, -r.top, 0);

		// And render it.
		glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(x1,y1);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(x2,y2);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(x3,y3);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(x4,y4);
		glEnd();

		glPopMatrix();
	}

	void OpenGLGraphics::drawSubSprite(const pSprite & sprite, float x, float y, float width, float height) const
	{
		// Get info of how to render the sprite.
		renderinfo r = sprite->getRenderInfo(x, y, width, height);

		glColor4ub(255, 255, 255, 255);

		// Bind the texture.
		sprite->bind();

		glPushMatrix();

		//glRotatef(180, 0, 0, 1);
		glTranslatef(-r.left, -r.top, 0);

		// And render it.
		glBegin(GL_QUADS);
			glTexCoord2f(r.xTex,r.yTex);				glVertex2f(0,0);
			glTexCoord2f(r.xTex,r.yTex+r.hTex);			glVertex2f(0,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex+r.hTex);	glVertex2f(r.width,r.height);
			glTexCoord2f(r.xTex+r.wTex,r.yTex);			glVertex2f(r.width,0);
		glEnd();

		glPopMatrix();
	}


	void OpenGLGraphics::drawParticleSystem(const pParticleSystem * particleSystem) const
	{
		// Additive blending
		if((*particleSystem)->isAdditive()) 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnable(GL_TEXTURE_2D);

		// Get list of particles.
		const list<particle> & particles = (*particleSystem)->getParticles();

		// Get sprite.
		const pSprite & sprite = (*particleSystem)->getSprite();

		// Get color.
		const pAnimatedColor & color = (*particleSystem)->getColor();


		// Iterate through particles and render
		list<particle>::const_iterator iter;

		sprite->bind();

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

			// Render
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

		}

		// Normal blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLGraphics::drawParticleSystem(const pParticleSystem * particleSystem, float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		drawParticleSystem(particleSystem);
		glPopMatrix();
	}

	void OpenGLGraphics::drawBezier(const pBezier * bezier, float x, float y, int precision, float lineWidth) const
	{
		// Test render bezier curve.
		const vector<Vector> points = (*bezier)->getPoints();

		float p = 1.0f/(float)(precision-1);

		glDisable(GL_TEXTURE_2D);
		glLineWidth(lineWidth);
		glEnable(GL_LINE_SMOOTH);
		glColor4ub(color->getRed(),color->getGreen(), color->getBlue(), color->getAlpha());

		glPushMatrix();
		glTranslatef(x, y, 0);
		glBegin(GL_LINE_STRIP);

		for(int i = 0;i<precision;i++)
		{
			Vector v = (*bezier)->getPoint(i*p);
			glVertex2f(v.getX(), v.getY());
		}

		glEnd();
		glPopMatrix();

		glDisable(GL_LINE_SMOOTH);
	}

	void OpenGLGraphics::drawString(const char * str, float x, float y) const
	{
		glPushMatrix();
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		if(font!=0)
		{
			glColor4ub(color->getRed(),color->getGreen(), color->getBlue(), color->getAlpha());
			font->print(str, x, y);
		}
		glPopMatrix();
	}

	void OpenGLGraphics::drawText(const char * str, float x, float y, float limit, int align) const
	{
		if(font!=0)
		{
			// Create new text object.
			//Text text(0,0);
			Text text(font.get(), color.get());

			// Set some attributes.
			text.align(align);
			text.setLimit(limit);

			// And print.
			text.print(x, y, str, font.get(), color.get());
		}	
	}

	void OpenGLGraphics::drawLine(float x1, float y1, float x2, float y2, float rotation, float lineWidth) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		glLineWidth(lineWidth);
		
		glTranslatef((x1+x2)/2, (y1+y2)/2, 0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glTranslatef(-(x1+x2)/2, -(y1+y2)/2, 0.0f);

		glBegin(GL_LINES);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::drawTriangle(float x, float y, float width, float height, float rotation, float lineWidth) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-(width/2),(height/2));
			glVertex2f(0,-(height/2));
			glVertex2f((width/2),(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::fillTriangle(float x, float y, float width, float height, float rotation) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		//glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f(0,-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::drawRectangle(float x, float y, float width, float height, float rotation, float lineWidth) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-(width/2),-(height/2));
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f((width/2),-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::fillRectangle(float x, float y, float width, float height, float rotation) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		//glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glVertex2f(-(width/2),-(height/2));
			glVertex2f(-(width/2),(height/2));
			glVertex2f((width/2),(height/2));
			glVertex2f((width/2),-(height/2));
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::drawCircle(float x, float y, float radius, int points, float rotation, float lineWidth) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		glLineWidth(lineWidth);
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i != points; i++)
		{
			float degInRad = (float)(i * (3.14159/(points / 2)));
			glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
		}
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::fillCircle(float x, float y, float radius, int points, float rotation) const
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
		glTranslatef(x,y,0.0f);
		glRotatef(rotation,0.0f,0.0f,1.0f);

		float x1 = 0;
		float y1 = 0;
		float x2 = 0;
		float y2 = 0;
 
		glBegin(GL_TRIANGLES);
		for (int i = 0; i <= points; i++)
		{
			float degInRad = (float)(i * (3.14159/(points / 2)));
			x2 = cos(degInRad)*radius;
			y2 = sin(degInRad)*radius;
			glVertex2f(0.0f,0.0f);
			glVertex2f(x2,y2);
			glVertex2f(x1,y1);
			x1 = x2;
			y1 = y2;
		}
		glEnd();

		glDisable(GL_MULTISAMPLE);
		//glEnable(GL_TEXTURE_2D); //enabled elsewhere
		glPopAttrib();
		glPopMatrix();
	}

	void OpenGLGraphics::translate(float x, float y) const
	{
		glTranslatef(x, y, 0);
	}

	void OpenGLGraphics::rotate(float a) const
	{
		glRotatef(a, 0, 0, 1);
	}

	void OpenGLGraphics::scale(float s) const
	{
		glScalef(s, s, 1);
	}

	void OpenGLGraphics::scale(float sx, float sy) const
	{
		glScalef(sx, sy, 1);
	}
	
	void OpenGLGraphics::identity() const
	{
		glLoadIdentity();
	}

	void OpenGLGraphics::push() const
	{
		glPushMatrix();
	}

	void OpenGLGraphics::pop() const
	{
		glPopMatrix();
	}

	void OpenGLGraphics::clear() const
	{
		// Clear color bit, etc
		glClearColor(background->getRed()/255.0f, background->getGreen()/255.0f, background->getBlue()/255.0f, 1); 
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}
	
} // love
