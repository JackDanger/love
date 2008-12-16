/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
*/

#ifndef LOVE_TIMER_W
#define LOVE_TIMER_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error "LOVE_WRAP_NAMESPACE must be defined."
#endif

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_step(lua_State * L)
	{
		step();
		return 0;
	}

	int _wrap_getDelta(lua_State * L)
	{
		lua_pushnumber(L, getDelta());
		return 1;
	}

	int _wrap_getFPS(lua_State * L)
	{
		lua_pushnumber(L, getFPS());
		return 1;
	}

	int _wrap_sleep(lua_State * L)
	{
		int ms = luaL_checkint(L, 1);
		sleep(ms);
		return 0;
	}

	int _wrap_getTime(lua_State * L)
	{
		lua_pushnumber(L, getTime());
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "step", _wrap_step },
		{ "getDelta", _wrap_getDelta },
		{ "getFPS", _wrap_getFPS },
		{ "sleep", _wrap_sleep },
		{ "getTime", _wrap_getTime },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "timer", module_fn);
		return 0;
	}

}
}

#endif // LOVE_TIMER_W
