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

// STD

// SDL
#include <SDL.h>

// LOVE
#include "common/config.h"
#include "common/runtime.h"
#include "common/constants.h"

// Modules
#include "modules/audio/openal/wrap_Audio.h"
#include "modules/event/sdl/wrap_Event.h"
#include "modules/filesystem/physfs/wrap_Filesystem.h"
#include "modules/graphics/opengl/wrap_Graphics.h"
#include "modules/image/devil/wrap_Image.h"
#include "modules/joystick/sdl/wrap_Joystick.h"
#include "modules/keyboard/sdl/wrap_Keyboard.h"
#include "modules/mouse/sdl/wrap_Mouse.h"
#include "modules/physics/box2d/wrap_Physics.h"
#include "modules/sound/sdlsound/wrap_Sound.h"
#include "modules/timer/sdl/wrap_Timer.h"

// Libraries.
#include "libraries/luasocket/luasocket.h"
#include "libraries/lanes/lanes.h"

static const luaL_reg wrappers[] = {
	{ "love.audio.openal", love::audio::openal::wrap_Audio_open },
	{ "love.filesystem.physfs", love::filesystem::physfs::wrap_Filesystem_open },
	{ "love.event.sdl", love::event::sdl::wrap_Event_open },
	{ "love.keyboard.sdl", love::keyboard::sdl::wrap_Keyboard_open },
	{ "love.mouse.sdl", love::mouse::sdl::wrap_Mouse_open },
	{ "love.timer.sdl", love::timer::sdl::wrap_Timer_open },
	{ "love.joystick.sdl", love::joystick::sdl::wrap_Joystick_open },
	{ "love.graphics.opengl", love::graphics::opengl::wrap_Graphics_open },
	{ "love.image.devil", love::image::devil::wrap_Image_open },
	{ "love.physics.box2d", love::physics::box2d::wrap_Physics_open },
	{ "love.sound.sdlsound", love::sound::sdlsound::wrap_Sound_open },
	{ 0, 0 }
};

static int module_searcher(lua_State * L)
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

DECLSPEC int luaopen_love(lua_State * L)
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

	// Add the module searcher function.
	//love::luax_register_searcher(L, module_searcher);

	love::luax_preload(L, love::audio::openal::wrap_Audio_open, "love.audio.openal");
	love::luax_preload(L, love::filesystem::physfs::wrap_Filesystem_open, "love.filesystem.physfs");
	love::luax_preload(L, love::event::sdl::wrap_Event_open, "love.event.sdl");
	love::luax_preload(L, love::keyboard::sdl::wrap_Keyboard_open, "love.keyboard.sdl");
	love::luax_preload(L, love::mouse::sdl::wrap_Mouse_open, "love.mouse.sdl");
	love::luax_preload(L, love::timer::sdl::wrap_Timer_open, "love.timer.sdl");
	love::luax_preload(L, love::joystick::sdl::wrap_Joystick_open, "love.joystick.sdl");
	love::luax_preload(L, love::graphics::opengl::wrap_Graphics_open, "love.graphics.opengl");
	love::luax_preload(L, love::image::devil::wrap_Image_open, "love.image.devil");
	love::luax_preload(L, love::physics::box2d::wrap_Physics_open, "love.physics.box2d");
	love::luax_preload(L, love::sound::sdlsound::wrap_Sound_open, "love.sound.sdlsound");

	love::luasocket::__open(L);
	love::lanes::open(L);

	return 0;
}

#if LOVE_BUILD_EXE

int main(int argc, char ** argv)
{
	// Create the virtual machine.
	lua_State * L = lua_open();
	luaL_openlibs(L);

	love::luax_preload(L, luaopen_love, "love");

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
	//luaL_dofile(L, "../../src/scripts/boot.lua");
#	include "scripts/boot.lua.h"

	lua_close(L);

#ifdef LOVE_DEBUG
	printf("(press key)\n");
	getchar();
#endif
	printf("Done. This was: %s (%s)\n", LOVE_VERSION_STR.c_str(), LOVE_VERSION_CODENAME.c_str());
	return 0;
}

#endif // LOVE_BUILD_EXE
