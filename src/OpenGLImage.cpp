#include "OpenGLImage.h"

#include <cmath>

// LOVE
#include "love_math.h"
#include "File.h"
#include "using_gl.h"
#include "using_graphics.h"

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
		//graphics->applyColorMode();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(0,0);
			glTexCoord2f(0.0,1.0); glVertex2f(0,textureHeight);
			glTexCoord2f(1.0,1.0); glVertex2f(textureWidth,textureHeight);
			glTexCoord2f(1.0,0.0); glVertex2f(textureWidth,0);
		glEnd();
		
	}

	void OpenGLImage::render(float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		glTranslatef(-center_x, -center_y, 0);
		render();
		glPopMatrix();
	}

	void OpenGLImage::render(float x, float y, float width, float height) const
	{
		//graphics->applyColorMode();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		float xTex = x/(float)textureWidth;
		float yTex = y/(float)textureHeight;

		float wTex = width/(float)textureWidth;
		float hTex = height/(float)textureHeight;

		glBegin(GL_QUADS);
			glTexCoord2f(xTex,yTex);				glVertex2i(0,0);
			glTexCoord2f(xTex,yTex+hTex);			glVertex2i(0,(int)height);
			glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2i((int)width,(int)height);
			glTexCoord2f(xTex+wTex,yTex);			glVertex2i((int)width,0);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void OpenGLImage::render(float x, float y, float angle, float sx, float sy) const
	{
		//graphics->applyColorMode();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(-center_x, -center_y, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2f(0,0);
			glTexCoord2f(0.0,1.0); glVertex2f(0,textureHeight);
			glTexCoord2f(1.0,1.0); glVertex2f(textureWidth,textureHeight);
			glTexCoord2f(1.0,0.0); glVertex2f(textureWidth,0);
		glEnd();
		glPopMatrix();
	}

	void OpenGLImage::render(const float * vertices, const float * texels, float x, float y, 
		float angle, float sx, float sy, float cx, float cy) const
	{
		//graphics->applyColorMode();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);

		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(cx, cy, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(texels[0],texels[1]); glVertex2f(vertices[0],vertices[1]);
			glTexCoord2f(texels[2],texels[3]); glVertex2f(vertices[2],vertices[3]);
			glTexCoord2f(texels[4],texels[5]); glVertex2f(vertices[4],vertices[5]);
			glTexCoord2f(texels[6],texels[7]); glVertex2f(vertices[6],vertices[7]);
		glEnd();
		glPopMatrix();
	}

	bool OpenGLImage::readData()
	{
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

		center_x = this->width/2.0f;
		center_y = this->height/2.0f;

		this->textureWidth = width;
		this->textureHeight = height;

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		return true;
	}

	rgba * OpenGLImage::getData() const
	{
		return (rgba *)ilGetData();
	}

	bool OpenGLImage::toHardware()
	{
		padTwoPower();

		// Pass on to OGL
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// @todo Warning. GL_RGBA8 might fail.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)textureWidth, (GLsizei)textureHeight, 0, 
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

		// Check for errors
		if(texture == 0) 
		{
			printf("Image error: could not create OGL texture.");
			return false;
		}

		return true;
	}

	void OpenGLImage::freeData()
	{
		// Delete DevIL-data (no longer needed)
		ilDeleteImages(1, &image);
		
		// Unload the file.
		file->unload();
	}

	bool OpenGLImage::load()
	{	
		// Read file.
		if(!readData())
			return false;

		// Send to hardware
		if(!toHardware())
			return false;

		// Free local data.
		freeData();

		// HW texture will be removed in unload.

		return true;
	}

	void OpenGLImage::unload()
	{
		// Delete the hardware texture.
		if(texture != 0)
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
		{
			d[i].a = 0;
			d[i].r = 61;
			d[i].g = 51;
			d[i].b = 251;
		}

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

	bool pixel_in_range(rgba * data, int width, int height, int x, int y)
	{
		return (x >= 0 && y >= 0 && x < width && y < height);
	}

	void pixel_commit(rgba & source, int & r, int & g, int & b, int & counter)
	{
		if(source.a != 0)
		{
			counter++;
			r += source.r;
			g += source.g;
			b += source.b;
		}
	}

	void pixel_average_area(rgba * data, int width, int height, int x, int y)
	{
		int p = 0; // Number of neighbor pixels with alpha != 0
		int r = 0, g = 0, b = 0;

		if(pixel_in_range(data, width, height, x-1, y-1)) pixel_commit(data[(y-1)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x, y-1)) pixel_commit(data[(y-1)*width+(x)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y-1)) pixel_commit(data[(y-1)*width+(x+1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x-1, y)) pixel_commit(data[(y)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y)) pixel_commit(data[(y)*width+(x+1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x-1, y+1)) pixel_commit(data[(y+1)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x, y+1)) pixel_commit(data[(y+1)*width+(x)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y+1))pixel_commit(data[(y+1)*width+(x+1)], r, g, b, p);

		if(p == 0) p = 1;

		data[y*width+x].r = r/p;
		data[y*width+x].g = g/p;
		data[y*width+x].b = b/p;

	}

	void OpenGLImage::extendAlpha()
	{
		// Get key data
		ILuint width	= ilGetInteger(IL_IMAGE_WIDTH);
		ILuint height	= ilGetInteger(IL_IMAGE_HEIGHT);
		ILuint depth	= ilGetInteger(IL_IMAGE_DEPTH);
		ILuint bpp		= ilGetInteger(IL_IMAGE_BPP);
		ILuint type		= ilGetInteger(IL_IMAGE_TYPE);
		ILuint format	= ilGetInteger(IL_IMAGE_FORMAT);
		ILuint origin	= ilGetInteger(IL_IMAGE_ORIGIN);

		// Source
		rgba * s = (rgba *)ilGetData();

		for(int y=0;y<this->height;y++)
		{
			for(int x=0;x<this->width;x++)
			{
				if(s[y*width+x].a == 0)
				{
					pixel_average_area(s, width, height, x, y);
				}
			}
		}

	}

	void OpenGLImage::addAlphaBorder(bool overwrite)
	{
		if(!overwrite)
		{
			// Extend image here.
			// Update size.
		}

		ILuint width	= ilGetInteger(IL_IMAGE_WIDTH);
		ILuint height	= ilGetInteger(IL_IMAGE_HEIGHT);

		rgba * s = (rgba *)ilGetData();

		// Overwrite the outer border.
		for(int i = 0;i<(int)width;i++)
		{
			s[i].a = 0;
			s[(height-1)*width + i].a = 0;
		}

		for(int i = 0;i<(int)height;i++)
		{
			s[height*i].a = 0;
			s[(height*i)+width-1].a = 0;
		}
	}
	
} // love
