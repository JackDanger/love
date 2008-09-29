/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* An interface to the keyboard device via SDL.
* 
* @author Anders Ruud
* @date 2008-03-16
*/
#ifndef LOVE_MOD_SDLKEYBOARD_H
#define LOVE_MOD_SDLKEYBOARD_H

// LOVE
#include <love/mod.h>

namespace love_sdlkeyboard
{
	// Standard module functions.
	bool module_init(love::Core * core);
	bool module_quit(love::Core * core);
	bool module_open(love::Core * core);

	/**
	* Checks whether a certain key is down or not.
	* @param key A key identifier.
	**/
	bool isDown(int key);

} // love_sdlkeyboard

#endif // LOVE_MOD_SDLKEYBOARD_H
