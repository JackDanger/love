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

#ifndef LOVE_GRAPHICS_OPENGL_SPRITE_BATCH_H
#define LOVE_GRAPHICS_OPENGL_SPRITE_BATCH_H

// LOVE
#include "../../math.h"
#include "../../Object.h"
#include "../../Vector.h"
#include "../../Matrix.h"
#include "../Drawable.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	// Forward declarations.
	class VertexBuffer;
	class Image;

	class SpriteBatch : public Drawable
	{
	private:

		// Max number of sprites in the batch.
		int size;

		// The next free element.
		int next;

		// Vertex Buffer.
		VertexBuffer * buffer;

	public:

		SpriteBatch(Image * image, int size, int usage);
		virtual ~SpriteBatch();

		void add(float x, float y, float a, float sx, float sy, float ox, float oy);
		void clear();

		// Implements Drawable.
		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;

	}; // SpriteBatch

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_SPRITE_BATCH_H
