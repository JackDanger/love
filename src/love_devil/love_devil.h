/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_MODULE_DEVIL_H
#define LOVE_MODULE_DEVIL_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/luax.h"
#include "../liblove/filesystem/File.h"

// love_devil
#include "ImageData.h"

namespace love
{
namespace devil
{

	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	ImageData * newImageData(File * file);
	ImageData * newImageData(int width, int height);
	int getFormats(lua_State * L);
	//ImageDataBuffer * newImageDataBuffer(int width, int height);

} // devil
} // love

#endif // LOVE_MODULE_DEVIL_H