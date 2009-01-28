/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "Image.h"

// DevIL
#include <IL/il.h>

// LOVE
#include "wrap_ImageData.h"

namespace love
{
namespace image
{
namespace devil
{
	Image * Image::_instance = 0;

	Image::Image()
	{
	}

	Image * Image::__getinstance()
	{
		if(_instance == 0)
			_instance = new Image();
		return _instance;
	}

	int Image::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"devil",
			"image",
			"DevIL Image Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Image::__open(lua_State * L)
	{
		ilInit();
		wrap_ImageData_open(L);
		luax_register_gc(L, "devil", &__garbagecollect);
		return 0;
	}

	int Image::__garbagecollect(lua_State * L)
	{
		ilShutDown();
		Image * m = Image::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	int Image::getFormats(lua_State * L)
	{
		lua_pushstring(L, "bmp cut dcx dds exr ico icns gif jpg jp2 "
			"lbm lif mdl pcd pcx pic png pnm psd psp raw sgi tga "
			"tif wal act pal hdr");
		return 1;
	}

	ImageData * Image::newImageData(love::filesystem::File * file)
	{
		return new ImageData(file);
	}

	ImageData * Image::newImageData(int width, int height)
	{
		return new ImageData(width, height);
	}

} // devil
} // image
} // love
