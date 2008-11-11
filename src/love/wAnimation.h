/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-08
**/

#ifndef LOVE_ANIMATION_W
#define LOVE_ANIMATION_W

#include "luax.h"

#include "wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_ANIMATION_BITS = (LOVE_ANIMATION_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkanimation(L, idx) luax_checktype<Animation>(L, idx, "Animation", LOVE_WRAP_ANIMATION_BITS)

	int _wrap_Animation_addFrame(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float w = (float)luaL_checknumber(L, 4);
		float h = (float)luaL_checknumber(L, 5);
		float delay = (float)luaL_checknumber(L, 6);
		a->addFrame(x, y, w, h, delay);
		return 0;
	}

	int _wrap_Animation_setMode(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		int mode = luaL_checkint(L, 2);
		a->setMode(mode);
		return 0;
	}

	int _wrap_Animation_play(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		a->play();
		return 0;
	}

	int _wrap_Animation_stop(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		a->stop();
		return 0;
	}

	int _wrap_Animation_reset(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		a->reset();
		return 0;
	}

	int _wrap_Animation_seek(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		int frame = luaL_checkint(L, 2);
		a->seek(frame);
		return 0;
	}

	int _wrap_Animation_getCurrentFrame(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		lua_pushinteger(L, a->getCurrentFrame());
		return 1;
	}

	int _wrap_Animation_getSize(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		lua_pushinteger(L, a->getSize());
		return 1;
	}

	int _wrap_Animation_setDelay(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		int frame = luaL_checkint(L, 2);
		float delay = (float)luaL_checknumber(L, 3);
		a->setDelay(frame, delay);
		return 0;
	}

	int _wrap_Animation_setSpeed(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		float speed = (float)luaL_checknumber(L, 2);
		a->setSpeed(speed);
		return 0;
	}

	int _wrap_Animation_getSpeed(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		lua_pushnumber(L, a->getSpeed());
		return 1;
	}

	int _wrap_Animation_update(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		float dt = (float)luaL_checknumber(L, 2);
		a->update(dt);
		return 0;
	}

	int _wrap_Animation_setOffset(lua_State * L)
	{
		Animation * a = luax_checkanimation(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		a->setOffset(x, y);
		return 0;
	}

	static const luaL_Reg Animation_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "addFrame", _wrap_Animation_addFrame },
		{ "setMode", _wrap_Animation_setMode },
		{ "play", _wrap_Animation_play },
		{ "stop", _wrap_Animation_stop },
		{ "reset", _wrap_Animation_reset },
		{ "seek", _wrap_Animation_seek },
		{ "getCurrentFrame", _wrap_Animation_getCurrentFrame },
		{ "getSize", _wrap_Animation_getSize },
		{ "setDelay", _wrap_Animation_setDelay },
		{ "setSpeed", _wrap_Animation_setSpeed },
		{ "getSpeed", _wrap_Animation_getSpeed },
		{ "update", _wrap_Animation_update },
		{ "setOffset", _wrap_Animation_setOffset },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_ANIMATION_W
