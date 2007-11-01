#include "AbstractImage.h"
#include "love.h"

namespace love
{

	AbstractImage::AbstractImage()
	{
	}

	AbstractImage::~AbstractImage()
	{
		unload();
	}

	void AbstractImage::initExternalLibraries()
	{

		if(extlibinit) return;

		// Init DevIL
		ilInit();
		iluInit();

		ilutEnable(ILUT_OPENGL_CONV);
		ilutRenderer(ILUT_OPENGL);

		extlibinit = true;
	}

	const ILuint AbstractImage::getImage() const
	{
		return image;
	}

	const GLuint AbstractImage::getTexture() const
	{
		return texture;
	}
	
	int AbstractImage::load()
	{
		return LOVE_OK;
	}

	void AbstractImage::unload()
	{
		// Delete texture.
		glDeleteTextures(1, &texture);
	}

	void AbstractImage::bind()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	void AbstractImage::beginRender()
	{
		bind();
		glBegin(GL_QUADS);

	}

	void AbstractImage::sendVertices()
	{
		glTexCoord2f(0.0,0.0); glVertex2f(0,0);
		glTexCoord2f(0.0,1.0); glVertex2f(0,actualHeight);
		glTexCoord2f(1.0,1.0); glVertex2f(actualWidth,actualHeight);
		glTexCoord2f(1.0,0.0); glVertex2f(actualWidth,0);
	}

	void AbstractImage::sendVertices(float x, float y, float width, float height)
	{

		float xTex = x/(float)this->actualWidth;
		float yTex = y/(float)this->actualHeight;

		float wTex = width/(float)this->actualWidth;
		float hTex = height/(float)this->actualHeight;

		glTexCoord2f(xTex,yTex);				glVertex2i(0,0);
		glTexCoord2f(xTex,yTex+hTex);			glVertex2i(0,(int)height);
		glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2i((int)width,(int)height);
		glTexCoord2f(xTex+wTex,yTex);			glVertex2i((int)width,0);
	}

	void AbstractImage::endRender()
	{
		glEnd();
	}

	renderinfo AbstractImage::getRenderInfo()
	{
		renderinfo r;
		r.xTex = 0.0f;
		r.yTex = 0.0f;
		r.wTex = 1.0f;
		r.hTex = 1.0f;
		r.top = height/2.0f;
		r.left = width/2.0f;
		r.width = actualWidth;;
		r.height = actualHeight;

		return r;

	}

	renderinfo AbstractImage::getRenderInfo(float x, float y, float width, float height)
	{
		renderinfo r;
		r.xTex = x/(float)this->actualWidth;
		r.yTex = y/(float)this->actualHeight;
		r.wTex = width/(float)this->actualWidth;
		r.hTex = height/(float)this->actualHeight;
		r.top = height/2.0f;
		r.left = width/2.0f;
		r.width = width;
		r.height = height;

		return r;
	}

	void AbstractImage::render(float x, float y)
	{
		glTranslatef(x, y, 0);
		render();
		glTranslatef(-x, -y, 0);
	}

	void AbstractImage::render()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(0,0);
			glTexCoord2f(0.0,1.0); glVertex2f(0,actualHeight);
			glTexCoord2f(1.0,1.0); glVertex2f(actualWidth,actualHeight);
			glTexCoord2f(1.0,0.0); glVertex2f(actualWidth,0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void AbstractImage::render(float x, float y, float width, float height)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		float xTex = x/(float)this->actualWidth;
		float yTex = y/(float)this->actualHeight;

		float wTex = width/(float)this->actualWidth;
		float hTex = height/(float)this->actualHeight;


		glBegin(GL_QUADS);
			glTexCoord2f(xTex,yTex);				glVertex2i(0,0);
			glTexCoord2f(xTex,yTex+hTex);			glVertex2i(0,(int)height);
			glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2i((int)width,(int)height);
			glTexCoord2f(xTex+wTex,yTex);			glVertex2i((int)width,0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void AbstractImage::renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);	

		// what is this?
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(x1,y1);
			glTexCoord2f(0.0,1.0); glVertex2f(x2,y2);
			glTexCoord2f(1.0,1.0); glVertex2f(x3,y3);
			glTexCoord2f(1.0,0.0); glVertex2f(x4,y4);
		glEnd();
	}

}// love
