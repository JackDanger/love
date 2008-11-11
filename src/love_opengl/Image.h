/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2007-08-19
**/

#ifndef LOVE_OPENGL_IMAGE_H
#define LOVE_OPENGL_IMAGE_H

// LOVE
#include <love/config.h>
#include <love/Drawable.h>

// Module
#include "Texture.h"

namespace love
{
namespace opengl
{
	/**
	* OpenGL-specific image loader and renderer. Uses DevIL image
	* library for support for all relevant formats.
	**/
	class Image : public Drawable
	{
	private:

		Texture * texture;

		// An image represents a part of a texture defined
		// by the top-left point (x,y) and the size (w,h).
		float x, y, width, height;

		// Contains vertex and texel information.
		float texels[8];
		float vertices[8];

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		Image();
		Image(Texture * texture);
		Image(Image * image, float x, float y, float w, float h);
		
		virtual ~Image();

		float getWidth() const;
		float getHeight() const;


		void draw(float x, float y, float angle, float sx, float sy) const;

#ifdef LOVE_COMPAT_050
	
		void setCenter(float x, float y);
		void draws(float x, float y, float cx, float cy, float w, float h, float angle, float sx, float sy, float ox, float oy);

#endif

		
	}; // Image
	
} // opengl
} // love

#endif // LOVE_OPENGL_IMAGE_H
