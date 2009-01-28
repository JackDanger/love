/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-18
**/

// LOVE
#include "wrap_Audio.h"

namespace love
{
namespace audio
{
namespace openal
{
	int _wrap_getNumChannels(lua_State * L)
	{
		lua_pushinteger(L, Audio::__getinstance()->getNumChannels());
		return 1;
	}

	int _wrap_newSound(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to SoundData, if necessary.
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "sound", "newSoundData");

		love::sound::SoundData * data = luax_checktype<love::sound::SoundData>(L, 1, "SoundData", LOVE_SOUND_SOUND_DATA_BITS);
		Sound * t = Audio::__getinstance()->newSound(data);
		luax_newtype(L, "Sound", LOVE_AUDIO_SOUND_BITS, (void*)t);
		return 1;
	}

	int _wrap_newMusic(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to SoundData, if necessary.
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "sound", "newSoundData");

		love::sound::SoundData * data = luax_checktype<love::sound::SoundData>(L, 1, "SoundData", LOVE_SOUND_SOUND_DATA_BITS);
		Music * t = Audio::__getinstance()->newMusic(data);
		luax_newtype(L, "Music", LOVE_AUDIO_MUSIC_BITS, (void*)t);
		return 1;
	}

	int _wrap_newChannel(lua_State * L)
	{
		Channel * t = Audio::__getinstance()->newChannel();
		luax_newtype(L, "Channel", LOVE_AUDIO_CHANNEL_BITS, (void*)t);
		return 1;
	}

	int _internal_play_audible(lua_State * L)
	{
		int top = lua_gettop(L);

		// play( audible )
		if(top == 1)
		{
			Audible * a = luax_checkaudible(L, 1);
			Audio::__getinstance()->play(a);
			return 0;
		}
		// play( audible, channel )
		else if(top == 2)
		{
			Audible * a = luax_checkaudible(L, 1);
			Channel * c = luax_checkchannel(L, 2);
			Audio::__getinstance()->play(a, c);
			return 0;
		}

		return luaL_error(L, "No matching overload");
	}

	int _wrap_play(lua_State * L)
	{
		if(luax_istype(L, 1, LOVE_AUDIO_MUSIC_BITS))
		{
			// In the case of music, we need to make a copy of the
			// SoundData object and replace it with the one on the stack.
			Music * m = luax_checkmusic(L, 1);

			// Get a copy.
			Music * clone = m->clone();

			// Push it onto the stack.
			luax_newtype(L, "Music", LOVE_AUDIO_MUSIC_BITS, (void*)clone);

			// Replace the current music object. 
			lua_replace(L, 1);
		}
		// Else: a sound object is being passed, in which 
		// case we do not need to copy the SoundData object.

		return _internal_play_audible(L);
	}

	int _wrap_stop(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		Audio::__getinstance()->stop(c);
		return 0;
	}

	int _wrap_pause(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		Audio::__getinstance()->pause(c);
		return 0;
	}

	int _wrap_rewind(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		Audio::__getinstance()->rewind(c);
		return 0;
	}

	int _wrap_setVolume(lua_State * L)
	{
		float v = (float)luaL_checknumber(L, 1);
		Audio::__getinstance()->setVolume(v);
		return 0;
	}

	int _wrap_getVolume(lua_State * L)
	{
		lua_pushnumber(L, Audio::__getinstance()->getVolume());
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Audio_functions[] = {
		{ "getNumChannels", _wrap_getNumChannels },
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

	int wrap_Audio_open(lua_State * L)
	{
		luax_register_module(L, "audio", wrap_Audio_functions);
		wrap_Channel_open(L);
		wrap_Audible_open(L);
		wrap_Music_open(L);
		wrap_Sound_open(L);
		return 0;
	}

} // openal
} // audio
} // love
