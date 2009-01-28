/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-21
**/

#include "Mouse.h"

// SDL
#include <SDL.h>

namespace love
{
namespace mouse
{
namespace sdlmouse
{
	// Wrapper loaders.
	extern int wrap_Mouse_open(lua_State * L);

	Mouse * Mouse::_instance = 0;

	Mouse::Mouse()
	{
	}

	Mouse * Mouse::__getinstance()
	{
		if(_instance == 0)
			_instance = new Mouse();
		return _instance;
	}

	int Mouse::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlmouse",
			"mouse",
			"SDL Mouse Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Mouse::__open(lua_State * L)
	{
		// Open stuff here.
		wrap_Mouse_open(L);
		luax_register_gc(L, "sdlmouse", &__garbagecollect);
		return 0;
	}

	int Mouse::__garbagecollect(lua_State * L)
	{
		Mouse * m = Mouse::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	int Mouse::getX() const
	{
		int x;
		SDL_GetMouseState(&x, 0);
		return x;
	}

	int Mouse::getY() const
	{
		int y;
		SDL_GetMouseState(0, &y);
		return y;
	}

	void Mouse::getPosition(int * x, int * y) const
	{
		SDL_GetMouseState(x, y);
	}

	void Mouse::setPosition(int x, int y)
	{
		SDL_WarpMouse(x, y);
	}

	void Mouse::setVisible(bool visible)
	{
		SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
	}

	bool Mouse::isDown(int button) const
	{
		return (SDL_GetMouseState(0, 0) & SDL_BUTTON(button)) != 0;
	}

	bool Mouse::isVisible() const
	{
		return (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE) ? true : false;
	}

} // sdlmouse
} // mouse
} // love
