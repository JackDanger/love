#include "Core.h"

#include "love.h"
#include "love_keys.h"

#include "AbstractDisplay.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
#include "AbstractFileSystem.h"
#include "AbstractAudio.h"
#include "AbstractGraphics.h"
#include "Parameters.h"
#include "Console.h"
#include "ConfigLoader.h"
#include "DefaultConfiguration.h"

#include "AbstractFont.h"

// Include the LoveMenu
#include "LoveMenu4.h"
#include "LuaGame.h"
#include "NeoFontTexGame.h"
#include "FontTexGame.h"


#include <cstdarg>

namespace love 
{


	Core::Core() : display(0), keyboard(0), mouse(0), timer(0), filesystem(0), current(0), uigame(0), verbose(false), runningExternalGame(false)
	{

	}

	Core::~Core()
	{
	}

	const Mouse & Core::getMouse() const
	{
		return (*mouse);
	}

	const AbstractFileSystem & Core::getFilesystem() const
	{
		return (*filesystem);
	}

	const DisplayMode & Core::getDisplayMode() const
	{
		return display->getCurrentDisplayMode();
	}

	const AbstractGraphics & Core::getGraphics() const
	{
		return (*graphics);
	}

	AbstractGUI * Core::getGUI() const
	{
		return gui;
	}

	int Core::init()
	{
		int status = LOVE_OK;

		// Init filesystem

		// Init all devices
		status &= display->init();
		status &= keyboard->init();
		status &= mouse->init();
		status &= timer->init();
		status &= filesystem->init();
		status &= parameters->init();
		status &= audio->init();
		status &= graphics->init();

		if(status != LOVE_OK) 
			error("Could not init LOVE CORE.\n");

		// Post-init 

		// Configure devices in accord with parameters
		filesystem->configure(parameters);
		core->configure(parameters);

		// Do we have a love.conf override?
		pDefaultConfiguration defaultConfig(new DefaultConfiguration());
		config.reset<ConfigLoader>(new ConfigLoader(filesystem->getBase() + "data/love.conf"));
		defaultConfig->defaultSystemConfig(config); // load defaults
		config->load(); // replace defaults with set values

		// Change the display mode
		int w = 800;
		int h = 600;
		int depth = 32;
		bool full = false;
		if(config->isString("default_resolution"))
		{
			string res = config->getString("default_resolution");
			w = atoi(res.substr(0, res.find('x')).c_str());
			h = atoi(res.substr(res.find('x')+1).c_str());
		}
		if(config->isInt("color_depth"))
			depth = config->getInt("color_depth");
		if(config->isBool("fullscreen"))
			full = config->getBool("fullscreen");

		display->tryChange(DisplayMode(w, h, depth, full));
		display->listener = this;

		//addGame("neoftg", new NeoFontTexGame());
		addGame("ftg", new FontTexGame());

		// Adds scripted games from the game directory.
		addGames();

		// Init all games.
		for(games.begin(); !games.end(); games.next())
			games.value()->init();

		// Add menu.
		addGame("love-system-menu", new LoveMenu4(&games));
		games["love-system-menu"]->init();

		if(current == 0)
			startGame("love-system-menu", false);

		// Init the GUI
		gui->init();
		uigame = new UIGame();
		uigame->init();

		// Start param game, if we have that.
		if(parameters->exists("game"))
		{
			// This is where we have an intro screen.
			runningExternalGame = true;
			string source = parameters->get("game");
			startGame(source);
		}

		// After init, there must be at least a current game.
		if(current == 0)
			return LOVE_ERROR;

		// Add a default font
		string temp = filesystem->getBase();
		pAbstractFont defaultFont = graphics->getFont("data/fonts/FreeSans.ttf", 14);
		defaultFont->load();
		graphics->setFont(defaultFont);

		return status;		
	}

	int Core::configure(Parameters * parametes)
	{
		if(parameters->exists("game"))
		{
			string source = parameters->get("game");
			addGame(source, new LuaGame(source));
		}

		return LOVE_OK;
	}

	int Core::addGames()
	{

		string gamesdir = filesystem->getBase() + "data/games";

		gamesdir = config->isString("gamedir") ? config->getString("gamedir") : gamesdir;

		// Check that game dir exists.
		if(!filesystem->exists(gamesdir, ""))
		{
			this->error("Game directory %s does not exist.\n", gamesdir.c_str());
			return LOVE_ERROR;
		}

		// Get a list of all games in directory.
		vector<string> sources = filesystem->getList(gamesdir, "");

		// Check if anything looks like a love game.
		for(int i =0;i<(int)sources.size();i++)
		{
			string s = sources[i];
		
			// Create full source.
			string source = gamesdir + "/" + s;

			// Directory?
			if(filesystem->isDir(gamesdir, s))
			{
				
			}else // Nope ... file.
			{
				// This would mean no room for ".love".
				if(s.length() < 6)
					continue;
				
				// If ignore it if it's not a .love-file.
				if(s.substr(s.length() - 5, s.length() - 1) != ".love")
					continue;
			}

			// At this point, we know that the file or directory is valid, at least.

			// Verify that entry.lua is present.
			if(!filesystem->exists(source, "main.lua"))
				continue;

			// Okay, it's a game.
			addGame(source, new LuaGame(source));

		}

		return LOVE_OK;
	}


	void Core::update(float dt)
	{
		current->update(dt);
		gui->update(dt);
	}

	void Core::render()
	{
		graphics->clear();

		current->render();

		gui->render();

		// @todo KILL.
		glLoadIdentity();
	}

	void Core::quit()
	{
		// Write all configurations
		config->write();
		// Call platform quit.
		platform_quit();
	}

	void Core::addGame(const string & name, Game * game)
	{
		games.create(name, game);
	}

	int Core::startGame(const string & name, bool dmchange)
	{
		// Check if game exists.
		if(!games.contains(name))
		{
			this->printf("Game \"%s\" does not exist.", name.c_str());
			return LOVE_ERROR;
		}

		this->printf("Starting game \"%s\".", name.c_str());

		// Set game as current.
		current = games[name].get();

		// Should display mode be changed?
		if(dmchange && !current->config->getDisplayMode().equals(display->getCurrentDisplayMode()))
		{
			// Change it.
			if(!display->tryResize(current->config->getDisplayMode()))
			{
				core->printf("Could not to change to requested display mode, trying default.\n");

				if(!display->tryChange(DisplayMode()))
				{
					core->printf("Could not to change to default display mode.\n");
					return LOVE_ERROR;
				}
			}

			if(verbose)
				core->printf("Display mode was changed to: %i x %i.\n", display->getCurrentDisplayMode().getWidth(), display->getCurrentDisplayMode().getHeight());

		}

		// Load game
		if(!current->isLoaded())
			current->load();

		// Always resume
		current->resume();

		return LOVE_OK;
	}

	int Core::suspendGame()
	{
		current->suspend();
		return LOVE_OK;
	}

	int Core::stopGame()
	{
		current->stop();
		return LOVE_OK;
	}

	void Core::printf(const char * msg, ...)
	{
		char ftext[1024];
		va_list	ap;

		va_start(ap, msg);
		vsprintf(ftext, msg, ap);
		va_end(ap);

		string s(ftext);
		s = s.substr(0, s.length() - 1);

		puts(s.c_str());
	}

	void Core::keyPressed(int key)
	{

		// Catch global stuff here
		switch(key)
		{
		case LOVE_KEY_ESCAPE:
			if(strcmp(current->getName().c_str(),"love-system-menu") == 0)
			{
				if(!uigame->isPaused())
				{
					uigame->showSettings();
					keyboard->keyPressed(key);
					return;
				}
			}
			break;
		case LOVE_KEY_TAB:
			if(strcmp(current->getName().c_str(),"love-system-menu") != 0 && (keyboard->isDown(LOVE_KEY_LSHIFT) || keyboard->isDown(LOVE_KEY_RSHIFT)))
			{
				if(!uigame->isPaused())
				{
					uigame->showPause();
					keyboard->keyPressed(key);
					return;
				}
			}
			//startGame("love-system-menu", false);
			break;
		case LOVE_KEY_RETURN:
			if(keyboard->isDown(LOVE_KEY_LALT))
			{
				display->toggleFullscreen();
				current->resume();
				if(verbose)
					this->printf("Fullscreen: %i\n", getDisplayMode().isFullscreen());
			}
			break;
		case LOVE_KEY_v:
			if(keyboard->isDown(LOVE_KEY_LCTRL))
			{
				display->toggleVSync();
				current->resume();
				if(verbose)
					this->printf("Vsync: %i\n", getDisplayMode().isVsync());
			}
			break;
		case LOVE_KEY_r:
			if(keyboard->isDown(LOVE_KEY_LCTRL))
			{
				if(!uigame->isPaused() && strcmp(current->getName().c_str(),"love-system-menu") != 0)
				{
					current->reload();
					if(verbose)
						printf("Reloaded: %s\n", current->getName().c_str());
				}
			}
			break;
		}

		// Update keyboard state.
		keyboard->keyPressed(key);

		// Send key input to game.
		current->keyPressed(key);
	}

	void Core::keyReleased(int key)
	{
		// Update keyboard state.
		keyboard->keyReleased(key);

		// Send key input to game.
		current->keyReleased(key);
	}


	void Core::mouseMoved(float x, float y)
	{
		// Update mouse state.
		mouse->mouseMoved(x, y);

		// Send input to game.
		current->mouseMoved(x, y);
	}

	void Core::mousePressed(float x, float y, int button)
	{
		// Update mouse state.
		mouse->mousePressed(x, y, button);

		// Send input to game.
		current->mousePressed(x, y, button);
	}

	void Core::mouseReleased(float x, float y, int button)
	{
		// Update mouse state.
		mouse->mouseReleased(x, y, button);

		// Send input to game.
		current->mouseReleased(x, y, button);
	}

	void Core::displayModeChanged()
	{
		// Tell games about this.
		for(games.begin(); !games.end(); games.next())
			games.value()->displayModeChanged();

		// Tell the GUI
		gui->displayModeChanged();
		uigame->displayModeChanged();

		// Reload persistent items.
		reloadPersistent();
	}

	void Core::eventFired(pEvent e)
	{
		current->eventFired(e);
	}

	void Core::error(const char * text, ...)
	{
		char ftext[1024];
		va_list	ap;

		va_start(ap, text);
		vsprintf(ftext, text, ap);
		va_end(ap);

		string s(ftext);
		s = s.substr(0, s.length() - 1);

		if(uigame != 0 && uigame->isLoaded() && current != 0)
			uigame->showError(s.c_str());
		puts(s.c_str());
	}

	bool Core::isVerbose()
	{
		return verbose;
	}

	void Core::reloadPersistent()
	{
		list<pLoadable>::iterator i = persistents.begin();

		// Reload all children.
		while(i != persistents.end())
		{
			(*i)->reload();			
			i++;
		}
	}

	void Core::addPersistent(pLoadable persistent)
	{
		persistents.push_back(persistent);
	}

	void Core::removePersistent(pLoadable & persistent)
	{
		persistents.remove(persistent);
	}

} // namespace love
