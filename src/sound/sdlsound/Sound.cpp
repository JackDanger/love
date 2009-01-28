/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
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
