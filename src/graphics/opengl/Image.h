/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2007-08-19
**/

#ifndef LOVE_GRAPHICS_OPENGL_IMAGE_H
#define LOVE_GRAPHICS_OPENGL_IMAGE_H

// LOVE
#include "../../config.h"
#include "../../image/ImageData.h"
#include "../../math.h"
#include "../Volatile.h"
#include "../Drawable.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	/**
	* OpenGL-specific image loader and renderer. 
	**/
	class Image : public Drawable, public Volatile
	{
	private:

		love::image::ImageData * data;

		// Width and height of the hardware texture.
		float width, height;

		// OpenGL texture identifier.
		unsigned int texture;

		// Vertices of the image.
		vertex vertices[4];

	public:
	
		/**
		* Creates a new Image. Not that anything is ready to use
		* before load is called.
		* @param file The file from which to load the image.
		**/
		Image(love::image::ImageData * data);
		
		virtual ~Image();

		float getWidth() const;
		float getHeight() const;

		const vertex * getVertices() const;

		/**
		* Generate vertices according to a subimage.
		* 
		* Note: out-of-range values will be clamped. 
		* Note: the vertex colors will not be changed.
		* 
		* @param x The top-left corner of the subimage along the x-axis.
		* @param y The top-left corner of the subimage along the y-axis.
		* @param w The width of the subimage.
		* @param h The height of the subimage.
		* @param vertices A vertex array of size four.
		**/
		void getRectangleVertices(int x, int y, int w, int h, vertex * vertices);

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
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_IMAGE_H
