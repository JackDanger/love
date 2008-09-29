#include "love_sdlmouse.h"
#include "mod_sdlmouse.h"

// LOVE
#include <love/Core.h>

// SDL
#include <SDL.h>

namespace love_sdlmouse
{
	bool module_init(love::Core * core)
	{
		std::cout << "INIT love.mouse [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_quit(love::Core * core)
	{
		std::cout << "QUIT love.mouse [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_open(love::Core * core)
	{
		luaopen_mod_sdlmouse(core->getL());
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

	int getPosition(lua_State * L)
	{
		int n = lua_gettop(L);

		if( n != 0 )
			return luaL_error(L, "Funtion does not take parameters.");

		lua_pushnumber(L, getX());
		lua_pushnumber(L, getY());

		return 2;
	}

} // love_sdlmouse
