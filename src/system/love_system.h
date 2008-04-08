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
#include "../mod.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_system
{
	
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC init(love_mod::modconf * conf);
		bool DECLSPEC quit();
		bool DECLSPEC luaopen(lua_State * s);
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
	const char * getCodeName();

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
	* Immediately restarts the current game.
	**/
	void restart();

	/**
	* Immediately suspends the current game. Should
	* only be used for development purposes.
	**/
	void suspend(); 

	/**
	* Prints a message graphically and to stdout.
	* @param msg The message to print.
	**/
	void print(const char * msg);

} // love_system

#endif // LOVE_MOD_SYSTEM_H
