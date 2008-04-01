#include "love_sdlmouse.h"

// SDL
#include <SDL.h>

// From SWIG.
extern "C" {
	int luaopen_mod_sdlmouse(lua_State * L);
}

namespace love_sdlmouse
{
	bool init(love_mod::modconf * conf)
	{
		// Standard mod setup.
		love_mod::setConf(conf);
		love_mod::report_init("love.mouse", "SDL");
		return true;
	}

	bool quit()
	{
		love_mod::report_init("love.mouse", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_sdlmouse(s);
		love_mod::do_string("love.mouse = mod_sdlmouse");
		return true;
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

} // love_sdlmouse
