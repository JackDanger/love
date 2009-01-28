/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#include "wrap_File.h"

namespace love
{
namespace filesystem
{
namespace physfs
{
	File * luax_checkfile(lua_State * L, int idx)
	{
		return luax_checktype<File>(L, idx, "File", LOVE_FILESYSTEM_FILE_BITS);
	}

	int _wrap_File_getSize(lua_State * L)
	{
		File * t = luax_checkfile(L, 1);
		lua_pushinteger(L, t->getSize());
		return 1;
	}

	const luaL_Reg wrap_File_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getSize", _wrap_File_getSize },
		{ 0, 0 }
	};

	int wrap_File_open(lua_State * L)
	{
		luax_register_type(L, "File", wrap_File_functions);
		return 0;
	}

} // physfs
} // filesystem
} // love