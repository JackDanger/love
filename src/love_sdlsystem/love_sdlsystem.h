/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_MODULE_SDLSYSTEM_H
#define LOVE_MODULE_SDLSYSTEM_H

// LOVE
#include "../liblove/luax.h"

namespace love
{
namespace sdlsystem
{
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* Returns an iterator function for
	* iterating over pending events.
	**/
	int events(lua_State * L);

	/**
	* The iterator function which iterates
	* pending SDL events.
	**/
	int events_i(lua_State * L);

} // sdlsystem
} // love

#endif // LOVE_MODULE_SDLSYSTEM_H