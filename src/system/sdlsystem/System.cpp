/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-21
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
		// The union used to get SDL events. 
		static SDL_Event e;

		// Get ONE event.
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_KEYDOWN:
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
