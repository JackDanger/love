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

#include "wrap_SoundData.h"

namespace love
{
namespace sound
{
	SoundData * luax_checksounddata(lua_State * L, int idx)
	{
		return luax_checktype<SoundData>(L, idx, "SoundData", LOVE_SOUND_SOUND_DATA_BITS);
	}

	int _wrap_SoundData_getPointer(lua_State * L)
	{
		SoundData * t = luax_checksounddata(L, 1);
		lua_pushlightuserdata(L, t->getData());
		return 1;
	}

	int _wrap_SoundData_getSize(lua_State * L)
	{
		SoundData * sd = luax_checksounddata(L, 1);
		lua_pushinteger(L, sd->getSize());
		return 1;
	}

	int _wrap_SoundData_getChannels(lua_State * L)
	{
		SoundData * t = luax_checksounddata(L, 1);
		lua_pushinteger(L, t->getChannels());
		return 1;
	}

	int _wrap_SoundData_getBits(lua_State * L)
	{
		SoundData * t = luax_checksounddata(L, 1);
		lua_pushinteger(L, t->getBits());
		return 1;
	}

	int _wrap_SoundData_getSampleRate(lua_State * L)
	{
		SoundData * t = luax_checksounddata(L, 1);
		lua_pushinteger(L, t->getSampleRate());
		return 1;
	}

	int _wrap_SoundData_setSample(lua_State * L)
	{
		SoundData * sd = luax_checksounddata(L, 1);
		int i = (int)lua_tointeger(L, 2);
		float sample = (float)lua_tonumber(L, 3);
		sd->setSample(i, sample);
		return 0;
	}

	int _wrap_SoundData_getSample(lua_State * L)
	{
		SoundData * sd = luax_checksounddata(L, 1);
		int i = (int)lua_tointeger(L, 2);
		lua_pushnumber(L, sd->getSample(i));
		return 1;
	}

	static const luaL_Reg wrap_SoundData_functions[] = {
		{ "getPointer", _wrap_SoundData_getPointer },
		{ "getSize", _wrap_SoundData_getSize },
		{ "getChannels", _wrap_SoundData_getChannels },
		{ "getBits", _wrap_SoundData_getBits },
		{ "getSampleRate", _wrap_SoundData_getSampleRate },
		{ "setSample", _wrap_SoundData_setSample },
		{ "getSample", _wrap_SoundData_getSample },
		{ 0, 0 }
	};
	
	int wrap_SoundData_open(lua_State * L)
	{
		luax_register_type(L, "SoundData", wrap_SoundData_functions);
		return 0;
	}

} // sound
} // love
