#include "OpenGLImage.h"
#include "AbstractImage.h"
#include "AbstractFile.h"
#include "love.h"

// DevIL
#include <IL/ilut.h>

namespace love
{
	
	OpenGLImage::OpenGLImage(pAbstractFile file) : Resource(file)
	{

	}
	
	OpenGLImage::~OpenGLImage()
	{
		printf("[-.-] - Destroyed! - [%s]\n", toString().c_str());
		unload();
	}

	int OpenGLImage::load()
	{	

		//printf("Loading OGLImage, LOEL %s -> %s\n", file->getSource().c_str(), file->getFilename().c_str());

		// Load image data into memory
		if(!file->load())
			return LOVE_ERROR;

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

		this->actualWidth = width;
		this->actualHeight = height;

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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)actualWidth, (GLsizei)actualHeight, 0, 
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

		return LOVE_OK;

	}

	void OpenGLImage::unload()
	{

		// Delete texture.
		glDeleteTextures(1, &texture);

		//printf("Image \"%s\" Unloaded!\n", file->getFilename().c_str());
	}

	int OpenGLImage::twoPower(int num) const
	{
		int temp = 1;
		while(temp < num)
			temp *= 2;
		return temp;
	}

	void OpenGLImage::padTwoPower()
	{

		// Get twopower of width and height
		ILuint width	= twoPower((int)this->width);
		ILuint height	= twoPower((int)this->height);

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
		this->actualWidth = (float)width;
		this->actualHeight = (float)height;

		// Cleanup
		delete [] d;
	}

	string OpenGLImage::toString() const
	{
		return "OpenGLImage: " + file->getFilename();
	}
	
} // love
