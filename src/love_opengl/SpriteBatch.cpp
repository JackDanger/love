/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "SpriteBatch.h"

// STD
#include <iostream>

// LOVE
#include "VertexBuffer.h"
#include "Image.h"

namespace love
{
namespace opengl
{
	SpriteBatch::SpriteBatch(Image * image, int size, int usage)
		: size(size), next(0)
	{
		// Four vertices in one sprite.
		buffer = new VertexBuffer(image, size*6, TYPE_TRIANGLES, usage);
	}

	SpriteBatch::~SpriteBatch()
	{
		buffer->release();
	}

	void SpriteBatch::add(float x, float y, float a, float sx, float sy, float ox, float oy)
	{
		// Only do this if there's a free slot.
		if(next < size)
		{
			// Get a pointer to the correct insertion position.
			vertex * v = buffer->vertices + next*6;

			// Half-sizes.
			float w2 = buffer->image->getWidth()/2.0f;
			float h2 = buffer->image->getHeight()/2.0f;

			v[0].x = -w2; v[0].y = -h2;
			v[1].x = -w2; v[1].y = h2;
			v[2].x = w2; v[2].y = h2;
			v[3].x = w2; v[3].y = -h2;

			v[0].s = 0; v[0].t = 0;
			v[1].s = 0; v[1].t = 1;
			v[2].s = 1; v[2].t = 1;
			v[3].s = 1; v[3].t = 0;

			// Transform.
			Matrix t;
			t.translate(x, y);
			t.scale(sx, sy);
			t.rotate(a);
			t.transform(v, v, 4);

			v[5] = v[3];
			v[4] = v[2];
			v[3] = v[0];

			// Send the buffer to the GPU.
			buffer->update(next*6, 6);

			// Increment counter.
			next++;			
		}
	}

	void SpriteBatch::clear()
	{
		// Reset the position of the next index.
		next = 0;

		// Also reset the buffer.
		buffer->clear();
	}

	void SpriteBatch::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		// Let the buffer handle this.
		buffer->draw(x, y, angle, sx, sy, ox, oy);
	}

} // opengl
} // love
