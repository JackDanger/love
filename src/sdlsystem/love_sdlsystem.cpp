#include "love_sdlsystem.h"
#include "mod_sdlsystem.h"

// STL
#include <math.h>

// SDL
#include <SDL.h>

// LOVE
#include <love/Core.h>
#include <love/version.h>
#include <love/constants.h>

namespace love_sdlsystem
{

	love::Core * core = 0;

	bool module_init(love::Core * core)
	{
		// Init SDL.
		if(SDL_Init(0))
		{
			std::cerr << "Could not init SDL. " << SDL_GetError() << std::endl;
			return false;
		}

		love_sdlsystem::core = core;

		std::cout << "INIT love.system [" << "SDL" << "]" << std::endl;


		// Enable UNICODE. This is needed for input to work properly.
		SDL_EnableUNICODE(1);

		return true;
	}

	bool module_quit(love::Core * core)
	{
		std::cout << "QUIT love.system [" << "SDL" << "]" << std::endl;
		SDL_Quit();
		return true;
	}

	bool module_open(love::Core * core)
	{
		luaopen_mod_sdlsystem(core->getL());
		return true;
	}

	const char * getVersion()
	{
		return LOVE_VERSION_STR;
	}

	const char * getCodename()
	{
		return LOVE_VERSION_CODENAME;
	}

	const char * getPlatform()
	{
#ifdef WIN32
		return "Windows";
#else
		return "Linux";
#endif
	}

	void exit()
	{
		//SDL_Event e;
		//e.type = love::EVENT_QUIT;
		//SDL_PushEvent(&e);
		::exit(0);
	}

	void restart()
	{
		SDL_Event e;
		e.type = love::EVENT_QUIT;
		SDL_PushEvent(&e);
	}

	void grabInput(bool grab)
	{
		if(grab)
			SDL_WM_GrabInput(SDL_GRAB_ON);
		else
			SDL_WM_GrabInput(SDL_GRAB_OFF);
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

	int waitEvent()
	{
		static SDL_Event e;
		SDL_WaitEvent(&e);
		return e.type;
	};

} // love_sdlsystem
