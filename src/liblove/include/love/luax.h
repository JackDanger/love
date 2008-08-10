/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* Lua auxiliary library. Not much here yet; functions
* will be added as development requires.
*
* @author Anders Ruud
* @date 2008-08-06
*/

#ifndef LOVE_LUAX_H
#define LOVE_LUAX_H

// Lua
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace love
{
	int luax_assert_argc(lua_State * L, int lower);
	int luax_assert_argc(lua_State * L, int lower, int upper);
	int luax_assert_function(lua_State * L, int n);

} // love

#endif // LOVE_LUAX_H
