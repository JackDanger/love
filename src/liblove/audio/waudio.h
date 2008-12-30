/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-18
**/

#ifndef LOVE_AUDIO_MODULE_W
#define LOVE_AUDIO_MODULE_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wAudible.h"
#include "wSound.h"
#include "wMusic.h"
#include "wChannel.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	int _wrap_newSound(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to SoundData, if necessary.
		if(luax_istype(L, 1, LOVE_FILE_BITS))
			luax_convobj(L, 1, "sound", "newSoundData");

		SoundData * data = luax_checktype<SoundData>(L, 1, "SoundData", LOVE_SOUND_DATA_BITS);
		Sound * t = newSound(data);
		luax_newtype(L, "Sound", LOVE_WRAP_SOUND_BITS, (void*)t);
		return 1;
	}

	int _wrap_newMusic(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to SoundData, if necessary.
		if(luax_istype(L, 1, LOVE_FILE_BITS))
			luax_convobj(L, 1, "sound", "newSoundData");

		SoundData * data = luax_checktype<SoundData>(L, 1, "SoundData", LOVE_SOUND_DATA_BITS);
		Music * t = newMusic(data);
		luax_newtype(L, "Music", LOVE_WRAP_MUSIC_BITS, (void*)t);
		return 1;
	}

	int _wrap_newChannel(lua_State * L)
	{
		Channel * t = newChannel();
		luax_newtype(L, "Channel", LOVE_WRAP_CHANNEL_BITS, (void*)t);
		return 1;
	}

	int _wrap_play(lua_State * L)
	{
		int top = lua_gettop(L);

		// play( audible )
		if(top == 1)
		{
			Audible * a = luax_checkaudible(L, 1);
			play(a);
			return 0;
		}
		// play( audible, channel )
		else if(top == 2)
		{
			Audible * a = luax_checkaudible(L, 1);
			Channel * c = luax_checkchannel(L, 2);
			play(a, c);
			return 0;
		}

		return luaL_error(L, "No matching overload");
	}

	int _wrap_stop(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		stop(c);
		return 0;
	}

	int _wrap_pause(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		pause(c);
		return 0;
	}

	int _wrap_rewind(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		rewind(c);
		return 0;
	}

	int _wrap_setVolume(lua_State * L)
	{
		float v = (float)luaL_checknumber(L, 1);
		setVolume(v);
		return 0;
	}

	int _wrap_getVolume(lua_State * L)
	{
		lua_pushnumber(L, getVolume());
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "newSound",  _wrap_newSound },
		{ "newMusic",  _wrap_newMusic },
		{ "newChannel",  _wrap_newChannel },
		{ "play",  _wrap_play },
		{ "stop",  _wrap_stop },
		{ "pause",  _wrap_pause },
		{ "rewind",  _wrap_rewind },
		{ "setVolume",  _wrap_setVolume },
		{ "getVolume",  _wrap_getVolume },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "audio", module_fn);
		luax_register_type(L, "Sound", Sound_mt);
		luax_register_type(L, "Music", Music_mt);
		luax_register_type(L, "Channel", Channel_mt);
		return 0;
	}

} // LOVE_WRAP_NAMESPACE
} // love

#endif // LOVE_AUDIO_MODULE_W
