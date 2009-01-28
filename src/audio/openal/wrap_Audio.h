/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-18
**/

#ifndef LOVE_AUDIO_OPENAL_WRAP_AUDIO_H
#define LOVE_AUDIO_OPENAL_WRAP_AUDIO_H

// LOVE
#include "../../wrap.h"
#include "Audio.h"
#include "wrap_Audible.h"
#include "wrap_Sound.h"
#include "wrap_Music.h"
#include "wrap_Channel.h"

namespace love
{
namespace audio
{
namespace openal
{
	int _wrap_getNumChannels(lua_State * L);
	int _wrap_newSound(lua_State * L);
	int _wrap_newMusic(lua_State * L);
	int _wrap_newChannel(lua_State * L);
	int _wrap_play(lua_State * L);
	int _wrap_stop(lua_State * L);
	int _wrap_pause(lua_State * L);
	int _wrap_rewind(lua_State * L);
	int _wrap_setVolume(lua_State * L);
	int _wrap_getVolume(lua_State * L);
	int wrap_Audio_open(lua_State * L);

} // openal
} // audio
} // love


#endif // LOVE_AUDIO_OPENAL_WRAP_AUDIO_H
