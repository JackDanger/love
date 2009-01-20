/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_MODULE_SDLTIMER_H
#define LOVE_MODULE_SDLTIMER_H

// LOVE
#include "../liblove/luax.h"

namespace love
{
namespace sdltimer
{
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	void step();
	float getDelta();
	float getFPS();
	void sleep(int ms);
	float getTime();

} // sdltimer
} // love

#endif // LOVE_MODULE_SDLTIMER_H