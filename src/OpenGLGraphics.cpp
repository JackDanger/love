#include "OpenGLGraphics.h"

// LOVE
#include "using_gl.h"
#include "love_math.h"
#include "OpenGLImage.h"
#include "OpenGLFont.h"
#include "OpenGLImageFont.h"
#include "OpenGLParticleSystem.h"

// DevIL
#include <IL/ilut.h>

namespace love
{
	OpenGLGraphics::OpenGLGraphics()
	{
	}
	
	OpenGLGraphics::~OpenGLGraphics()
	{
		quit();
	}

	bool OpenGLGraphics::init(int argc, char* argv[])
	{
		ilInit();
		return true;
	}

	void OpenGLGraphics::quit()
	{
	}

	void OpenGLGraphics::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void OpenGLGraphics::setBlendMode(int mode)
	{
		if(mode == LOVE_BLEND_ADDITIVE)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else // mode == LOVE_BLEND_NORMAL
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLGraphics::setColorMode(int mode)
	{
		if(mode == LOVE_COLOR_MODULATE)
			glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		else // mode = LOVE_COLOR_NORMAL
			glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}

	void OpenGLGraphics::setColor(int r, int g, int b, int a)
	{
		glColor4ub(r, g, b, a);	
	}

	void OpenGLGraphics::setBackgroundColor(int r, int g, int b)
	{
		glClearColor((float)(r/255.0f), (float)(g/255.0f), (float)(b/255.0f), 1.0f);
	}

	pImage OpenGLGraphics::newImage(pFile file) const
	{
		pImage tmp (new OpenGLImage(file));
		return tmp;
	}

	pFont OpenGLGraphics::newFont(pFile file, int size) const
	{
		pFont tmp (new OpenGLFont(file, size));
		return tmp;
	}
	
	pFont OpenGLGraphics::newImageFont(pFile file, std::string glyphs) const
	{
		pFont tmp (new OpenGLImageFont(file, glyphs));
		return tmp;
	}

	pParticlesystem OpenGLGraphics::newParticlesystem() const
	{
		pParticlesystem tmp(new OpenGLParticleSystem());
		return tmp;
	}
	
	void OpenGLGraphics::drawLine(float xpos, float ypos, float x1, float y1, float x2, float y2, float lineWidth) const
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth) const
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3) const
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_TRIANGLES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth) const
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);				
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_QUADS);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawCircle(float xpos, float ypos, float radius, float points, float lineWidth) const
	{
		if(points <= 0) points = 1;
		float angle_shift = (two_pi / points);
  
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_LINE_LOOP);

			for(float i = 0; i < two_pi; i+= angle_shift)
				glVertex2f(radius * sin(i),radius * cos(i));

			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillCircle(float xpos, float ypos, float radius, float points) const
	{

		if(points <= 0) points = 1;
		float angle_shift = (two_pi / points);
  
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glBegin(GL_TRIANGLE_FAN);

			for(float i = 0; i < two_pi; i+= angle_shift)
				glVertex2f(radius * sin(i),radius * cos(i));

			glEnd();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::activateSmoothLines()
	{
		glEnable(GL_LINE_SMOOTH);
	}
	
	void OpenGLGraphics::deactivateSmoothLines()
	{
		glDisable(GL_LINE_SMOOTH);
	}
	
} // love
