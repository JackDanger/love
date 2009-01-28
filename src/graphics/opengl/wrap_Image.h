/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_IMAGE_H
#define LOVE_GRAPHICS_OPENGL_WRAP_IMAGE_H

// LOVE
#include "../../wrap.h"
#include "Image.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Image * luax_checkimage(lua_State * L, int idx);
	int _wrap_Image_getWidth(lua_State * L);
	int _wrap_Image_getHeight(lua_State * L);
	int wrap_Image_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_IMAGE_H
