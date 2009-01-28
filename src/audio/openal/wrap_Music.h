/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_AUDIO_OPENAL_WRAP_MUSIC_H
#define LOVE_AUDIO_OPENAL_WRAP_MUSIC_H

#include "../../wrap.h"
#include "Music.h"

namespace love
{
namespace audio
{
namespace openal
{
	Music * luax_checkmusic(lua_State * L, int idx);
	int wrap_Music_open(lua_State * L);

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_WRAP_MUSIC_H
