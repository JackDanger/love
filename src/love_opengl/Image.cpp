/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2007-08-19
**/

#include "Image.h"

// STD
#include <cstring> // For memcpy

// Module
#include "Texture.h"

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{

	Image::Image(ImageData * data)
		: width((float)(data->getWidth())), height((float)(data->getHeight()))
	{
		data->retain();
		this->data = data;
	}

	Image::~Image()
	{
		if(data != 0)
			data->release();
		unload();
	}

	float Image::getWidth() const
	{
		return width;
	}

	float Image::getHeight() const
	{
		return height;
	}

	void Image::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		// Half-sizes.
		float w2 = width/2.0f;
		float h2 = height/2.0f;

		bind();
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(ox,oy,0);
		glBegin(GL_QUADS);
		glVertex2f(-w2, -h2); glTexCoord2f(0, 0);
		glVertex2f(-w2, h2); glTexCoord2f(0, 1);
		glVertex2f(w2, h2); glTexCoord2f(1, 1);
		glVertex2f(w2, -h2); glTexCoord2f(1, 0);
		glEnd();
		glPopMatrix();
	}
	
	void Image::draws(float x, float y, float angle, float sx, float sy, float ox, float oy, float rx, float ry, float rw, float rh) const
	{
		// TODO
	}

	void Image::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	bool Image::load()
	{
		return loadVolatile();
	}

	void Image::unload()
	{
		unloadVolatile();
	}

	bool Image::loadVolatile()
	{
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 
			0, 
			GL_RGBA8, 
			(GLsizei)width, 
			(GLsizei)height, 
			0, 
			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			data->getData());

		return true;
	}

	void Image::unloadVolatile()
	{
		// Delete the hardware texture.
		if(texture != 0)
		{
			glDeleteTextures(1, &texture);
			texture = 0;
		}
	}

} // opengl	
} // love
