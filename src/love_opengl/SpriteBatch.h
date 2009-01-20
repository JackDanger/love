/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-14
**/

#ifndef LOVE_OPENGL_SPRITE_BATCH_H
#define LOVE_OPENGL_SPRITE_BATCH_H

// LOVE
#include "../liblove/math.h"
#include "../liblove/Object.h"
#include "../liblove/graphics/Drawable.h"
#include "../liblove/Vector.h"
#include "../liblove/Matrix.h"

namespace love
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
} // love

#endif // LOVE_OPENGL_SPRITE_BATCH_H
