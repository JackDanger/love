/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_DRAWABLE_W
#define LOVE_DRAWABLE_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkdrawable(L, idx) luax_checktype<Drawable>(L, idx, "Drawable", LOVE_DRAWABLE_BITS)

	static const luaL_Reg Drawable_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_DRAWABLE_W
