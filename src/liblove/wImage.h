/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
**/

#ifndef LOVE_IMAGE_W
#define LOVE_IMAGE_W

#include "luax.h"

#include "wwrap.h"

#include "wDrawable.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_IMAGE_BITS = (LOVE_IMAGE_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkimage(L, idx) luax_checktype<Image>(L, idx, "Image", LOVE_WRAP_IMAGE_BITS)

	int _wrap_Image_getWidth(lua_State * L)
	{
		Image * t = luax_checkimage(L, 1);
		lua_pushnumber(L, t->getWidth());
		return 1;
	}

	int _wrap_Image_getHeight(lua_State * L)
	{
		Image * t = luax_checkimage(L, 1);
		lua_pushnumber(L, t->getHeight());
		return 1;
	}

	static const luaL_Reg Image_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getWidth", _wrap_Image_getWidth },
		{ "getHeight", _wrap_Image_getHeight },

		// From drawable.
		{ "setOffset", _wrap_Drawable_setOffset },
		{ "getOffset", _wrap_Drawable_getOffset },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_IMAGE_W
