/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "SpriteBatch.h"

// STD
#include <iostream>

namespace love
{
namespace opengl
{
	SpriteBatch::SpriteBatch(Image * image, int size)
		: image(image), size(size), next(0)
	{
		image->retain();
		sprites = new SpriteBatchElement[size];
		glGenBuffers(1, &vbo_buf);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteBatchElement)*size, sprites, GL_DYNAMIC_DRAW);
	}

	SpriteBatch::~SpriteBatch()
	{
		image->release();
		delete [] sprites;
		glDeleteBuffers(1, &vbo_buf);
	}

	void SpriteBatch::add(float x, float y, float a, float sx, float sy, float ox, float oy)
	{
		// Only do this if there's a free slot.
		if(next < size)
		{
			SpriteBatchElement & e = sprites[next];

			// Half-sizes.
			float w2 = image->getWidth()/2.0f;
			float h2 = image->getHeight()/2.0f;

			e[0].x = -w2; e[0].y = -h2;
			e[1].x = -w2; e[1].y = h2;
			e[2].x = w2; e[2].y = h2;
			e[3].x = w2; e[3].y = -h2;

			e[0].s = 0; e[0].t = 0;
			e[1].s = 0; e[1].t = 1;
			e[2].s = 1; e[2].t = 1;
			e[3].s = 1; e[3].t = 0;

			// Transform.
			Matrix t;
			t.translate(x, y);
			t.scale(sx, sy);
			t.rotate(a);
			t.transform(sprites[next], sprites[next], 4);

			// Update VBO.
			glBindBuffer(GL_ARRAY_BUFFER, vbo_buf);
			glBufferSubData(GL_ARRAY_BUFFER, next*sizeof(SpriteBatchElement), sizeof(SpriteBatchElement), &sprites[next]);

			// Increment counter.
			next++;			
		}
	}

	void SpriteBatch::clear()
	{
		// Reset the position of the next index.
		next = 0;
	}

	void SpriteBatch::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
	
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);		
		image->bind();

		/**
		glVertexPointer(2, GL_FLOAT, sizeof(vertex2v2t), (GLvoid*)&sprites[0][0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(vertex2v2t), (GLvoid*)&sprites[0][0].s);
		glDrawArrays(GL_QUADS, 0, 4*next);
		**/

		glBindBuffer(GL_ARRAY_BUFFER, vbo_buf);
		glVertexPointer(2, GL_FLOAT, sizeof(vertex2v2t), 0);
		glTexCoordPointer(2, GL_FLOAT, sizeof(vertex2v2t), (GLvoid*)(sizeof(float)*2));
		glDrawArrays(GL_QUADS, 0, 4*next);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

} // opengl
} // love
