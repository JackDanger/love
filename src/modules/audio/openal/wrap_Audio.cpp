/**
* Copyright (c) 2006-2009 LOVE Development Team
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
**/

// LOVE
#include "wrap_Audio.h"

namespace love
{
namespace audio
{
namespace openal
{
	static Audio * instance = 0;

	int _wrap_getNumChannels(lua_State * L)
	{
		lua_pushinteger(L, instance->getNumChannels());
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
		Sound * t = instance->newSound(data);
		luax_newtype(L, "Sound", LOVE_AUDIO_SOUND_BITS, (void*)t);
		return 1;
	}

	/*
	int _wrap_newMusic(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to SoundData, if necessary.
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "sound", "newSoundData");

		love::sound::SoundData * data = luax_checktype<love::sound::SoundData>(L, 1, "SoundData", LOVE_SOUND_SOUND_DATA_BITS);
		Music * t = instance->newMusic(data);
		luax_newtype(L, "Music", LOVE_AUDIO_MUSIC_BITS, (void*)t);
		return 1;
	}
	*/

	int _wrap_newChannel(lua_State * L)
	{
		Channel * t = instance->newChannel();
		luax_newtype(L, "Channel", LOVE_AUDIO_CHANNEL_BITS, (void*)t);
		return 1;
	}

	/*

	int _internal_play_audible(lua_State * L)
	{
		int top = lua_gettop(L);

		// play( audible )
		if(top == 1)
		{
			Audible * a = luax_checkaudible(L, 1);
			instance->play(a);
			return 0;
		}
		// play( audible, channel )
		else if(top == 2)
		{
			Audible * a = luax_checkaudible(L, 1);
			Channel * c = luax_checkchannel(L, 2);
			instance->play(a, c);
			return 0;
		}

		return luaL_error(L, "No matching overload");
	}

	*/

	int _wrap_play(lua_State * L)
	{
		int top = lua_gettop(L);

		// play( audible )
		if(top == 1 && luax_istype(L, 1, LOVE_AUDIO_SOUND_BITS))
		{
			Sound * s = luax_checksound(L, 1);
			instance->play(s);
			return 0;
		}

		// play( audible, channel )
		else if(top == 2 && luax_istype(L, 1, LOVE_AUDIO_SOUND_BITS))
		{
			Sound * s = luax_checksound(L, 1);
			Channel * c = luax_checkchannel(L, 2);
			instance->play(s, c);
			return 0;
		}

		return luaL_error(L, "No matching overload");
	}

	int _wrap_stop(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		instance->stop(c);
		return 0;
	}

	int _wrap_pause(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		instance->pause(c);
		return 0;
	}

	int _wrap_rewind(lua_State * L)
	{
		Channel * c = luax_checkchannel(L, 1);
		instance->rewind(c);
		return 0;
	}

	int _wrap_setVolume(lua_State * L)
	{
		float v = (float)luaL_checknumber(L, 1);
		instance->setVolume(v);
		return 0;
	}

	int _wrap_getVolume(lua_State * L)
	{
		lua_pushnumber(L, instance->getVolume());
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Audio_functions[] = {
		{ "getNumChannels", _wrap_getNumChannels },
		{ "newSound",  _wrap_newSound },
		//{ "newMusic",  _wrap_newMusic },
		{ "newChannel",  _wrap_newChannel },
		{ "play",  _wrap_play },
		{ "stop",  _wrap_stop },
		{ "pause",  _wrap_pause },
		{ "rewind",  _wrap_rewind },
		{ "setVolume",  _wrap_setVolume },
		{ "getVolume",  _wrap_getVolume },
		{ 0, 0 }
	};

	static const lua_CFunction wrap_Audio_types[] = {
		wrap_Channel_open,
		wrap_Audible_open,
		//wrap_Music_open,
		wrap_Sound_open,
		0
	};

	int wrap_Audio_open(lua_State * L)
	{
		if(instance == 0)
		{
			try 
			{
				instance = new Audio();
			} 
			catch(std::exception e)
			{
				return luaL_error(L, e.what());
			}
		}

		return luax_register_module(L, wrap_Audio_functions, wrap_Audio_types);
	}

} // openal
} // audio
} // love
