#include "love_sdlkeyboard.h"
#include "mod_sdlkeyboard.h"

// LOVE
#include <love/Core.h>

// SDL
#include <SDL.h>

namespace love_sdlkeyboard
{
	bool module_init(love::Core * core)
	{
		std::cout << "INIT love.keyboard [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_quit(love::Core * core)
	{
		std::cout << "QUIT love.keyboard [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_open(love::Core * core)
	{
		luaopen_mod_sdlkeyboard(core->getL());
		return true;
	}

	bool isDown(int key)
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;		
	}

} // love_sdlkeyboard
