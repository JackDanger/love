/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* An interface to add gamepad devices via SDL.
* 
* @author Anders Ruud
* @date 2008-03-16
*/
#ifndef LOVE_MOD_SDLJOYSTICK_H
#define LOVE_MOD_SDLJOYSTICK_H

// LOVE
#include <love/mod.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_sdljoystick
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	int test();

} // love_sdljoystick

#endif // LOVE_MOD_SDLJOYSTICK_H
