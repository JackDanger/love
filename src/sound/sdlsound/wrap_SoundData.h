/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_SOUND_SDLSOUND_WRAP_SOUND_DATA_H
#define LOVE_SOUND_SDLSOUND_WRAP_SOUND_DATA_H

// LOVE
#include "../../wrap.h"
#include "SoundData.h"

namespace love
{
namespace sound
{
namespace sdlsound
{
	SoundData * luax_checksounddata(lua_State * L, int idx);
	int wrap_SoundData_open(lua_State * L);

} // sdlsound
} // sound
} // love

#endif // LOVE_SOUND_SDLSOUND_WRAP_SOUND_DATA_H
