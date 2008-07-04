/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This is a timer module based on SDL's SDL_GetTicks.
* It's not extremely precise, but it works everywhere.
* 
* @author Anders Ruud
* @date 2008-03-16
*/

#ifndef LOVE_MOD_SDLTIMER_H
#define LOVE_MOD_SDLTIMER_H

// LOVE
#include <love/mod.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_sdltimer
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	/**
	* Updates the timer one step. Should only
	* be called once per frame.
	**/
	void step();

	/**
	* Gets the current delta (does not update). 
	* Can be called multiple times per frame.
	**/
	float getDelta();
	
	/**
	* Gets the average FPS for the previous second.
	**/
	float getFPS();

	/**
	* Causes execution to sleep for a certain
	* amout of milliseconds.
	**/
	void sleep(int ms);

	/**
	* Returns the time since the initialization of the
	* module. 
	* @return The time in seconds.
	**/
	float getTime();

} // love_sdltimer

#endif // LOVE_MOD_SDLTIMER_H
