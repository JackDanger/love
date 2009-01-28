/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-21
**/

#include "Keyboard.h"

// SDL
#include <SDL.h>

namespace love
{
namespace keyboard
{
namespace sdlkeyboard
{
	// Wrapper loaders.
	extern int wrap_Keyboard_open(lua_State * L);

	Keyboard * Keyboard::_instance = 0;

	Keyboard::Keyboard()
	{
	}

	Keyboard * Keyboard::__getinstance()
	{
		if(_instance == 0)
			_instance = new Keyboard();
		return _instance;
	}

	int Keyboard::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlkeyboard",
			"keyboard",
			"SDL Keyboard Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Keyboard::__open(lua_State * L)
	{
		// Open stuff here.
		wrap_Keyboard_open(L);
		luax_register_gc(L, "sdlkeyboard", &__garbagecollect);
		return 0;
	}

	int Keyboard::__garbagecollect(lua_State * L)
	{
		Keyboard * m = Keyboard::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	bool Keyboard::isDown(int key) const
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;		
	}

} // sdlkeyboard
} // keyboard
} // love
