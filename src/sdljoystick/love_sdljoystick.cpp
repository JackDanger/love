#include "love_sdljoystick.h"
#include "mod_sdljoystick.h"

// LOVE
#include <love/Core.h>

// SDL
#include <SDL.h>
#include <SDL_Joystick.h>

namespace love_sdljoystick
{
	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.gamepad [" << "SDL" << "]" << std::endl;
		
		// Set function pointers and load module.
		{
			love::Gamepad * g = core->getGamepad();
			g->loaded = true;
		}
		
		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.gamepad [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_sdljoystick(s);
		return true;
	}

	int test()
	{
		return 5;
	}

} // love_sdljoystick
