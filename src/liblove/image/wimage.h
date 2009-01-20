/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-15
**/

#ifndef LOVE_IMAGE_MODULE_W
#define LOVE_IMAGE_MODULE_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wImageData.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{

	// getFormats

	int _wrap_newImageData(lua_State * L)
	{

		// Case 1: Integers.
		if(lua_isnumber(L, 1))
		{
			int w = luaL_checkint(L, 1);
			int h = luaL_checkint(L, 2);
			ImageData * t = newImageData(w, h);
			luax_newtype(L, "ImageData", LOVE_WRAP_IMAGE_DATA_BITS, (void*)t);
			return 1;
		}

		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Case 2: String/File.
		File * file = luax_checktype<File>(L, 1, "File", LOVE_FILE_BITS);
		ImageData * t = newImageData(file);
		luax_newtype(L, "ImageData", LOVE_WRAP_IMAGE_DATA_BITS, (void*)t);
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "getFormats",  getFormats },
		{ "newImageData",  _wrap_newImageData },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "image", module_fn);
		luax_register_type(L, "ImageData", ImageData_mt);
		return 0;
	}

} // LOVE_WRAP_NAMESPACE
} // love

#endif // LOVE_IMAGE_MODULE_W
