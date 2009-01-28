/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#include "wrap.h"

// LOVE
#include "Object.h"

namespace love
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
