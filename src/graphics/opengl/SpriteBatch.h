/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-14
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
