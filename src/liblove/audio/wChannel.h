/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#ifndef LOVE_CHANNEL_TYPE_W
#define LOVE_CHANNEL_TYPE_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_CHANNEL_BITS = (LOVE_CHANNEL_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkchannel(L, idx) luax_checktype<Channel>(L, idx, "Channel", LOVE_CHANNEL_BITS)

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

	static const luaL_Reg Channel_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "setPitch", _wrap_Channel_setPitch },
		{ "getPitch", _wrap_Channel_getPitch },
		{ "setVolume", _wrap_Channel_setVolume },
		{ "getVolume", _wrap_Channel_getVolume },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_CHANNEL_TYPE_W
