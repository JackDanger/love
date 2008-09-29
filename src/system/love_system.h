/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
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
	
	// Standard module functions.
	bool module_init(love::Core * core);
	bool module_quit(love::Core * core);
	bool module_open(love::Core * core);

	/**
	* This function takes LOVE into suspended mode, 
	* with the specified error message. Called syserr() and not 
	* error() because there are name conflicts with something
	* in GCC.
	* @param msg The message to display in suspended mode.
	**/
	void syserr(const char * msg);

	/**
	* A warning does pretty much the same thing as an 
	* error, but a different error message is shown. Called syswarn()
	* and not warning() to prevent name conflicts.
	* @param msg The message to display in suspended mode.
	**/
	void syswarn(const char * msg);

	/**
	* Sends a message to the error game.
	* @param msg The message to send.
	* @param tag Indicates the purpose of the message.
	**/
	void message(const char * msg, int tag);

	/**
	* This "native" function includes and runs
	* some file containing Lua code.
	**/
	int include(lua_State * L);

	/**
	* Gets a reference to the current game. This is used
	* by the main loop to determine the current game each
	* frame.
	* @return A reference to the current game.
	**/
	const love::pGame DECLSPEC & getGame();

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

	/**
	* Grabs or ungrabs input.
	* @grab True grabs input, false ungrabs.
	**/
	void grabInput(bool grab);

	// Error handler functions.
	int runtime_error(lua_State * L);
	void compile_error(lua_State * L, int status);

} // love_system

#endif // LOVE_MOD_SYSTEM_H
