/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* Generic wrapper functions. For most objects, 
* the same values for the fields __index and __gc
* can be used in the metatable. 
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_WRAP_W
#define LOVE_WRAP_W

// LOVE
#include "types.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap__index(lua_State * L)
	{
		lua_getmetatable(L, 1);
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		return 1;
	}

	int _wrap__gc(lua_State * L)
	{
		userdata * u = (userdata *)lua_touserdata(L, 1);
		Object * t = (Object *)u->data;
		t->release();
		return 0;
	}

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_WRAP_W
