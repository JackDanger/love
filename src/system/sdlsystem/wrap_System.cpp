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
		return System::getInstance()->events(L);
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
