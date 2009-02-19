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
