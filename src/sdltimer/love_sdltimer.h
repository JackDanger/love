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
	
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC module_init(int argc, char ** argv, love::Core * core);
		bool DECLSPEC module_quit();
		bool DECLSPEC module_open(void * vm);

		/**
		* Updates the timer one step. Should only
		* be called once per frame.
		**/
		void DECLSPEC step();

		/**
		* Gets the current delta (does not update). 
		* Can be called multiple times per frame.
		**/
		float DECLSPEC getDelta();
	}
	
	/**
	* Gets the average FPS for the previous second.
	**/
	float getFPS();

	/**
	* Causes execution to sleep for a certain
	* amout of milliseconds.
	**/
	void sleep(int ms);

} // love_sdltimer

#endif // LOVE_MOD_SDLTIMER_H
