/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_SOUND_SDLSOUND_WRAP_SOUND_H
#define LOVE_SOUND_SDLSOUND_WRAP_SOUND_H

// LOVE
#include "../../luax.h"
#include "wrap_SoundData.h"

namespace love
{
namespace sound
{
namespace sdlsound
{

	int _wrap_newSoundData(lua_State * L);
	int wrap_Sound_open(lua_State * L);

} // sdlsound
} // sound
} // love

#endif // LOVE_SOUND_SDLSOUND_WRAP_SOUND_H
