/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H
#define LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H

// LOVE
#include "../../wrap.h"
#include "Color.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Color * luax_checkcolor(lua_State * L, int idx);
	int _wrap_Color_setRed(lua_State * L);
	int _wrap_Color_setGreen(lua_State * L);
	int _wrap_Color_setBlue(lua_State * L);
	int _wrap_Color_setAlpha(lua_State * L);
	int _wrap_Color_getRed(lua_State * L);
	int _wrap_Color_getGreen(lua_State * L);
	int _wrap_Color_getBlue(lua_State * L);
	int _wrap_Color_getAlpha(lua_State * L);
	int wrap_Color_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_COLOR_H
