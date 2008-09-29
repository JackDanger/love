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
	* Returns an iterator function for
	* iterating over pending events.
	**/
	int events(lua_State * L);

	/**
	* The iterator function which iterates
	* pending SDL events.
	**/
	int events_i(lua_State * L);

} // love_sdlsystem

#endif // LOVE_MOD_SDLSYSTEM_H
