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

#include "Image.h"

// LOVE
#include "../../Matrix.h"
#include "../../math.h"

// STD
#include <cstring> // For memcpy

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace graphics
{
namespace opengl
{

	Image::Image(love::image::ImageData * data)
		: width((float)(data->getWidth())), height((float)(data->getHeight())), texture(0)
	{
		data->retain();
		this->data = data;

		// Generate vertices.
		float w2 = width/2.0f;
		float h2 = height/2.0f;

		memset(vertices, 255, sizeof(vertex)*4);

		vertices[0].x = -w2; vertices[0].y = -h2;
		vertices[1].x = -w2; vertices[1].y = h2;
		vertices[2].x = w2; vertices[2].y = h2;
		vertices[3].x = w2; vertices[3].y = -h2;

		vertices[0].s = 0; vertices[0].t = 0;
		vertices[1].s = 0; vertices[1].t = 1;
		vertices[2].s = 1; vertices[2].t = 1;
		vertices[3].s = 1; vertices[3].t = 0;

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

	const vertex * Image::getVertices() const
	{
		return vertices;
	}

	void Image::getRectangleVertices(int x, int y, int w, int h, vertex * vertices)
	{
		// Check upper.
		x = (x+w > (int)width) ? (int)width-w : x;
		y = (y+h > (int)height) ? (int)height-h : y;

		// Check lower.
		x = (x < 0) ? 0 : x;
		y = (y < 0) ? 0 : y;

		// Half width/height of the 
		float w2 = (float)w/2.0f;
		float h2 = (float)h/2.0f;

		vertices[0].x = -w2; vertices[0].y = -h2;
		vertices[1].x = -w2; vertices[1].y = h2;
		vertices[2].x = w2; vertices[2].y = h2;
		vertices[3].x = w2; vertices[3].y = -h2;

		float tx = (float)x/width;
		float ty = (float)y/height;
		float tw = (float)w/width;
		float th = (float)h/height;

		vertices[0].s = tx; vertices[0].t = ty;
		vertices[1].s = tx; vertices[1].t = ty+th;
		vertices[2].s = tx+tw; vertices[2].t = ty+th;
		vertices[3].s = tx+tw; vertices[3].t = ty;
	}

	void Image::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		bind();

		//Matrix t(x, y, angle, sx, sy, ox, oy);

		//glMultMatrixf((const GLfloat*)t.getElements());
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(LOVE_TODEG(angle), 0, 0, 1);
		glScalef(sx, sy, 1);
		glTranslatef(ox, oy, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&vertices[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&vertices[0].s);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}
	
	void Image::draws(float x, float y, float angle, float sx, float sy, float ox, float oy, float rx, float ry, float rw, float rh) const
	{
		// TODO
	}

	void Image::bind() const
	{
		if(texture != 0)
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
} // graphics
} // love
