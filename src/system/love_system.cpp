#include "love_system.h"

// Module.
#include "LuaGame.h"

// LOVE
#include <love/Core.h>
#include <love/Game.h>
#include <love/events.h>
#include <love/version.h>
#include <love/arg.h>
#include <love/Configuration.h>
#include <love/Exception.h>

// SDL
#include <SDL.h>

// From SWIG.
extern "C" {
	int luaopen_mod_system(lua_State * L);
}

#define GAME_MAIN "main.lua"
#define GAME_CONF "game.conf"

namespace love_system
{
	love::pGame current_game;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.system [" << "Generic" << "]" << std::endl;

		// Check command line arguments.
		std::string arg_game = love::get_arg_game(argc, argv);
		
		// Arguments might be empty.
		if(arg_game.empty())
		{
			std::cout << "Usage: love [FILE]" << std::endl;
			std::cout << std::endl << "Examples:" << std::endl << "  love demo01.love";
			std::cout << std::endl << "  love /home/nyan/mygame" << std::endl << std::endl;
			return false;
		}

		try
		{
			// Typedefs for filesystem.
			typedef love::pFile * (*fptr_getFile)(const char *);
			typedef bool (*fptr_exists)(const std::string &);
			typedef const char * (*fptr_getBaseDirectory)();
			typedef const char * (*fptr_getLeaf)(const std::string &);
			typedef bool (*fptr_setSaveDirectory)(const std::string &);
			typedef bool (*fptr_addDirectory)(const std::string &);
			typedef bool (*fptr_bool)();

			// Typedefs for graphics.
			typedef bool (*fptr_setMode)(int, int, bool, bool, int);

			// Get function pointers.
			fptr_getFile getFile = (fptr_getFile)core->getf(love::Module::FILESYSTEM, "getFile");
			fptr_exists exists = (fptr_exists)core->getf(love::Module::FILESYSTEM, "exists");
			//fptr_getLeaf getLeaf = (fptr_getLeaf)core->getf(love::Module::FILESYSTEM, "getLeaf");
			fptr_setSaveDirectory setSaveDirectory = (fptr_setSaveDirectory)core->getf(love::Module::FILESYSTEM, "setSaveDirectory");
			fptr_getBaseDirectory getBaseDirectory = (fptr_getBaseDirectory)core->getf(love::Module::FILESYSTEM, "getBaseDirectory");
			fptr_addDirectory addDirectory = (fptr_addDirectory)core->getf(love::Module::FILESYSTEM, "addDirectory");
			fptr_setMode setMode = (fptr_setMode)core->getf(love::Module::GRAPHICS, "setMode");

			// Create the game source.
			std::string base = std::string(getBaseDirectory());
			bool absolute = love::is_arg_absolute(arg_game);
			std::string game_source = absolute ? (arg_game) : (base + "/" + arg_game);
			
			// Add the game source to the search path.
			if(!addDirectory(game_source))
			{
				std::cerr << "Game (" << game_source << ") does not exist." << std::endl;
				return false;
			}

			// Create configuration.
			love::pFile * conf = getFile(GAME_CONF);
			love::Configuration gc(*conf);
			delete conf;

			// Get entry point and create game.
			love::pFile * main = getFile(GAME_MAIN);
			current_game.reset<love::Game>(new LuaGame(*main, core));
			delete main;
			
			// Create default values for the game configuration.
			gc.add("title", "Untitled Game");
			gc.add("author", "Unknown Author");
			gc.add("width", 800);
			gc.add("height", 600);
			gc.add("vsync", true);
			gc.add("fsaa", 0);
			gc.add("fullscreen", false);
			gc.add("love_version", LOVE_VERSION_STR);
			gc.add("display_auto", true);

			// Now load the config file, causing default values
			// to be overwritten.
			if(exists(GAME_CONF) && !gc.load())
			{
				std::cerr << "Could not load configuration." << std::endl;
				return false;
			}

			// Set the display mode, unless the user want to do
			// that in Lua.
			if(gc.getBool("display_auto"))
			{
				// Try config.
				if(!setMode(gc.getInt("width"), gc.getInt("height"), gc.getBool("fullscreen"), gc.getBool("vsync"), gc.getInt("fsaa")))
				{
					// Try failsafe.
					if(!setMode(800, 600, false, true, 0))
					{
						std::cerr << "Could not set display mode." << std::endl;
						return false;
					}
				}
			}
			
		}
		catch(love::Exception exc)
		{
			std::cerr << exc.msg() << std::endl;
			return false;
		}

		// Current game should be set at this point.
		if(current_game != 0 && !current_game->load())
		{
			std::cerr << "Game could not be loaded." << std::endl;
			return false;
		}

		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.system [" << "Generic" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_system(s);
		return true;
	}

	void error(const char * msg)
	{
		std::cerr << msg << std::endl;
	}

	void warning(const char * msg)
	{
		std::cerr << msg << std::endl;
	}

	const love::pGame & getGame()
	{
		return current_game;
	}

	const char * getVersion()
	{
		return LOVE_VERSION_STR;
	}

	const char * getCodename()
	{
		return LOVE_VERSION_CODENAME;
	}

	const char * getPlatform()
	{
#ifdef WIN32
		return "Windows";
#else
		return "Linux";
#endif
	}

	void exit()
	{
		SDL_Event e;
		e.type = SDL_QUIT;

		if( SDL_PushEvent(&e) != 0 )
			error("Could not exit.");
	}

	void compile_error(lua_State * L, int status)
	{
		if(status == 0)
			return; // No errors.

		// This is the human readable error message.
		const char * msg = lua_tostring(L, -1);
		
		switch (status)
		{
		case LUA_ERRMEM:
			std::cerr << "Memory allocation error: " << msg << std::endl;
			break;
		case LUA_ERRSYNTAX:
			std::cerr << "Syntax error: " << msg << std::endl;
			break;
		}

		// Remove error message.
		lua_pop(L, 1);
	}

	int runtime_error(lua_State * L)
	{
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		if (!lua_istable(L, -1)) {
			lua_pop(L, 1);
			return 1;
		}
		lua_getfield(L, -1, "traceback");
		if (!lua_isfunction(L, -1)) {
			lua_pop(L, 2);
			return 1;
		}
		lua_pushvalue(L, 1);  /* pass error message */
		lua_pushinteger(L, 2);  /* skip this function and traceback */
		lua_call(L, 2, 1);  /* call debug.traceback */

		// Extract message.
		if(lua_isstring(L, -1))
		{
			// msg now holds the complete error message (with stack trace).
			const char * msg = lua_tostring(L, -1);
			std::cerr << "Run-time error: " << msg << std::endl;
		}

		return 1;
	}

} // love_system
