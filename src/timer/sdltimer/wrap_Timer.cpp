/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

// LOVE
#include "wrap_Timer.h"
#include "Timer.h"

namespace love
{
namespace timer
{
namespace sdltimer
{
	int _wrap_step(lua_State * L)
	{
		Timer::getInstance()->step();
		return 0;
	}

	int _wrap_getDelta(lua_State * L)
	{
		lua_pushnumber(L, Timer::getInstance()->getDelta());
		return 1;
	}

	int _wrap_getFPS(lua_State * L)
	{
		lua_pushnumber(L, Timer::getInstance()->getFPS());
		return 1;
	}

	int _wrap_sleep(lua_State * L)
	{
		int ms = luaL_checkint(L, 1);
		Timer::getInstance()->sleep(ms);
		return 0;
	}

	int _wrap_getTime(lua_State * L)
	{
		lua_pushnumber(L, Timer::getInstance()->getTime());
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
		luax_register_gc(L, "sdltimer", &wrap_Timer_gc);
		if(!Timer::getInstance()->init())
			return luaL_error(L, "Could not init module sdltimer.");
		return 0;
	}

	int wrap_Timer_gc(lua_State * L)
	{
		Timer::getInstance()->quit();
		return 0;
	}

} // sdltimer
} // timer
} // love
