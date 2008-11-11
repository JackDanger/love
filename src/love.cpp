/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

// Test change.

// STD

// SDL
#include <SDL.h>

// LOVE
#include "liblove/config.h"
#include "liblove/luax.h"
#include "liblove/constants.h"

// Modules
#include "love_sdltimer/love_sdltimer.h"
#include "love_opengl/love_opengl.h"
#include "love_physfs/love_physfs.h"
#include "love_sdlsystem/love_sdlsystem.h"
#include "love_sdlmouse/love_sdlmouse.h"
#include "love_sdlkeyboard/love_sdlkeyboard.h"
#include "love_box2d/love_box2d.h"

int luaopen_love(lua_State * L)
{
	// Create the love table.
	lua_newtable(L);

	// TODO:
	// Install constants.
	for(int i = 0; love::lua_constants[i].name != 0; i++)
	{
		lua_pushinteger(L, love::lua_constants[i].value);
		lua_setfield(L, -2, love::lua_constants[i].name);
	}

	// __mod table.
	lua_newtable(L);
	lua_setfield(L, -2, "__mod");

	// __fin table.
	lua_newtable(L);
	lua_setfield(L, -2, "__fin");

	// Set the love table.
	lua_setglobal(L, "love");

	//
	// This will create a table roughly
	// equal to this: 
	// 
	// love.__mod = {
	//   graphics = {
	//      opengl = { ... },
	//      directx = { ... }
	//   },
	//   timer = {
	//      sdltimer = { ... },
	//      wintimer = { ... },
	//   },
	//   -- etc
	//  

	// Advertise here.

	love::sdlsystem::luainfo(L);
	love::opengl::luainfo(L);
	love::sdltimer::luainfo(L);
	love::physfs::luainfo(L);
	love::sdlmouse::luainfo(L);
	love::sdlkeyboard::luainfo(L);
	love::box2d::luainfo(L);

	return 0;
}

#if LOVE_BUILD_EXE

int main(int argc, char ** argv)
{
	// Create the virtual machine.
	lua_State * L = lua_open();
	luaL_openlibs(L);

	luaopen_love(L);

	// Add command line arguments to love.__args
	{
		lua_getglobal(L, "love");
		lua_newtable(L);
		for(int i = 0;i<argc;i++)
		{
			lua_pushstring(L, argv[i]);
			lua_rawseti(L, -2, i);
		}
		lua_setfield(L, -2, "__args");
		lua_pop(L, 1);
	}

	// Add love.__exe = true.
	// This indicates that we're running the 
	// standalone version of love, and not the
	// DLL version.
	{
		lua_getglobal(L, "love");
		lua_pushboolean(L, 1);
		lua_setfield(L, -2, "__exe");
		lua_pop(L, 1);
	}

	// This is where we should run the built-in Lua code
	// which gets everything started.

	// TODO: This is obviously test code.
	luaL_dofile(L, "test.lua");
	lua_close(L);

	getchar();
	return 0;
}

#endif
