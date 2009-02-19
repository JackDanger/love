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

#include "Sound.h"

// LOVE
#include "wrap_SoundData.h"

namespace love
{
namespace sound
{
namespace sdlsound
{
	Sound * Sound::_instance = 0;

	Sound::Sound()
	{
	}

	Sound * Sound::__getinstance()
	{
		if(_instance == 0)
			_instance = new Sound();
		return _instance;
	}

	int Sound::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"sdlsound",
			"sound",
			"SDL_sound Sound Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Sound::__open(lua_State * L)
	{
		Sound_Init();
		wrap_SoundData_open(L);
		luax_register_gc(L, "sdlsound", &__garbagecollect);
		return 0;
	}

	int Sound::__garbagecollect(lua_State * L)
	{
		Sound_Quit();
		Sound * m = Sound::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	SoundData * Sound::newSoundData(love::filesystem::File * file)
	{
		return new SoundData(file);
	}

} // sdlsound
} // sound
} // love
