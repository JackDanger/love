/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
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

// Module.
#include "Image.h"

// OpenGL
#include "GLee.h"
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{
	typedef vertex2v2t SpriteBatchElement[4];

	class SpriteBatch : public Drawable
	{
	private:

		// Max number of sprites in the batch.
		int size;

		Image * image;

		// Contains the sprites to be drawn.
		SpriteBatchElement * sprites;

		// The next free element.
		int next;

		GLuint vbo_buf;

	public:

		SpriteBatch(Image * image, int size = 1000);
		~SpriteBatch();

		void add(float x, float y, float a, float sx, float sy, float ox, float oy);
		void clear();

		// Implements Drawable.
		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;

	}; // SpriteBatch

} // opengl
} // love

#endif // LOVE_OPENGL_SPRITE_BATCH_H
