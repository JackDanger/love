/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "Texture.h"

// STD
#include <iostream>

// DevIL
#include <IL/il.h>

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{

	Texture::Texture(ImageData * data)
	{
		this->data = data;
		data->retain();
		width = data->getWidth();
		height = data->getHeight();
	}
	
	Texture::~Texture()
	{
		data->release();
		unload();
	}

	int Texture::getWidth() const
	{
		return (int)width;
	}

	int Texture::getHeight() const
	{
		return (int)width;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	bool Texture::load()
	{
		return loadVolatile();
	}

	void Texture::unload()
	{
		unloadVolatile();
	}

	bool Texture::loadVolatile()
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

	void Texture::unloadVolatile()
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
