/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
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
