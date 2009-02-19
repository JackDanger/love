/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* -- LOVE Development Team, http://love2d.org
**/

#include "wrap_Sound.h"

// LOVE
#include "Sound.h"

namespace love
{
namespace sound
{
namespace sdlsound
{

	int _wrap_newSoundData(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		love::filesystem::File * file = luax_checktype<love::filesystem::File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
		SoundData * t = Sound::__getinstance()->newSoundData(file);
		luax_newtype(L, "SoundData", LOVE_SOUND_SOUND_DATA_BITS, (void*)t);
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Sound_functions[] = {
		{ "newSoundData",  _wrap_newSoundData },
		{ 0, 0 }
	};

	int wrap_Sound_open(lua_State * L)
	{
		luax_register_module(L, "sound", wrap_Sound_functions);
		wrap_SoundData_open(L);
		return 0;
	}

} // sdlsound
} // sound
} // love
