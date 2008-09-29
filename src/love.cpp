/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-03-15
*/

// STD

// SDL
#include <SDL.h>

// LOVE
#include <love/Core.h>

// This neat macro makes static module 
// configuration prettier.
#define STATIC_MOD_EXTERN(ns) \
	namespace ns { \
		extern bool module_init(love::Core * core); \
		extern bool module_quit(love::Core * core); \
		extern bool module_open(love::Core * core); \
	} \

#define LOVE_MOD(ns) \
	love::Module(ns::module_init, ns::module_quit, ns::module_open) \

// Static module conf.
STATIC_MOD_EXTERN(love_sdlsystem);
STATIC_MOD_EXTERN(love_sdlkeyboard);
STATIC_MOD_EXTERN(love_sdlmouse);
STATIC_MOD_EXTERN(love_sdljoystick);
STATIC_MOD_EXTERN(love_sdltimer);
STATIC_MOD_EXTERN(love_physfs);
STATIC_MOD_EXTERN(love_opengl);
STATIC_MOD_EXTERN(love_box2d);
STATIC_MOD_EXTERN(love_luasocket);

typedef struct
{
	const char * name;
	const char * provides;
	love::Module module;
} modentry;

// Module list.
const static modentry love_libs[] = 
{
	{ "love_sdlsystem",		"love.system",		LOVE_MOD(love_sdlsystem) },
	{ "love_sdlkeyboard",	"love.keyboard",	LOVE_MOD(love_sdlkeyboard) },
	{ "love_sdlmouse",		"love.mouse",		LOVE_MOD(love_sdlmouse) },
	{ "love_sdljoystick",	"love.joystick",	LOVE_MOD(love_sdljoystick) },
	{ "love_sdltimer",		"love.timer",		LOVE_MOD(love_sdltimer) },
	{ "love_physfs",		"love.filesystem",	LOVE_MOD(love_physfs) },
	{ "love_opengl",		"love.graphics",	LOVE_MOD(love_opengl) },
	{ "love_box2d",			"love.physics",		LOVE_MOD(love_box2d) },
	{ "love_luasocket",		"love.luasocket",	LOVE_MOD(love_luasocket) },
	{ 0, 0, love::Module(0,0,0) }, // End
};

int modloader(lua_State * L)
{
	int i = (int)lua_tointeger(L, lua_upvalueindex(1));
	love::core->insert(love_libs[i].module);
	return 0;
}

int modseacher(lua_State * L)
{
	// Get the module name.
	const char * name = lua_tostring(L, -1);

	// Find the module.
	for(int i = 0; love_libs[i].name != 0; i++)
	{
		if(strcmp(name, love_libs[i].name) == 0)
		{
			lua_pushinteger(L, i);
			lua_pushcclosure(L, modloader, 1);
			return 1;
		}
	}
	lua_pushstring(L, "No such module.");
	return 1;
}

int main(int argc, char ** argv)
{
	love::Core core;
	core.setArg(argc, argv);
	core.addSearcher(modseacher);
	int status = core.init();

	if(status!=0)
	{
		printf("Error: %i\n", status);
		getchar();
	}

	return status;
}