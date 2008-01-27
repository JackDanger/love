#include "OpenGLGraphics.h"

// LOVE
#include "using_gl.h"
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
		// Clear color bit, etc
		glClearColor(	(float)states.back().background->getRed()/255.0f,
						(float)states.back().background->getGreen()/255.0f,
						(float)states.back().background->getBlue()/255.0f, 
						1); 
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void OpenGLGraphics::apply(const pColor & color) const
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	void OpenGLGraphics::applyColorMode() const
	{
		int color_mode = getColorMode();
		if(color_mode == LOVE_COLOR_NORMAL)
			glColor4f(1, 1, 1, 1);
		else if(color_mode == LOVE_COLOR_MODULATE)
			apply(states.back().color);
	}

	void OpenGLGraphics::setBlendMode(int mode)
	{

		if(mode == LOVE_BLEND_ADDITIVE)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else if(mode == LOVE_BLEND_NORMAL)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Graphics::setBlendMode(mode);
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
		const pColor & color = states.back().color;
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth) const
	{
		glDisable(GL_TEXTURE_2D);
		const pColor & color = states.back().color;
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3) const
	{
		glDisable(GL_TEXTURE_2D);
		const pColor & color = states.back().color;
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_TRIANGLES);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth) const
	{
		glDisable(GL_TEXTURE_2D);
		const pColor & color = states.back().color;
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_LINE_LOOP);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		glDisable(GL_TEXTURE_2D);
		const pColor & color = states.back().color;
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_QUADS);
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);
				glVertex2f(x4, y4);
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::drawCircle(float xpos, float ypos, float radius, float points, float lineWidth) const
	{

		const pColor & color = states.back().color;
		float angle_radians, x, y;
		int angle_shift = (int)(360 / points);
  
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glLineWidth(lineWidth);
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_LINE_LOOP);
			for (int angle = 0; angle < 365; angle += angle_shift)
			{
				angle_radians = angle * (float)3.14159 / (float)180;
				x = radius * (float)cos(angle_radians);
				y = radius * (float)sin(angle_radians);
				glVertex2f(x,y);
			}
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
	void OpenGLGraphics::fillCircle(float xpos, float ypos, float radius, float points) const
	{
		const pColor & color = states.back().color;
		float angle, x, y;
		int angle_shift = (int)(360 / points);
  
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(xpos, ypos, 0.0f);
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()); 
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0.0f, 0.0f);	
			for(int i = 0; i < 365; i+= angle_shift)
			{
				angle = (float)(((double)i) / 57.29577957795135);	
				x = radius * (float)sin((double)angle);
				y = radius * (float)cos((double)angle);
									
				glVertex2f(x,y);
			}
			glEnd();
			//glColor4ub(255,255,255,255);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
	}
	
} // love
