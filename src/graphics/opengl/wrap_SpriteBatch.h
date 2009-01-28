/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-15
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_SPRITE_BATCH_H
#define LOVE_GRAPHICS_OPENGL_WRAP_SPRITE_BATCH_H

#include "../../wrap.h"
#include "SpriteBatch.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	SpriteBatch * luax_checkspritebatch(lua_State * L, int idx);
	int _wrap_SpriteBatch_add(lua_State * L);
	int _wrap_SpriteBatch_clear(lua_State * L);
	int wrap_SpriteBatch_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_SPRITE_BATCH_H
