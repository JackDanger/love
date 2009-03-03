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