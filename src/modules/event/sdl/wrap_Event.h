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
**/

#ifndef LOVE_EVENT_SDL_WRAP_EVENT_H
#define LOVE_EVENT_SDL_WRAP_EVENT_H

// LOVE
#include "Event.h"

namespace love
{
namespace event
{
namespace sdl
{
	int _wrap_get(lua_State * L);
	int _wrap_quit(lua_State * L);

	int wrap_Event_open(lua_State * L);

} // sdl
} // event
} // love

#endif // LOVE_EVENT_SDL_WRAP_EVENT_H
