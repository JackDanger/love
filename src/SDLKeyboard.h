/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDL_KEYBOARD_H
#define LOVE_SDL_KEYBOARD_H

// LOVE
#include "Keyboard.h"

namespace love
{

	/**
	* Abstract keyboard class.
	*
	* @author Anders Ruud
	* @date 2006-03-12
	**/
	class SDLKeyboard : public Keyboard
	{
	private:
	public:

		virtual ~SDLKeyboard();

		// From Device.
		bool init(int argc, char* argv[]);
		void quit();

		// From Keyboard.
		bool isDown(int key) const;

	}; // SDLKeyboard

}// love

#endif // LOVE_SDL_KEYBOARD_H
