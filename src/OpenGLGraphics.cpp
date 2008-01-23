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
		glClearColor(	(float)background->getRed()/255.0f,
						(float)background->getGreen()/255.0f,
						(float)background->getBlue()/255.0f, 
						1); 
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	void OpenGLGraphics::apply(const pColor & color) const
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	pImage OpenGLGraphics::getImage(pFile file) const
	{
		pImage tmp (new OpenGLImage(file));
		return tmp;
	}

	pFont OpenGLGraphics::getFont(pFile file, int size) const
	{
		pFont tmp (new OpenGLFont(file, size));
		return tmp;
	}
	
	pFont OpenGLGraphics::getImageFont(pFile file, std::string glyphs) const
	{
		pFont tmp (new OpenGLImageFont(file, glyphs));
		return tmp;
	}

	pParticlesystem OpenGLGraphics::getParticlesystem() const
	{
		pParticlesystem tmp(new OpenGLParticleSystem());
		return tmp;
	}
	
	// And here too
	void OpenGLGraphics::drawRectangle(float x, float y, float width, float height) const
	{
		glPushMatrix();
			glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
			glBegin(GL_QUADS);
				glVertex2f(x+width, y);
				glVertex2f(x,y);
				glVertex2f(x,y+height);
				glVertex2f(x+width,y+height);
			glEnd();
			glColor4ub(255,255,255,255);
		glPopMatrix();
	}
	
} // love
