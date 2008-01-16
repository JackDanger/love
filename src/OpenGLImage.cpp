#include "OpenGLImage.h"

#include <cmath>

// LOVE
#include "love_math.h"
#include "File.h"
#include "using_gl.h"

// DevIL
#include <IL/ilut.h>

using std::string;

namespace love
{
	
	OpenGLImage::OpenGLImage(pFile file) : Image(file), image(0), texture(0)
	{
	}
	
	OpenGLImage::~OpenGLImage()
	{
		unload();
	}

	void OpenGLImage::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	void OpenGLImage::render() const
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		//glColor3f(1, 1, 1);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(0,0);
			glTexCoord2f(0.0,1.0); glVertex2f(0,textureHeight);
			glTexCoord2f(1.0,1.0); glVertex2f(textureWidth,textureHeight);
			glTexCoord2f(1.0,0.0); glVertex2f(textureWidth,0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void OpenGLImage::render(float x, float y) const
	{
		glPushMatrix();
		//glTranslatef(floor(x), floor(y), 0);
		glTranslatef(x, y, 0);
		render();
		glPopMatrix();
	}

	void OpenGLImage::render(float x, float y, float width, float height) const
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		float xTex = x/(float)textureWidth;
		float yTex = y/(float)textureHeight;

		float wTex = width/(float)textureWidth;
		float hTex = height/(float)textureHeight;

		glColor3f(1, 1, 1);

		glBegin(GL_QUADS);
			glTexCoord2f(xTex,yTex);				glVertex2i(0,0);
			glTexCoord2f(xTex,yTex+hTex);			glVertex2i(0,(int)height);
			glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2i((int)width,(int)height);
			glTexCoord2f(xTex+wTex,yTex);			glVertex2i((int)width,0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	bool OpenGLImage::load()
	{	

		//printf("Loading OGLImage, LOEL %s -> %s\n", file->getSource().c_str(), file->getFilename().c_str());

		// Load image data into memory
		if(!file->load())
			return false;

		// Generate DevIL image.
		ilGenImages(1, &image);

		// Bind the image.
		ilBindImage(image);

		// Try to load the image.
		
		ILboolean success = ilLoadL(IL_TYPE_UNKNOWN, (void*)file->getData(), file->getSize());

		// Check for errors
		if(!success)
			printf((const char *)iluErrorString(ilGetError()));

		this->width			= (float)ilGetInteger(IL_IMAGE_WIDTH);
		this->height		= (float)ilGetInteger(IL_IMAGE_HEIGHT);

		this->textureWidth = width;
		this->textureHeight = height;

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		padTwoPower();

		// Pass on to OGL

		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// @todo Warning. This desperado-GL_RGBA8'ing might cause severe failure on
		// someone's computer.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)textureWidth, (GLsizei)textureHeight, 0, 
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

		//texture = ilutGLBindTexImage();

		// Check for errors
		if(texture == 0) 
			printf("Image error: could not create OGL texture.");


		//@todo Add inheritable "manipulate" functoihw.n.

		// Delete DevIL-data (no longer needed)
		ilDeleteImages(1, &image);


		//printf("Image \"%s\" loaded!\n", file->getFilename().c_str());

		file->unload();

		return true;

	}

	void OpenGLImage::unload()
	{
		// Delete the hardware texture.
		glDeleteTextures(1, &texture);
	}

	void OpenGLImage::padTwoPower()
	{

		// Get twopower of width and height
		ILuint width	= power_of_two((int)this->width);
		ILuint height	= power_of_two((int)this->height);

		// No change needed?
		if(width == this->width && height == this->height)
			return;

		// Get key data
		ILuint depth	= ilGetInteger(IL_IMAGE_DEPTH);
		ILuint bpp		= ilGetInteger(IL_IMAGE_BPP);
		ILuint type		= ilGetInteger(IL_IMAGE_TYPE);
		ILuint format	= ilGetInteger(IL_IMAGE_FORMAT);
		ILuint origin	= ilGetInteger(IL_IMAGE_ORIGIN);
		
		// Create new data.
		unsigned int size = width * height * bpp;

		// Destination
		rgba * d = new rgba[size];

		// Source
		rgba * s = (rgba *)ilGetData();

		// Fill entire texture
		for(unsigned int i=0;i<width*height;i++) 
			d[i].a = 0;

		for(int y=0;y<this->height;y++)
		{
			for(int x=0;x<this->width;x++)
			{

				int si = (int)(y * this->width + x);
				
				int dx = x;
				int dy = height - y;

				if(origin == IL_ORIGIN_UPPER_LEFT)
					dy = y;

				int di = dy * width + dx;

				d[di].r = s[si].r;
				d[di].g = s[si].g;
				d[di].b = s[si].b;
				d[di].a = s[si].a;
			}
		}

		// Delete the old image.
		ilDeleteImages(1, &image);

		// Generate new DevIL image.
		ilGenImages(1, &image);

		// Bind the image.
		ilBindImage(image);

		// Create the new image
		ilTexImage(width, height, depth, bpp, format, type, (ILvoid*)d);

		// Set new "real" dimensions
		this->textureWidth = (float)width;
		this->textureHeight = (float)height;

		// Cleanup
		delete [] d;
	}
	
} // love
