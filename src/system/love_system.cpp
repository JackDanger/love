#include "love_system.h"
#include "mod_system.h"

#include <math.h>

// Module.
#include "LuaGame.h"
#include "resources.h"

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

#define GAME_MAIN "main.lua"
#define GAME_ERROR "error.lua"
#define GAME_CONF "game.conf"

namespace love_system
{
	// The game pointed to by this object will be
	// used in the main update and draw loop.
	love::pGame current_game;

	// This is the main game. If there are no
	// errors, this will be the current game.
	love::pGame main_game;

	// If an error occurs, this game will be called.
	love::pGame error_game;

	// Required modules.
	love::Filesystem * filesystem = 0;
	love::Graphics * graphics = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		//std::cout << "argv[0] = " << argv[0] << std::endl;
		std::cout << "INIT love.system [" << "Generic" << "]" << std::endl;

		// Get used modules.
		filesystem = core->getFilesystem();
		graphics = core->getGraphics();

		// Verify all.
		if(!filesystem->verify())
		{
			std::cerr << "Required module filesystem not loaded." << std::endl;
			return false;
		}
		if(!graphics->verify())
		{
			std::cerr << "Required module graphics not loaded." << std::endl;
			return false;
		}

		// Set function pointers and load module.
		{
			love::System * s = core->getSystem();
			s->getGame = love_system::getGame;
			s->error = love_system::syserr;
			s->loaded = true;
		}

		bool compatible = true;

		// Check command line arguments.
		std::string arg_game = love::get_arg_game(argc, argv);
		bool nogame = arg_game.empty();
		
		// Arguments might be empty.
		if(nogame)
		{
			std::cout << "Usage: love [FILE]" << std::endl;
			std::cout << std::endl << "Examples:" << std::endl << "  love demo01.love";
			std::cout << std::endl << "  love /home/nyan/mygame" << std::endl << std::endl;
		}

		// If no arguments, just load the no-game.
		if(nogame)
		{
			main_game.reset<love::Game>(new LuaGame(love::nogame_lua, core));
			if(!main_game->load())
			{
				std::cout << "Could not load the no-game." << std::endl;
				return false;
			}
			current_game = main_game;
			return true;
		}

		// Create the game source.
		std::string base = std::string(filesystem->getBaseDirectory());
		bool absolute = love::is_arg_absolute(arg_game);
		std::string game_source = absolute ? (arg_game) : (base + "/" + arg_game);

		// Setup the save directory.
		if(!filesystem->setSaveDirectory(game_source))
		{
			std::cerr << "Could not set save directory!" << std::endl;
			return false;
		}

		// Add the game source to the search path.
		if(!filesystem->addDirectory(game_source))
		{
			std::cerr << "Game (" << game_source << ") does not exist." << std::endl;
			return false;
		}

		// Create configuration.
		love::pFile * conf = filesystem->getFile(GAME_CONF);
		love::Configuration gc(*conf);
		delete conf;

		// Get entry point and create game.
		love::pFile * main = filesystem->getFile(GAME_MAIN);
		main_game.reset<love::Game>(new LuaGame(*main, core));
		delete main;

		// Also create error game, but load nothing yet.
		if(filesystem->exists(std::string(GAME_ERROR)))
		{
			love::pFile * error_main = filesystem->getFile(GAME_ERROR);
			error_game.reset<love::Game>(new LuaGame(*error_main, core));
			delete error_main;
		}
		else
			error_game.reset<love::Game>(new LuaGame(love::error_lua, core));

		// The main game is the current game for now.
		current_game = main_game;
		
		// Create default values for the game configuration.
		gc.add("title", "Untitled Game");
		gc.add("author", "Unknown Author");
		gc.add("width", 800);
		gc.add("height", 600);
		gc.add("vsync", true);
		gc.add("fsaa", 0);
		gc.add("fullscreen", false);
		gc.add("love_version", std::string(LOVE_VERSION_STR));
		gc.add("display_auto", true);

		// Now load the config file, causing default values
		// to be overwritten.
		if(filesystem->exists(GAME_CONF) && !gc.load())
		{
			std::cerr << "Could not load configuration." << std::endl;
			return false;
		}

		// Set the window title.
		graphics->setCaption(gc.getString("title").c_str());

		// Check if this game is made for a compatible
		// version of LOVE.
		std::string love_version = gc.getString("love_version");
		compatible = love::is_compatible(love_version.c_str());	

		// Set the display mode, unless the user wants to do
		// that in Lua. 
		// Note! In case the game isn't compatible, we must use
		// config settings. (Main game isn't loaded)
		if(gc.getBool("display_auto") || !compatible)
		{
			// Try config.
			if(!graphics->setMode(gc.getInt("width"), gc.getInt("height"), gc.getBool("fullscreen"), gc.getBool("vsync"), gc.getInt("fsaa")))
			{
				// Try failsafe.
				if(!graphics->setMode(800, 600, false, true, 0))
				{
					std::cerr << "Could not set display mode." << std::endl;
					return false;
				}
			}
		}
		
		// If the game isn't compatible, change to error game.
		if(!compatible)
		{
			std::stringstream err;
			err << "This game is made for another version of LOVE! The current "
				<< "version is " << LOVE_VERSION_STR << " (game was made for " << love_version << ").";
			suspend();
			message(err.str().c_str(), love::TAG_INCOMPATIBLE);
		}

		// Current game should be set at this point.
		if(!current_game->isLoaded())
		{
			if(compatible && current_game != 0 && !current_game->load())
			{
				std::cerr << "Game could not be loaded." << std::endl;
				return false;
			}
		}

		return true;
	}

	bool module_quit()
	{

		// Clean global data.
		main_game.reset();
		error_game.reset();
		current_game.reset();

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

	void syserr(const char * msg)
	{
		if(current_game == error_game)
			return;

		std::cerr << msg << std::endl;
		suspend();
		message(msg, love::TAG_ERROR);
	}

	void syswarn(const char * msg)
	{
		if(current_game == error_game)
			return;

		std::cerr << msg << std::endl;
		suspend();
		message(msg, love::TAG_WARNING);
	}

	void message(const char * msg, int tag)
	{
		if(error_game == 0 || !error_game->isLoaded())
			return;

		// Notify error game that state must be stored.
		pLuaGame e = boost::dynamic_pointer_cast<LuaGame, love::Game>(error_game);
		if(e != 0)
		{
			e->message(msg, tag);
		}
	}

	int include(lua_State * L)
	{
		int n = lua_gettop(L);

		if( n != 1 )
			return luaL_error(L, "Function requires a single parameter.");

		int type = lua_type(L, 1);

		if(type != LUA_TSTRING)
			return luaL_error(L, "Function requires parameter of type string.");
		
		const char * filename = lua_tostring(L, 1);

		// Get the file.
		love::pFile * file = filesystem->getFile(filename);

		if(!(*file)->load())
		{
			delete file;
			std::stringstream ss;
			ss << "Could not include file \"" << filename << "\".";
			return luaL_error(L, ss.str().c_str());
		}

		int status = luaL_loadbuffer (L, (const char *)(*file)->getData(), 
			(*file)->getSize(), (*file)->getFilename().c_str());

		delete file;

		if(status != 0)
		{
			compile_error(L, status);
			return 0;
		}

		// Stealing this from LuaGame.
		int narg = 0, nres = 0;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);

		return 0;
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
			syserr("Could not exit.");
	}

	void suspend()
	{
		// Error game must be set.
		if(error_game == 0)
		{
			std::cout << "Error game is not set! Quitting ..." << std::endl;
			exit();
			return;
		}

		// If the game is suspended, and there is no screen: create one.
		if(!graphics->isCreated())
			if(!graphics->setMode(800, 600, false, true, 0))
				std::cerr << "Could not set display mode." << std::endl;

		// Load the error game if suspended for the first time.
		if(!error_game->isLoaded())
		{
			if(!error_game->load())
			{
				std::cout << "Error while loading error game! The irony!" << std::endl;
				return;
			}
		}

		// Notify error game that state must be stored.
		message("savestate", love::TAG_COMMAND);

		current_game = error_game;
	}

	void resume()
	{
		// Main game must be set.
		if(main_game == 0)
		{
			std::cout << "Main game is not set!" << std::endl;
			return;
		}

		if(!main_game->isLoaded())
		{
			if(!main_game->load())
			{
				std::cout << "Could not load main game!" << std::endl;
				return;
			}
		}

		current_game = main_game;
	}

	void restart()
	{
		SDL_Event e;
		e.type = love::EVENT_RESTART;

		// Push the SDL event.
		if( SDL_PushEvent(&e) != 0 )
			syserr("Could not restart game.");

		// Reset the graphics device.
		graphics->reset();
	}

	void grabInput(bool grab)
	{
		if(grab)
			SDL_WM_GrabInput(SDL_GRAB_ON);
		else
			SDL_WM_GrabInput(SDL_GRAB_OFF);
	}

	void compile_error(lua_State * L, int status)
	{
		if(status == 0)
			return; // No errors.

		// This is the human readable error message.
		const char * msg = lua_tostring(L, -1);

		std::stringstream ss;
		
		switch (status)
		{
		case LUA_ERRMEM:
			ss << "Memory allocation error: " << msg << std::endl;
			syserr(ss.str().c_str());
			break;
		case LUA_ERRSYNTAX:
			ss << "Syntax error: " << msg << std::endl;
			syserr(ss.str().c_str());
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
			std::stringstream ss;
			ss << "Run-time error: " << msg << std::endl;
			syserr(ss.str().c_str());
		}

		return 1;
	}

} // love_system
