/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-15
**/

#ifndef LOVE_IMAGE_DEVIL_WRAP_IMAGE_H
#define LOVE_IMAGE_DEVIL_WRAP_IMAGE_H

// LOVE
#include "../../luax.h"
#include "wrap_ImageData.h"

namespace love
{
namespace image
{
namespace devil
{
	int _wrap_getFormats(lua_State * L);
	int _wrap_newImageData(lua_State * L);
	int wrap_Image_open(lua_State * L);

} // devil
} // image
} // love

#endif // LOVE_IMAGE_DEVIL_WRAP_IMAGE_H
