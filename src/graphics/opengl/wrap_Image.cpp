/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
**/

// LOVE
#include "wrap_Image.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	Image * luax_checkimage(lua_State * L, int idx)
	{
		return luax_checktype<Image>(L, idx, "Image", LOVE_GRAPHICS_IMAGE_BITS);
	}

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

	static const luaL_Reg wrap_Image_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getWidth", _wrap_Image_getWidth },
		{ "getHeight", _wrap_Image_getHeight },
		{ 0, 0 }
	};

	int wrap_Image_open(lua_State * L)
	{
		luax_register_type(L, "Image", wrap_Image_functions);
		return 0;
	}

} // opengl
} // graphics
} // love
