/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#include "wrap_Channel.h"

namespace love
{
namespace audio
{
namespace openal
{
	Channel * luax_checkchannel(lua_State * L, int idx)
	{
		return luax_checktype<Channel>(L, idx, "Channel", LOVE_AUDIO_CHANNEL_BITS);
	}

	int _wrap_Channel_setPitch(lua_State * L)
	{
		Channel * t = luax_checkchannel(L, 1);
		float p = (float)luaL_checknumber(L, 2);
		t->setPitch(p);
		return 0;
	}

	int _wrap_Channel_getPitch(lua_State * L)
	{
		Channel * t = luax_checkchannel(L, 1);
		lua_pushnumber(L, t->getPitch());
		return 1;
	}

	int _wrap_Channel_setVolume(lua_State * L)
	{
		Channel * t = luax_checkchannel(L, 1);
		float p = (float)luaL_checknumber(L, 2);
		t->setVolume(p);
		return 0;
	}

	int _wrap_Channel_getVolume(lua_State * L)
	{
		Channel * t = luax_checkchannel(L, 1);
		lua_pushnumber(L, t->getVolume());
		return 1;
	}

	static const luaL_Reg wrap_Channel_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setPitch", _wrap_Channel_setPitch },
		{ "getPitch", _wrap_Channel_getPitch },
		{ "setVolume", _wrap_Channel_setVolume },
		{ "getVolume", _wrap_Channel_getVolume },
		{ 0, 0 }
	};

	int wrap_Channel_open(lua_State * L)
	{
		luax_register_type(L, "Channel", wrap_Channel_functions);
		return 0;
	}

} // openal
} // audio
} // love
