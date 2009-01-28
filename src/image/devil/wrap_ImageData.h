/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-15
**/

#ifndef LOVE_IMAGE_DEVIL_WRAP_IMAGE_DATA_H
#define LOVE_IMAGE_DEVIL_WRAP_IMAGE_DATA_H

// LOVE
#include "../../wrap.h"
#include "ImageData.h"

namespace love
{
namespace image
{
namespace devil
{
	ImageData * luax_checkimagedata(lua_State * L, int idx);
	int _wrap_ImageData_getWidth(lua_State * L);
	int _wrap_ImageData_getHeight(lua_State * L);
	int _wrap_ImageData_getPixel(lua_State * L);
	int _wrap_ImageData_setPixel(lua_State * L);
	int _wrap_ImageData_mapPixel(lua_State * L);
	int wrap_ImageData_open(lua_State * L);

} // devil
} // image
} // love

#endif // LOVE_IMAGE_DEVIL_WRAP_IMAGE_DATA_H
