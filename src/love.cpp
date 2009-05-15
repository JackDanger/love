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
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

// STD

// SDL
#include <SDL.h>

// LOVE
#include "config.h"
#include "luax.h"
#include "constants.h"

// Modules
#include "event/sdl/wrap_Event.h"
#include "keyboard/sdl/wrap_Keyboard.h"
#include "mouse/sdl/wrap_Mouse.h"
#include "timer/sdl/wrap_Timer.h"
#include "joystick/sdl/wrap_Joystick.h"
#include "graphics/opengl/wrap_Graphics.h"
#include "image/devil/wrap_Image.h"
#include "filesystem/physfs/wrap_Filesystem.h"

#include "sound/sdlsound/Sound.h"
#include "audio/openal/Audio.h"
#include "physics/box2d/Physics.h"

#include "luasocket/luasocket.h"

const luaL_reg wrappers[] = {
	{ "love.event.sdl", love::event::sdl::wrap_Event_open },
	{ "love.keyboard.sdl", love::keyboard::sdl::wrap_Keyboard_open },
	{ "love.mouse.sdl", love::mouse::sdl::wrap_Mouse_open },
	{ "love.timer.sdl", love::timer::sdl::wrap_Timer_open },
	{ "love.joystick.sdl", love::joystick::sdl::wrap_Joystick_open },
	{ "love.graphics.opengl", love::graphics::opengl::wrap_Graphics_open },
	{ "love.image.devil", love::image::devil::wrap_Image_open },
	{ "love.filesystem.physfs", love::filesystem::physfs::wrap_Filesystem_open },
	{ 0, 0 }
};

int module_searcher(lua_State * L)
{
	// Get the module name.
	const char * name = luaL_checkstring(L, 1);

	// Try to find it.
	for(const luaL_reg * r = wrappers; r->name != 0; r++)
	{
		if(strcmp(r->name, name) == 0)
		{
			// Found a module with that name!
			lua_pushcfunction(L, r->func);
			return 1;
		}
	}

	// Found nothing ...
	lua_pushfstring(L, "\n\tno LOVE module '%s'", name);
	return 1;
}

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
	love::sound::sdlsound::Sound::__advertise(L);
	love::audio::openal::Audio::__advertise(L);
	love::physics::box2d::Physics::__advertise(L);

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

	// Add the module searcher function.
	love::luax_register_searcher(L, module_searcher);

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
