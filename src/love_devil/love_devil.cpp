/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "love_devil.h"

// DevIL
#include <IL/il.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE devil
#define LOVE_WRAP_BITS LOVE_DEVIL_BITS
#include "../liblove/image/wimage.h"

namespace love
{
namespace devil
{

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"devil",
			"image",
			"PhysicsFS Image Module",
			"LOVE Development Team",
			luaopen);

		ilInit();

		return 0;
	}

	int luaopen(lua_State * L)
	{
		luareg(L);
		luax_register_gc(L, "devil", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		ilShutDown();
		return 0;
	}

	int getFormats(lua_State * L)
	{
		lua_pushstring(L, "bmp cut dcx dds exr ico icns gif jpg jp2 "
			"lbm lif mdl pcd pcx pic png pnm psd psp raw sgi tga "
			"tif wal act pal hdr");
		return 1;
	}

	ImageData * newImageData(File * file)
	{
		return new ImageData(file);
	}

	ImageData * newImageData(int width, int height)
	{
		return new ImageData(width, height);
	}

} // devil
} // love
