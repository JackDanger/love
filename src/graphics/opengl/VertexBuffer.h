/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-15
**/

#ifndef LOVE_GRAPHICS_OPENGL_VERTEX_BUFFER_H
#define LOVE_GRAPHICS_OPENGL_VERTEX_BUFFER_H

// LOVE
#include "../../constants.h"
#include "../../math.h"
#include "../../Object.h"
#include "../../Vector.h"
#include "../../Matrix.h"
#include "../Drawable.h"

// Module.
#include "Image.h"

// OpenGL
#include "GLee.h"
#include <SDL/SDL_opengl.h>

namespace love
{
namespace graphics
{
namespace opengl
{
	class VertexBuffer : public Drawable
	{
		friend class SpriteBatch;
	private:

		vertex * vertices;

		// Max number of vertices in the buffer.
		int size;

		// The next free element.
		int next;

		// The texture (optional).
		Image * image;

		// Contains the vbo_buffer.
		GLuint vbo_buf;

		// The uage hint for the vertex buffer.
		int usage;
		int gl_usage;

		// The type of primitives we're drawing.
		int type;
		int gl_type;

	private:

		bool useVBO() const;
		void update(int pos, int size);

	public:

		VertexBuffer(Image * image, int size, int type, int usage);
		virtual ~VertexBuffer();

		void setType(int type);
		int getType() const;

		void add(float x, float y, float s, float t, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void add(float x, float y, float s, float t);
		void clear();

		// Implements Drawable.
		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;

	}; // VertexBuffer

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_VERTEX_BUFFER_H
