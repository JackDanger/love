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

#include "Keyboard.h"

// SDL
#include <SDL.h>

namespace love
{
namespace keyboard
{
namespace sdl
{

	Keyboard * Keyboard::instance = 0;

	Keyboard::Keyboard()
	{
	}

	Keyboard * Keyboard::getInstance()
	{
		if(instance == 0)
			instance = new Keyboard();
		return instance;
	}

	int Keyboard::init(lua_State * L)
	{
		return 0;
	}

	int Keyboard::quit(lua_State * L)
	{
		// Delete instance
		if(instance != 0)
		{
			delete instance;
			instance = 0;
		}

		return 0;
	}

	const char * Keyboard::getName() const
	{
		return "love.keyboard.sdl";
	}

	bool Keyboard::isDown(int key) const
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;		
	}

} // sdl
} // keyboard
} // love
