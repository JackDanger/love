/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-04-08
*/

#ifndef LOVE_MOD_SYSTEM_H
#define LOVE_MOD_SYSTEM_H

// LOVE
#include <love/mod.h>
#include <love/Game.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_system
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
		* This function takes LOVE into suspended mode, 
		* with the specified error message.
		* @param msg The message to display in suspended mode.
		**/
		void DECLSPEC error(const char * msg);

		/**
		* A warning does pretty much the same thing as an 
		* error, but a different error message is shown.
		* @param msg The message to display in suspended mode.
		**/
		void DECLSPEC warning(const char * msg);

		/**
		* Sends a message to the error game.
		* @param msg The message to send.
		* @param tag Indicates the purpose of the message.
		**/
		void DECLSPEC message(const char * msg, int tag);

		int DECLSPEC include(lua_State * L);

		const love::pGame DECLSPEC & getGame();

	}

	/**
	* Gets the current version of LOVE.
	* @return Return values will be on the format "0.2.1".
	**/
	const char * getVersion();

	/**
	* Gets the codename for this version. (For fun :)
	* @return A string containing the codename, such as "Mini-Moose".
	**/
	const char * getCodename();

	/**
	* Get a string representing the current platform.
	* @return "Windows" or "Linux", currently.
	**/
	const char * getPlatform();

	/**
	* Immediately quits LOVE.
	**/
	void exit();

	/**
	* Makes the error handler game the current game. This
	* function will also be available from the error handler
	* game, but will have no effect if called from it.
	**/
	void suspend();

	/**
	* Sets the main game as the current game. Will
	* not have any effect if called from the main game.
	**/
	void resume();

	/**
	* Restarts the current game.
	**/
	void restart();

} // love_system

#endif // LOVE_MOD_SYSTEM_H
