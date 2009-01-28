/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
*/

#ifndef LOVE_SDLSYSTEM_WRAP_SYSTEM_H
#define LOVE_SDLSYSTEM_WRAP_SYSTEM_H

// LOVE
#include "../../config.h"
#include "../../luax.h"

// sdlsystem
#include "System.h"

namespace love
{
namespace system
{
namespace sdlsystem
{
	int _wrap_getVersion(lua_State * L)
	{
		lua_pushstring(L, LOVE_VERSION_STR.c_str());
		return 1;
	}

	int _wrap_getCodename(lua_State * L)
	{
		lua_pushstring(L, LOVE_VERSION_CODENAME.c_str());
		return 1;
	}

	int _wrap_getPlatform(lua_State * L)
	{
#if defined(LOVE_WINDOWS)
		lua_pushstring(L, "Windows");
#elif defined(LOVE_LINUX)
		lua_pushstring(L, "Linux");
#elif defined(LOVE_MACOSX)
		lua_pushstring(L, "Mac OS X");
#endif
		return 1;
	}

	int _wrap_events(lua_State * L)
	{
		return System::__getinstance()->events(L);
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_System_functions[] = {
		
		{ "getVersion", _wrap_getVersion },
		{ "getCodename", _wrap_getCodename },
		{ "getPlatform", _wrap_getPlatform },
		{ "events", _wrap_events },
		{ 0, 0 }
	};

	int wrap_System_open(lua_State * L)
	{
		luax_register_module(L, "system", wrap_System_functions);
		return 0;
	}

} // sdlsystem
} // system
} // love

#endif // LOVE_SDLSYSTEM_WRAP_SYSTEM_H
