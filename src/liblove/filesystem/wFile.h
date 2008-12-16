/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_FILE_W
#define LOVE_FILE_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_FILE_BITS = (LOVE_FILE_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkfile(L, idx) luax_checktype<File>(L, idx, "File", LOVE_WRAP_FILE_BITS)

	int _wrap_File_getSize(lua_State * L)
	{
		File * t = luax_checkfile(L, 1);
		lua_pushinteger(L, t->getSize());
		return 1;
	}

	static const luaL_Reg File_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getSize", _wrap_File_getSize },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_FILE_W
