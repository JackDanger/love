/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#include "love_sdlsystem.h"

// SDL
#include <SDL.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdlsystem
#include "../liblove/wsystem.h"

namespace love
{
namespace sdlsystem
{
	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlsystem",
			"system",
			"SDL System Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		// Init SDL.
		if(SDL_Init(0) < 0)
			return luaL_error(L, SDL_GetError());

		// Enable UNICODE. This is needed for input to work properly.
		SDL_EnableUNICODE(1);

		luareg(L);
		luax_register_gc(L, "sdlsystem", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		SDL_Quit();
		return 0;
	}

	int events(lua_State * L)
	{
		lua_pushcclosure(L, events_i, 0);
		return 1;
	}

	int events_i(lua_State * L)
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
} // love
