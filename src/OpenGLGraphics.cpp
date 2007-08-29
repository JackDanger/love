#include "OpenGLGraphics.h"
#include "Core.h"
#include "love.h"
#include "Sprite.h"
#include "Text.h"

namespace love
{
	
	OpenGLGraphics::OpenGLGraphics()
	{
		color.reset<Color>(new Color(255, 255, 255, 255));
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
		if(font!=0)
		{
			font->print(str, x, y);
		}
	}

	void OpenGLGraphics::drawText(const char * str, float x, float y, float limit, int align) const
	{
		if(font!=0)
		{
			// Create new text object.
			Text text(0, 0);

			// Set some attributes.
			text.align(align);
			text.setLimit(limit);

			// And print.
			text.print(x, y, str, font.get(), color.get());
		}	
	}
	
} // love
