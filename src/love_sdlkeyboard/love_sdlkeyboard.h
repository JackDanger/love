/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_MODULE_SDLKEYBOARD_H
#define LOVE_MODULE_SDLKEYBOARD_H

// LOVE
#include "../liblove/luax.h"

namespace love
{
namespace sdlkeyboard
{
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* Checks whether a certain key is down or not.
	* @param key A key identifier.
	**/
	bool isDown(int key);	

} // sdlkeyboard
} // love

#endif // LOVE_MODULE_SDLKEYBOARD_H
