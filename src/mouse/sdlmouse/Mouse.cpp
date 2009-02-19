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
