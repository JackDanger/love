/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
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
