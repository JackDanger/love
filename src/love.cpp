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

#include "Configuration.h"

// Games.
#include "FontTexGame.h"
#include "LuaGame.h"

// STD
#include <stdio.h>
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
		printf("LOVE %s - Now with more Santa-power.\n\n", version_string().c_str());

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
				printf("Game does not exist! (Gamesrc: %s)\n", game_src.c_str());
				return false;
			}

			game = new LuaGame(game_src);

			printf(" * Opening game %s\n", arg_game.c_str());

			// Read config file.
			if(filesystem->exists(game_src, "game.conf"))
			{
				pFile file = filesystem->getFile(game_src, "game.conf");
				conf = new Configuration(file);
				if(!conf->load()) printf("Could not load config file");
			}

		}
		else
		{
			game = new FontTexGame();
			//printf("Usage: love [item]\n - [item] may be an archive file or directory ^.^\n\n");
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

	void error(const char * text, ...)
	{
		bool buffer_overrun;
		int buffer_size = 1024;
		char *ftext;
		va_list	ap;

		va_start(ap, text);
		do
		{
			ftext = new char[buffer_size];
			buffer_overrun = vsnprintf(ftext, buffer_size, text, ap) < 0;
			if (buffer_overrun)
			{
				delete[] ftext;
				buffer_size *= 2;
			}
		} while (buffer_overrun);
		va_end(ap);

		std::string s(ftext);
		delete[] ftext;
		puts(s.substr(0, s.length() - 1).c_str());
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
			return;
		}

		game->keyPressed(key);
	}

	void key_released(int key)
	{
		game->keyReleased(key);
	}

	void mouse_pressed(float x, float y, int button)
	{
		game->mousePressed(x, y, button);
	}

	void mouse_released(float x, float y, int button)
	{
		game->mouseReleased(x, y, button);
	}

}// love


