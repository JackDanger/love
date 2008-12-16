/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-02
*/

#ifndef LOVE_SYSTEM_W
#define LOVE_SYSTEM_W

// LOVE
#include "../platform.h"
#include "../luax.h"
#include "../version.h"

#ifndef LOVE_WRAP_NAMESPACE
#error "LOVE_WRAP_NAMESPACE must be defined."
#endif

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_getVersion(lua_State * L)
	{
		lua_pushstring(L, LOVE_VERSION_STR);
		return 1;
	}

	int _wrap_getCodename(lua_State * L)
	{
		lua_pushstring(L, LOVE_VERSION_CODENAME);
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

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		
		// Generic:
		{ "getVersion", _wrap_getVersion },
		{ "getCodename", _wrap_getCodename },
		{ "getPlatform", _wrap_getPlatform },

		// Must be implemented:
		{ "events", events },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "system", module_fn);
		return 0;
	}

}
}

#endif // LOVE_SYSTEM_W
