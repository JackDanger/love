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

#include "wrap_Audible.h"

namespace love
{
namespace audio
{
namespace openal
{
	Audible * luax_checkaudible(lua_State * L, int idx)
	{
		return luax_checktype<Audible>(L, idx, "Audible", LOVE_AUDIO_AUDIBLE_BITS);
	}

	static const luaL_Reg wrap_Audible_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

	int wrap_Audible_open(lua_State * L)
	{
		luax_register_type(L, "Audible", wrap_Audible_functions);
		return 0;
	}

} // openal
} // audio
} // love
