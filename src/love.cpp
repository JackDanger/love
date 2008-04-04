#include "love.h"

#include "modfs.h"

#include <iostream>

// Modules.
#include "Filesystem.h"
#include "Graphics.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Audio.h"
#include "Physics.h"


#include "Exception.h"
#include "Configuration.h"
#include "love_arg.h"
#include "constants.h"

// Games.
#include "LuaGame.h"
#include "NoGame.h"
#include "SuspendGame.h"

#include <SDL.h>

namespace love
{

	// The stack of games.
	// (Not used currently).
	std::vector<pGame> games;

	// A pointer to the current game.
	pGame game;

	// List of modules.
	std::vector<Module *> modules;

	// Modules.
	Filesystem filesystem;
	Graphics graphics;
	Timer timer;
	Keyboard keyboard;
	Mouse mouse;
	Audio audio;
	Physics physics;

	// Module configuration.
	love_mod::modconf modconf;
	
	/**
	* Pushes a Game onto the game stack.
	* @param g The new game to become the current game.
	**/
	void push(pGame g);

	bool init(int argc, char* argv[])
	{
		// Init SDL.
		if(SDL_Init(0))
		{
			std::cerr << "Could not init SDL. " << SDL_GetError() << std::endl;
			return false;
		}

		printf("This is LOVE " LOVE_VERSION_FULL_STR ".\n\n");

		std::string arg_game = get_arg_game(argc, argv);
		if(arg_game.empty())
			game.reset<Game>(new NoGame());
		else
			game.reset<Game>(new LuaGame());

		push(game);

		// Create module config.
		modconf.argc = argc;
		modconf.argv = argv;
		modconf.error = error;
		modconf.print = print;
		modconf.filesystem = &filesystem;

		// Init modules.
		filesystem.init(LOVE_MOD_FILESYSTEM, &modconf); // Should be first.
		graphics.init(LOVE_MOD_GRAPHICS, &modconf);
		physics.init(LOVE_MOD_PHYSICS, &modconf);
		timer.init(LOVE_MOD_TIMER, &modconf);
		keyboard.init(LOVE_MOD_KEYBOARD, &modconf);
		mouse.init(LOVE_MOD_MOUSE, &modconf);
		audio.init(LOVE_MOD_AUDIO, &modconf);

		// Push filesystem state.
		filesystem.push();

		// Shove all modules into game.
		game->require(filesystem);
		game->require(graphics);
		game->require(timer);
		game->require(keyboard);
		game->require(mouse);
		game->require(audio);
		game->require(physics);

		// Give game access to the filesystem.
		game->setFilesystem(&filesystem);

		Configuration * conf = 0;

		// Figure out which game to run.
		if(!arg_game.empty())
		{
			// Is game path absolute?
			bool absolute = is_arg_absolute(arg_game);
			std::string base;
			filesystem.getBaseDir(base);

			std::string game_src = absolute ? arg_game : base + arg_game;

			if(!filesystem.addDir(game_src))
			{
				std::cerr << "Game does not exist! (Gamesrc: " << game_src << ")" << std::endl;
				return false;
			}

			std::cout << " * Opening game " << arg_game << std::endl;

			// Read config file.
			if(filesystem.exists("game.conf"))
			{
				pFile file(new File("game.conf"));
				filesystem.load(file);
				conf = new Configuration(file);
				if(!conf->load())
				{
					std::cerr << "Could not load config file." << std::endl;
					return false;
				}
			}

			/**
			* Setup save directory.
			**/

			// Get filename.
			std::string leaf;
			filesystem.getLeaf(game_src, leaf);

			// Set the write directory.
			if(!filesystem.setSaveDirectory(leaf))
			{
				std::cerr << "Could not set save directory." << std::endl;
			}

		}
		else
		{
			std::cout << "Usage: love [FILE]" << std::endl;
			std::cout << std::endl << "Examples:" << std::endl << "  love demo01.love";
			std::cout << std::endl << "  love /home/nyan/mygame" << std::endl << std::endl;
		}

		bool compatible = true;

		if(conf != 0)
		{

			// Is this game compatible?
			std::string version = conf->isString("love_version") ? conf->getString("love_version") : "any";
			compatible = is_compatible(version.c_str());

			/**
			* Not yet.
			if(!compatible)
			{
				std::stringstream ss;
				ss << "Warning: the game \"" << conf->getString("title") <<"\" was not made for this version of LOVE. ";
				ss << "(This is " << LOVE_VERSION_STR << ". Game requires " << version << ")." << std::endl;
				graphics.print("[box]");
				graphics.print(ss.str().c_str());
				graphics.print("[/box]");
				game->setConsoleVisible(true);
			}
			**/

			int width = conf->getInt("width");
			int height = conf->getInt("height");
			bool fs = conf->getBool("fullscreen");

			if(width <= 0) width = 800;
			if(height <= 0) height = 600;

			printf(" * %s (%ix%i-%s)\n", conf->getString("title").c_str(), width, height, fs ? "fullscreen" : "windowed");
			display_mode dm;
			dm.color_depth = 32;
			dm.width = width;
			dm.height = height;
			dm.fullscreen = fs;
			dm.vsync = true;
			dm.fsaa = 0;
			graphics.try_change(dm);

			// Set Display title.
			std::string title = conf->getString("title");
			SDL_WM_SetCaption(title.c_str(), 0);

			delete conf;

		} 
		else
		{
			display_mode dm;
			dm.color_depth = 32;
			dm.width = 800;
			dm.height = 600;
			dm.fullscreen = false;
			dm.vsync = true;
			dm.fsaa = 0;
			graphics.try_change(dm);
		}

		game->load();

		return true;
	}

	bool quit()
	{

		// Pop the filesystem state.
		filesystem.pop();

		// Quit modules.
		physics.quit();
		audio.quit();
		mouse.quit();
		keyboard.quit();
		timer.quit();
		graphics.quit();
		filesystem.quit();

		// Remove all modules.
		Module::detach_all();

		return true;
	}

	void print(const char * str)
	{
		// Print to stdout.
		std::cout << str << std::endl;

		// Print graphically.
		if(graphics.print != 0)
			graphics.print(str);
	}

	void string_tokenize(const std::string& str,
						std::vector<std::string>& tokens,
						  const std::string& delimiters = " ")
	{
		// Skip delimiters at beginning.
		std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

		while (std::string::npos != pos || std::string::npos != lastPos)
		{
			// Found a token, add it to the vector.
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = str.find_first_not_of(delimiters, pos);
			// Find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

	void error(const char * str)
	{
		std::cerr << "Error was called: " << str << std::endl;

		// Print graphically.
		if(graphics.print != 0)
		{
			pGame suspend_game(new SuspendGame());
			if(suspend_game->load())
				push(suspend_game);
			else
				std::cerr << "Could not suspend game." << std::endl;
			
			graphics.print("[box]");

			std::string s(str);

			s = "Error: " + s;

			// Tokenize.
			std::vector<std::string> tokens;
			string_tokenize(s, tokens, "\n");

			// Print each line individually.
			for(int i = 0;i<(int)tokens.size(); i++)
				graphics.print(tokens[i].c_str());

			graphics.print("[/box]");
			graphics.print("Press C to continue, or press R to restart.");
		}
	}

	void push(pGame g)
	{
		games.push_back(g);
		game = games.back();
	}

	void pop()
	{
		if(games.size() < 2)
			return;
		games.pop_back();
		game = games.back();
	}

	void restart()
	{
		game->reload();
	}

	int loop()
	{

		// Enable UNICODE. This is needed for input to work properly.
		// And yes, this only worked here.
		SDL_EnableUNICODE(1);

		// The union used to get SDL events. 
		SDL_Event e;

		while(1)
		{

			timer.step();

			game->update(timer.getDelta());

			graphics.clear();
			game->draw();

			if(game->isConsoleVisible())
				graphics.draw_console();

			while(SDL_PollEvent(&e))
			{

				// Do events.
				switch(e.type)
				{
					case SDL_KEYDOWN:
						
						game->keyPressed(e.key.keysym.sym);

						if(keyboard.isDown(KEY_LCTRL) && static_cast<int>(e.key.keysym.sym) == static_cast<int>(KEY_c))
						{
							print("Continuing.");
							pop();
						}						

						if(keyboard.isDown(KEY_LCTRL) && static_cast<int>(e.key.keysym.sym) == static_cast<int>(KEY_r))
						{
							print("Restarting.");
							game->reload();
						}

						if(keyboard.isDown(KEY_LALT) && static_cast<int>(e.key.keysym.sym) == static_cast<int>(KEY_RETURN))
						{
							if(!graphics.toggleFullscreen())
							{
								printf("Could not toggle fullscreen.");
							}
						}

						if(keyboard.isDown(KEY_LALT) && static_cast<int>(e.key.keysym.sym) == static_cast<int>(KEY_F4))
						{
							quit();
							return 0;
						}

						if(keyboard.isDown(KEY_LSHIFT) && static_cast<int>(e.key.keysym.sym) == static_cast<int>(KEY_TAB))
						{
							game->setConsoleVisible(!game->isConsoleVisible());
						}

						break;
					case SDL_KEYUP:
						game->keyReleased(e.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						game->mousePressed(e.button.x, e.button.y, e.button.button);
						break;
					case SDL_MOUSEBUTTONUP:
						game->mouseReleased(e.button.x, e.button.y, e.button.button);
						break;
					case SDL_MOUSEMOTION:
						game->mouseMoved(e.button.x, e.button.y);
						break;
					case SDL_QUIT:
						quit();
						return 0;
					default:
						break;
				}
			}

			graphics.present();
		}
	}
}
