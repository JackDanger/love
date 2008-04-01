#include "love_sdlkeyboard.h"

// SDL
#include <SDL.h>

// From SWIG.
extern "C" {
	int luaopen_mod_sdlkeyboard(lua_State * L);
}

namespace love_sdlkeyboard
{
	bool init(love_mod::modconf * conf)
	{
		love_mod::setConf(conf);
		love_mod::report_init("love.keyboard", "SDL");
		return true;
	}

	bool quit()
	{
		love_mod::report_init("love.keyboard", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_sdlkeyboard(s);
		love_mod::do_string("love.keyboard = mod_sdlkeyboard");
		return true;
	}


	bool isDown(int key)
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;		
	}

} // love_sdlkeyboard
