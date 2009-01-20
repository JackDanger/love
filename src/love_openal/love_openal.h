/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_MODULE_OPENAL_H
#define LOVE_MODULE_OPENAL_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/filesystem/File.h"
#include "../liblove/luax.h"
#include "../liblove/types.h"
#include "../liblove/sound/SoundData.h"

// Module
#include "Channel.h"
#include "Sound.h"
#include "Music.h"

namespace love
{
namespace openal
{
	// Standard function.
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	int getNumChannels();

	Sound * newSound(SoundData * data);
	Music * newMusic(SoundData * data);
	Channel * newChannel();

	void play(Audible * audible, Channel * channel);
	void play(Audible * audible);

	void stop(Channel * channel);
	void pause(Channel * channel);
	void rewind(Channel * channel);

	void setVolume(float volume);
	float getVolume();

} // openal
} // love

#endif // LOVE_MODULE_OPENAL_H
