/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#include "love_sdlmouse.h"

// SDL
#include <SDL.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdlmouse
#include "../liblove/wmouse.h"

namespace love
{
namespace sdlmouse
{

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlmouse",
			"mouse",
			"SDL Mouse Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		// Init the SDL timer system.
		if(SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
			return luaL_error(L, SDL_GetError());

		luareg(L);
		luax_register_gc(L, "sdlmouse", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		SDL_QuitSubSystem(SDL_INIT_TIMER);
		return 0;
	}

	float getX()
	{
		int x;
		SDL_GetMouseState(&x, 0);
		return (float)x;
	}

	float getY()
	{
		int y;
		SDL_GetMouseState(0, &y);
		return (float)y;
	}

	void setPosition(float x, float y)
	{
		SDL_WarpMouse((int)x, (int)y);
	}

	bool isDown(int button)
	{
		return (SDL_GetMouseState(0, 0) & SDL_BUTTON(button)) != 0;
	}

	void setVisible(bool visible)
	{
		SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
	}

	bool isVisible()
	{
		return (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE) ? true : false;
	}

	int getPosition(lua_State * L)
	{
		lua_pushnumber(L, getX());
		lua_pushnumber(L, getY());
		return 2;
	}

} // sdlmouse
} // love
