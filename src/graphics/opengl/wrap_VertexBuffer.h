/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-15
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_VERTEX_BUFFER_H
#define LOVE_GRAPHICS_OPENGL_WRAP_VERTEX_BUFFER_H 

#include "../../luax.h"
#include "../../wrap.h"
#include "VertexBuffer.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	VertexBuffer * luax_checkvertexbuffer(lua_State * L, int idx);
	int _wrap_VertexBuffer_setType(lua_State * L);
	int _wrap_VertexBuffer_getType(lua_State * L);
	int _wrap_VertexBuffer_add(lua_State * L);
	int _wrap_VertexBuffer_clear(lua_State * L);
	int wrap_VertexBuffer_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_VERTEX_BUFFER_H