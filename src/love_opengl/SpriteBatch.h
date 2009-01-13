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
#include "../liblove/Object.h"
#include "../liblove/graphics/Drawable.h"

// Module.
#include "Image.h"

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{

	struct sprite
	{
		GLfloat vertices[8];
		GLfloat texels[8];
	};

	class SpriteBatch : public Drawable
	{
	private:

		// Max number of sprites in the batch.
		int size;

		Image * image;

	public:

		SpriteBatch(Image * image, int size = 1000);
		~SpriteBatch();

	}; // SpriteBatch

} // opengl
} // love

#endif // LOVE_OPENGL_SPRITE_BATCH_H
