/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#include "love_sdlkeyboard.h"

// SDL
#include <SDL.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdlkeyboard
#include "../liblove/wkeyboard.h"

namespace love
{
namespace sdlkeyboard
{

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlkeyboard",
			"keyboard",
			"SDL Keyboard Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		luareg(L);
		luax_register_gc(L, "sdlkeyboard", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		return 0;
	}

	bool isDown(int key)
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;		
	}

} // sdlkeyboard
} // love
