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
#include "../liblove/config.h"
#include "../liblove/image/ImageData.h"
#include "../liblove/graphics/Drawable.h"

// Module
#include "../liblove/graphics/Volatile.h"

namespace love
{
namespace opengl
{
	/**
	* OpenGL-specific image loader and renderer. 
	**/
	class Image : public Drawable, public Volatile
	{
	private:

		ImageData * data;

		// Width and height of the hardware texture.
		float width, height;

		// OpenGL texture identifier.
		unsigned int texture;

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		Image(ImageData * data);
		
		virtual ~Image();

		float getWidth() const;
		float getHeight() const;

		// Implements Drawable.
		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;

		/**
		* This function draws a section of the image.
		**/
		void draws(float x, float y, float angle, float sx, float sy, float ox, float oy, float rx, float ry, float rw, float rh) const;
		
		void bind() const;

		bool load();
		void unload();

		// Implements Volatile.
		bool loadVolatile();
		void unloadVolatile();		

	}; // Image
	
} // opengl
} // love

#endif // LOVE_OPENGL_IMAGE_H
