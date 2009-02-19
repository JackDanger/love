/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
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
