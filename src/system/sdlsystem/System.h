/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* System module using the SDL.
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_SYSTEM_SDLSYSTEM_SYSTEM_H
#define LOVE_SYSTEM_SDLSYSTEM_SYSTEM_H

// LOVE
#include "../../luax.h"

namespace love
{
namespace system
{
namespace sdlsystem
{
	class System
	{
	private:
		static System * _instance;
	protected:
		System();
	public:

		static System * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		/**
		* Returns an iterator function for
		* iterating over pending events.
		**/
		int events(lua_State * L);

		/**
		* The iterator function which iterates
		* pending SDL events.
		**/
		static int events_i(lua_State * L);

	}; // System

} // sdlsystem
} // system
} // love

#endif // LOVE_SYSTEM_SDLSYSTEM_SYSTEM_H
