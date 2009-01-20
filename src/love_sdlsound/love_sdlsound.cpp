/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-16
**/

#include "love_sdlsound.h"

// STD
#include <iostream>
#include <cmath>

// LOVE
#include "../liblove/version.h"
#include "../liblove/constants.h"

// SDL_sound
#include <SDL_sound.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdlsound
#define LOVE_WRAP_BITS LOVE_SDLSOUND_BITS
#include "../liblove/sound/wsound.h"

namespace love
{
namespace sdlsound
{

	int luainfo(lua_State * L)
	{
		luax_register_info(L,
			"sdlsound",
			"sound",
			"SDL_sound Sound Module",
			"LOVE Development Team",
			luaopen);

		

		return 0;
	}

	int luaopen(lua_State * L)
	{
		Sound_Init();
		luareg(L);
		luax_register_gc(L, "sdlsound", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		Sound_Quit();
		return 0;
	}

	SoundData * newSoundData(File * file)
	{
		return new SoundData(file);
	}

} // sdlsound
} // love
