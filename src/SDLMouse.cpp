#include "SDLMouse.h"

#include <SDL.h>

namespace love
{

	SDLMouse::~SDLMouse()
	{
		quit();
	}

	bool SDLMouse::init(int argc, char* argv[])
	{
		return true;
	}

	void SDLMouse::quit()
	{
	}

	float SDLMouse::getX() const
	{
		int x;
		SDL_GetMouseState(&x, 0);
		return (float)x;
	}

	float SDLMouse::getY() const
	{
		int y;
		SDL_GetMouseState(0, &y);
		return (float)y;
	}

	bool SDLMouse::isDown(int button) const
	{
		return (SDL_GetMouseState(0, 0) & SDL_BUTTON(button)) != 0;
	}

	void SDLMouse::setVisible(bool visible)
	{
		SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
	}

	bool SDLMouse::isVisible() const
	{
		return (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE) ? true : false;
	}

}// love
