/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_SDLTIMER_WRAP_TIMER_H
#define LOVE_SDLTIMER_WRAP_TIMER_H

// LOVE
#include "../../luax.h"

// sdltimer
#include "Timer.h"

namespace love
{
namespace timer
{
namespace sdltimer
{
	int _wrap_step(lua_State * L)
	{
		Timer::__getinstance()->step();
		return 0;
	}

	int _wrap_getDelta(lua_State * L)
	{
		lua_pushnumber(L, Timer::__getinstance()->getDelta());
		return 1;
	}

	int _wrap_getFPS(lua_State * L)
	{
		lua_pushnumber(L, Timer::__getinstance()->getFPS());
		return 1;
	}

	int _wrap_sleep(lua_State * L)
	{
		int ms = luaL_checkint(L, 1);
		Timer::__getinstance()->sleep(ms);
		return 0;
	}

	int _wrap_getTime(lua_State * L)
	{
		lua_pushnumber(L, Timer::__getinstance()->getTime());
		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg wrap_Timer_functions[] = {
		{ "step", _wrap_step },
		{ "getDelta", _wrap_getDelta },
		{ "getFPS", _wrap_getFPS },
		{ "sleep", _wrap_sleep },
		{ "getTime", _wrap_getTime },
		{ 0, 0 }
	};

	int wrap_Timer_open(lua_State * L)
	{
		luax_register_module(L, "timer", wrap_Timer_functions);
		return 0;
	}

} // sdltimer
} // timer
} // love

#endif // LOVE_SDLTIMER_WRAP_TIMER_H
