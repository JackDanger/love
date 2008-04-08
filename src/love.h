/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-03-15
*/

#ifndef LOVE_H
#define LOVE_H

#include "version.h"

// Modules.
#ifdef WIN32
#	define LOVE_WINDOWS
#	define LOVE_MOD_FILESYSTEM "love_physfs.dll"
#	define LOVE_MOD_PHYSICS	"love_chipmunk.dll"
#	define LOVE_MOD_GRAPHICS "love_opengl.dll"
#	define LOVE_MOD_TIMER "love_sdltimer.dll"
#	define LOVE_MOD_KEYBOARD "love_sdlkeyboard.dll"
#	define LOVE_MOD_MOUSE "love_sdlmouse.dll"
#	define LOVE_MOD_AUDIO "love_sdlmixer.dll"
#	define LOVE_MOD_SYSTEM "love_system.dll"
#else
#	define LOVE_LINUX
#	define LOVE_MOD_PATH "/usr/lib/love/"
#	define LOVE_MOD_FILESYSTEM "./love_physfs.so"
#	define LOVE_MOD_PHYSICS	"./love_chipmunk.so"
#	define LOVE_MOD_GRAPHICS "./love_opengl.so"
#	define LOVE_MOD_TIMER "./love_sdltimer.so"
#	define LOVE_MOD_KEYBOARD "./love_sdlkeyboard.so"
#	define LOVE_MOD_MOUSE "./love_sdlmouse.so"
#	define LOVE_MOD_AUDIO "./love_sdlmixer.so"
#	define LOVE_MOD_SYSTEM "./love_system.so"
#endif

// STD
#include <string>

namespace love
{
	/**
	* Inits LOVE MACHINE, and all modules.
	**/
	bool init(int argc, char* argv[]);

	/**
	* Quits LOVE MACHINE and all modules.
	**/
	bool quit();

	/**
	* Should print message to console, and possibly
	* stdout.
	**/
	void print(const char * str);	

	/**
	* This is supposed to be the error handler. 
	* (This does not trigger errors).
	**/
	void error(const char * str);

	/**
	* Pops the top Game off the game stack. If there's 
	* only one game left on the stack, nothing happens.
	**/
	void pop();

	/**
	* Restarts the Game at the top of the stack.
	**/
	void restart();

	/**
	* Main loop. Events are delegated to the
	* current game from this function.
	**/
	int loop();
}

#endif // LOVE MACHINE
