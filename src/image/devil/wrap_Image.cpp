/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-15
**/

#include "wrap_Image.h"

// LOVE
#include "Image.h"

namespace love
{
namespace image
{
namespace devil
{
	int _wrap_getFormats(lua_State * L)
	{
		return Image::__getinstance()->getFormats(L);
	}

	int _wrap_newImageData(lua_State * L)
	{

		// Case 1: Integers.
		if(lua_isnumber(L, 1))
		{
			int w = luaL_checkint(L, 1);
			int h = luaL_checkint(L, 2);
			ImageData * t = Image::__getinstance()->newImageData(w, h);
			luax_newtype(L, "ImageData", LOVE_IMAGE_IMAGE_DATA_BITS, (void*)t);
			return 1;
		}

		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Case 2: String/File.
		love::filesystem::File * file = luax_checktype<love::filesystem::File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
		ImageData * t = Image::__getinstance()->newImageData(file);
		luax_newtype(L, "ImageData", LOVE_IMAGE_IMAGE_DATA_BITS, (void*)t);
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Image_functions[] = {
		{ "getFormats",  _wrap_getFormats },
		{ "newImageData",  _wrap_newImageData },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "image", wrap_Image_functions);
		wrap_ImageData_open(L);
		return 0;
	}

} // devil
} // image
} // love
