/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-09-28
*/

#ifndef LOVE_MOD_SDLSYSTEM_H
#define LOVE_MOD_SDLSYSTEM_H

// LOVE
#include <love/mod.h>

namespace love_sdlsystem
{	
	// Standard module functions.
	bool module_init(love::Core * core);
	bool module_quit(love::Core * core);
	bool module_open(love::Core * core);

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
	* Restarts the current game.
	**/
	void restart();

	/**
	* Grabs or ungrabs input.
	* @grab True grabs input, false ungrabs.
	**/
	void grabInput(bool grab);

	/**
	* Returns an iterator function for
	* iterating over pending events.
	**/
	int events(lua_State * L);

	/**
	* The iterator function which iterates
	* pending SDL events.
	**/
	int events_i(lua_State * L);

	/**
	* Blocks until some event occurs, then
	* returns the event.
	**/
	int waitEvent();

} // love_sdlsystem

#endif // LOVE_MOD_SDLSYSTEM_H
