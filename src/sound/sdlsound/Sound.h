/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_SOUND_SDLSOUND_SOUND_H
#define LOVE_SOUND_SDLSOUND_SOUND_H

// LOVE
#include "../../luax.h"
#include "SoundData.h"

namespace love
{
namespace sound
{
namespace sdlsound
{
	class Sound
	{
	private:
		static Sound * _instance;
	protected:
		Sound();
	public:

		static Sound * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		SoundData * newSoundData(love::filesystem::File * file);

	}; // Sound

} // sdlsound
} // sound
} // love

#endif // LOVE_SOUND_SDLSOUND_SOUND_H