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

// Module
#include "Texture.h"

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{

	Image::Image()
		: x(0), y(0), width(0), height(0), texture(0)
	{
	}

	Image::Image(Texture * texture)
		: x(0), y(0), width(texture->width), height(texture->height)
	{
		texture->retain();
		this->texture = texture;

		float w2 = width/2.0f;
		float h2 = height/2.0f;

		const float temp_vertices [] = 
		{
			-w2, -h2, 
			-w2, h2, 
			w2, h2,
			w2, -h2
		};

		float tw = width/texture->textureWidth;
		float th = height/texture->textureHeight;

		const float temp_texels [] = 
		{
			0, 0, 
			0, th,
			tw, th, 
			tw, 0
		};

		memcpy(vertices, temp_vertices, sizeof(float)*8);
		memcpy(texels, temp_texels, sizeof(float)*8);
	}
	
	Image::Image(Image * image, float x, float y, float w, float h)
		: x(image->x + x), y(image->y + y), width(w), height(h)
	{
		texture = image->texture;
		texture->retain();

		float w2 = width/2.0f;
		float h2 = height/2.0f;

		const float temp_vertices [] = 
		{
			-w2, -h2, 
			-w2, h2, 
			w2, h2,
			w2, -h2
		};

		float tx = this->x/(texture->textureWidth);
		float ty = this->y/(texture->textureHeight);
		float tw = this->width/(texture->textureWidth);
		float th = this->height/(texture->textureHeight);

		const float temp_texels [] = 
		{
			tx, ty,
			tx, ty+th,
			tx+tw, ty+th,
			tx+tw, ty
		};

		memcpy(vertices, temp_vertices, sizeof(float)*8);
		memcpy(texels, temp_texels, sizeof(float)*8);
	}

	Image::~Image()
	{
		if(texture != 0)
			texture->release();
	}

	float Image::getWidth() const
	{
		return width;
	}

	float Image::getHeight() const
	{
		return height;
	}

	void Image::draw(float x, float y, float angle, float sx, float sy) const
	{
		glBindTexture(GL_TEXTURE_2D,texture->texture);
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef( offsetX, offsetY, 0);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texels);
		glDrawArrays(GL_QUADS, 0, 4);	
		glPopMatrix();
	}

#ifdef LOVE_COMPAT_050
	
	void Image::setCenter(float x, float y)
	{
		offsetX = x - (width/2.0f);
		offsetY = y - (height/2.0f);
	}

	void Image::draws(float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy, float ox, float oy)
	{
		float xTex = cx/(float)texture->textureWidth;
		float yTex = cy/(float)texture->textureHeight;
		float wTex = w/(float)texture->textureWidth;
		float hTex = h/(float)texture->textureHeight;

		const float temp_texels[] = {
			xTex, yTex, 
			xTex, yTex+hTex, 
			xTex+wTex, yTex+hTex,
			xTex+wTex, yTex 
		};

		const float temp_vertices [] = 
		{
			0, 0,
			0, h, 
			w, h,
			w, 0
		};

		glBindTexture(GL_TEXTURE_2D,texture->texture);

		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(-ox, -oy, 0);
		glVertexPointer(2, GL_FLOAT, 0, temp_vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, temp_texels);
		glDrawArrays(GL_QUADS, 0, 4);	
		glPopMatrix();
	}

#endif

} // opengl	
} // love
