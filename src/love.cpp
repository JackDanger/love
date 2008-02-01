#include "love.h"


// LOVE
#include "platform.h"
#include "love_keys.h"
#include "love_arg.h"
#include "love_version.h"
#include "Game.h"

#include "Display.h"
#include "Graphics.h"
#include "Audio.h"
#include "Timer.h"
#include "Filesystem.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Widget.h"

#include "Configuration.h"

// Games.
#include "FontTexGame.h"
#include "NoGame.h"
#include "LuaGame.h"

// STD
#include <iostream>
#include <cstdarg>


namespace love
{
		
	// The current game.
	Game * game = 0;

	// Global devices.
	Display * display;
	Graphics * graphics;
	Audio * audio;
	Timer * timer;
	Filesystem * filesystem;
	Mouse * mouse;
	Keyboard * keyboard;

	bool init(int argc, char* argv[])
	{
		printf("LOVE %s - Now with More Mini-Moose (tm).\n\n", version_string().c_str());

		if(!display->init(argc, argv))
			return false;

		if(!graphics->init(argc, argv))
			return false;

		if(!audio->init(argc, argv))
			return false;

		if(!timer->init(argc, argv))
			return false;

		if(!filesystem->init(argc, argv))
			return false;

		if(!mouse->init(argc, argv))
			return false;

		if(!keyboard->init(argc, argv))
			return false;

		/*****************************************
		* Test area begins here.
		*****************************************/

		// Print full path.
		//printf(" * Full path is: %s\n", filesystem->getBase().c_str());

		// Check arguments.
		std::string arg_base = get_arg(argc, argv, "-b");
		std::string arg_game = get_arg_game(argc, argv);

		Configuration * conf = 0;

		// Figure out which game to run.
		if(!arg_game.empty())
		{
			// Is game path absolute?
			bool absolute = is_arg_absolute(arg_game);

			std::string game_src = absolute ? arg_game : filesystem->getBase() + arg_game;

			if(!filesystem->exists(game_src))
			{
				std::cerr << "Game does not exist! (Gamesrc: " << game_src << ")" << std::endl;
				return false;
			}

			game = new LuaGame(game_src);

			std::cout << " * Opening game " << arg_game << std::endl;

			// Read config file.
			if(filesystem->exists(game_src, "game.conf"))
			{
				pFile file = filesystem->newFile(game_src, "game.conf");
				conf = new Configuration(file);
				if(!conf->load())
				{
					std::cerr << "Could not load config file." << std::endl;
					return false;
				}
			}

		}
		else
		{
			game = new NoGame();
			//game = new FontTexGame();
			printf("Usage: love [FILE]\n");
			printf("\nExamples:\n  love demo01.love\n  love /home/nyan/mygame\n\n");
			//return false;
		
		}
		// Setup display.
		if(conf != 0)
		{
			int width = conf->getInt("width");
			int height = conf->getInt("height");
			bool fs = conf->getBool("fullscreen");

			if(width <= 0) width = 800;
			if(height <= 0) height = 600;

			printf(" * %s (%ix%i-%s)\n", conf->getString("title").c_str(), width, height, fs ? "fullscreen" : "windowed");
			display->tryChange(width, height, 32, fs);

			delete conf;

		}else display->tryChange(800, 600);


		// If game is still 0, then something's wrong.
		if(game == 0)
		{
			printf("No game.\n");
			return false;
		}

		if(!game->load())
		{
			printf("Game did not load properly.\n");
			return false;
		}

		return true;
	}

	void free()
	{
		// Anything init allocates should die here.
		delete game;
	}

	void quit()
	{
		platform_quit();
	}

	void error(const std::string & str)
	{
		printf("Error: %s\n", str.c_str());

		// Error should not cause quit, but as long as we have
		// no GUI, it's better than let the code keep running
		// after an error.
		quit();
	}

	void warning(const std::string & str)
	{
		printf("Warning: %s\n", str.c_str());
	}

	void info(const std::string & str)
	{
		printf(str.c_str());
	}

	void update(float dt)
	{
		game->update(dt);
	}

	void render()
	{
		// Clear screen.
		graphics->clear();

		// Render current game.
		game->render();
	}

	void key_pressed(int key)
	{
		if(key == LOVE_KEY_ESCAPE)
		{
			quit();
			return;
		}

		// Reload the game.
		if(keyboard->isDown(LOVE_KEY_LCTRL) && key == LOVE_KEY_r)
		{
			game->reload();
			printf("Reloaded.\n");
			return;
		}

		game->keyPressed(key);
		Widget::distributeKeyPressed(key);
	}

	void key_released(int key)
	{
		game->keyReleased(key);
		Widget::distributeKeyReleased(key);
	}

	void mouse_pressed(float x, float y, int button)
	{
		game->mousePressed(x, y, button);
		Widget::distributeMousePressed(x, y, button);
	}

	void mouse_released(float x, float y, int button)
	{
		game->mouseReleased(x, y, button);
		Widget::distributeMouseReleased(x, y, button);
	}

	void mouse_moved(float x, float y)
	{
		Widget::distributeMouseMoved(x, y);
	}

}// love


