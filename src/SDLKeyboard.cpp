#include "SDLKeyboard.h"

#include <SDL.h>

namespace love
{

	SDLKeyboard::~SDLKeyboard()
	{
		quit();
	}

	bool SDLKeyboard::init(int argc, char* argv[])
	{
		return true;
	}

	void SDLKeyboard::quit()
	{
	}

	bool SDLKeyboard::isDown(int key) const
	{
		Uint8 * keystate = SDL_GetKeyState(0);
		return keystate[key] == 1;
	}


} //love
