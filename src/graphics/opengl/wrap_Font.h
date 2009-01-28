/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-07
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_FONT_H
#define LOVE_GRAPHICS_OPENGL_WRAP_FONT_H

// LOVE
#include "../../wrap.h"
#include "Font.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Font * luax_checkfont(lua_State * L, int idx);
	int _wrap_Font_getHeight(lua_State * L);
	int _wrap_Font_getWidth(lua_State * L);
	int _wrap_Font_setLineHeight(lua_State * L);
	int _wrap_Font_getLineHeight(lua_State * L);
	int wrap_Font_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_FONT_H
