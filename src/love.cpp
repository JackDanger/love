/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-27
**/

// STD

// SDL
#include <SDL.h>

// LOVE
#include "config.h"
#include "luax.h"
#include "constants.h"

// Modules
#include "timer/sdltimer/Timer.h"
#include "system/sdlsystem/System.h"
#include "graphics/opengl/Graphics.h"
#include "mouse/sdlmouse/Mouse.h"
#include "keyboard/sdlkeyboard/Keyboard.h"
#include "image/devil/Image.h"
#include "sound/sdlsound/Sound.h"
#include "audio/openal/Audio.h"
#include "physics/box2d/Physics.h"
#include "joystick/sdljoystick/Joystick.h"

#include "luasocket/luasocket.h"


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
	love::timer::sdltimer::Timer::__advertise(L);
	love::system::sdlsystem::System::__advertise(L);
	love::keyboard::sdlkeyboard::Keyboard::__advertise(L);
	love::mouse::sdlmouse::Mouse::__advertise(L);
	love::graphics::opengl::Graphics::__advertise(L);
	love::image::devil::Image::__advertise(L);
	love::sound::sdlsound::Sound::__advertise(L);
	love::audio::openal::Audio::__advertise(L);
	love::physics::box2d::Physics::__advertise(L);
	love::joystick::sdljoystick::Joystick::__advertise(L);

	love::luasocket::__open(L);

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
	luaL_dofile(L, "../../src/lua/love2.lua");
	lua_close(L);
	printf("(press key)\n");
	getchar();
	printf("Done. This was: %s (%s)\n", LOVE_VERSION_STR.c_str(), LOVE_VERSION_CODENAME.c_str());
	return 0;
}

#endif // LOVE_BUILD_EXE
