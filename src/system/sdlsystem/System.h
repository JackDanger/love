/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
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
		static System * instance;
	protected:
		System();
	public:

		static System * getInstance();
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
