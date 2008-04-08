#include "love_system.h"
#include "../events.h"
#include "../version.h"

// SDL
#include <SDL.h>

// From SWIG.
extern "C" {
	int luaopen_mod_system(lua_State * L);
}

namespace love_system
{
	bool init(love_mod::modconf * conf)
	{
		love_mod::setConf(conf);
		love_mod::report_init("love.system", "love");

		return true;
	}

	bool quit()
	{
		love_mod::report_init("love.system", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_system(s);
		love_mod::do_string("love.system = mod_system");
		return true;
	}

	const char * getVersion()
	{
		return LOVE_VERSION_STR;
	}

	const char * getCodeName()
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
		SDL_Event e;
		e.type = SDL_QUIT;

		if( SDL_PushEvent(&e) != 0 )
			love_mod::error("Could not exit.");
	}

	void restart()
	{
		SDL_Event e;
		e.type = love::EVENT_RESTART;

		if( SDL_PushEvent(&e) != 0 )
			love_mod::error("Could not restart.");
	}

	void suspend()
	{
		SDL_Event e;
		e.type = love::EVENT_SUSPEND;

		if( SDL_PushEvent(&e) != 0 )
			love_mod::error("Could not suspend.");
	}

	void print(const char * msg)
	{
		std::string str(msg);
		love_mod::print(str);
	}

} // love_system
