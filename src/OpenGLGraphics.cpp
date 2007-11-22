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
