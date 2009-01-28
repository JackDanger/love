/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* General wrapper functions for objects. For most objects, 
* the same values for the fields __index and __gc
* can be used in the metatable. 
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_WRAP_H
#define LOVE_WRAP_H

#include "luax.h"

namespace love
{
	int _wrap__index(lua_State * L);
	int _wrap__gc(lua_State * L);

} // love

#endif // LOVE_WRAP_H
