/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* -- LOVE Development Team, http://love2d.org
**/

#include "System.h"

// SDL
#include <SDL.h>

namespace love
{
namespace system
{
namespace sdlsystem
{
	// Wrapper loaders.
	extern int wrap_System_open(lua_State * L);

	System * System::_instance = 0;

	System::System()
	{
	}

	System * System::__getinstance()
	{
		if(_instance == 0)
			_instance = new System();
		return _instance;
	}

	int System::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlsystem",
			"system",
			"SDL System Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int System::__open(lua_State * L)
	{
		// Open stuff here.
		wrap_System_open(L);
		luax_register_gc(L, "sdlsystem", &__garbagecollect);
		return 0;
	}

	int System::__garbagecollect(lua_State * L)
	{
		System * m = System::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	int System::events(lua_State * L)
	{
		lua_pushcclosure(L, &events_i, 0);
		return 1;
	}

	int System::events_i(lua_State * L)
	{
		SDL_EnableUNICODE(1);

		// The union used to get SDL events. 
		static SDL_Event e;

		// Get ONE event.
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_KEYDOWN:
				lua_pushinteger(L, e.type);
				lua_pushinteger(L, e.key.keysym.sym);
				lua_pushinteger(L, e.key.keysym.unicode);
				return 3;
			case SDL_KEYUP:
				lua_pushinteger(L, e.type);
				lua_pushinteger(L, e.key.keysym.sym);
				return 2;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				lua_pushinteger(L, e.type);
				lua_pushinteger(L, e.button.x);
				lua_pushinteger(L, e.button.y);
				lua_pushinteger(L, e.button.button);
				return 4;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				lua_pushinteger(L, e.type);
				lua_pushinteger(L, e.jbutton.which);
				lua_pushinteger(L, e.jbutton.button);
				return 3;
			case SDL_QUIT:
				lua_pushinteger(L, e.type);
				return 1;
			default:
				break;
			}
		}

		// No pending events.
		return 0;
	}

} // sdlsystem
} // system
} // love
