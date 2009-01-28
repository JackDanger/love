/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2007-08-19
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
