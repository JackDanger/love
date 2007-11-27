/**
* @file Core.h
* @brief Contains definition of class Core.
* @date 2006-03-06
* @author Anders Ruud
*
* Core is the class which controls the games, inits devices, 
* and so on.
**/

#ifndef LOVE_CORE_H
#define LOVE_CORE_H

// Interfaces
#include "AbstractDevice.h"
#include "MouseListener.h"
#include "MouseMotionListener.h"
#include "KeyListener.h"
#include "Updateable.h"
#include "Renderable.h"
#include "DisplayModeListener.h"
#include "AbstractGraphics.h"
#include "OpenGLGUI.h"

#include "AbstractImage.h"
#include "AbstractFont.h"
#include "AbstractSound.h"
#include "AbstractMusic.h"
#include "AbstractFile.h"
#include "Loadable.h"

// Other LOVE files
#include "ConfigLoader.h"
#include "Game.h"
#include "UIGame.h"

// We want to be friends with some platform functions. (later)
#include "platform.h"
#include "lualove.h" // and some lualove functions.

// Dirty, horrible, etc.
//#include <guichan.hpp>
//#include <guichan/opengl.hpp>
//#include <guichan/sdl.hpp>
extern gcn::SDLInput * gcn_input;

/**
* @namespace love
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains the love library.
**/
namespace love 
{

	// Forward declarations (devices)
	class AbstractDisplay;
	class Keyboard;
	class Mouse;
	class Timer;
	class AbstractFileSystem;
	class AbstractSoundDevice;
	class AbstractImageDevice;
	class AbstractGraphics;
	class Console;
	class DisplayMode;


	// Other
	class Parameters;
	class LuaGame;

	/**
	* @class Core
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief The main class.
	*
	**/
	class Core :	public AbstractDevice, public Updateable, public Renderable,
					public MouseListener, public MouseMotionListener, public KeyListener, 
					public DisplayModeListener, public EventListener
	{

	private:

		// The "devices". 
		AbstractDisplay * display;
		Keyboard * keyboard;
		Mouse * mouse;
		Timer * timer;
		AbstractFileSystem * filesystem;
		AbstractSoundDevice * audio;
		AbstractImageDevice * imaging;
		AbstractGraphics * graphics;
		Parameters * parameters;
		AbstractGUI * gui;

		pConfigLoader config;


		// Console used for useful output
		Console * console;

		//Contains all the Games.
		Container<Game> games;

		// The current game 
		Game * current;

		// GUI
		UIGame * uigame;

		// How many messages there should be
		bool verbose;

		list<pLoadable> persistents;


	public:

		/**
		* We want to be friends with platform code, so that it can configure core devices.
		**/
		friend int platform_init(int argc, char * argv[]);
		friend int platform_loop();
		friend void lualove_bind_globals();
		friend void lualove_gui_error(const char * message);

		// We also want to be friends with some classes
		friend class LuaGame;
		friend class LoveMenu4;
		//friend class NeoFontTexGame;
		friend class Console;
		friend class ObjectFactory;
		//friend class OpenGLGUI;
		friend class UIGame;

		/**
		* @brief Creates a new Core object. Remeber to always call init(). 
		**/
		Core();

		/**
		* @brief Gets a reference to the mouse device.
		* @return A reference to the mouse device.
		**/
		const Mouse & getMouse() const;

		/**
		* @brief Gets a constant reference to the current file system.
		* @return A reference to the file system.
		**/
		const AbstractFileSystem & getFilesystem() const;

		/**
		* @brief Gets a constant reference to the current image system
		* @return A reference to the image system.
		**/
		const AbstractImageDevice & getImaging() const;

		/**
		* @brief Gets the current display mode.
		* @return The current display mode.
		**/
		const DisplayMode & getDisplayMode() const;

		/**
		* @brief Gets the current graphics device.
		* @return The current graphics device.
		**/
		const AbstractGraphics & getGraphics() const;

		/**
		* @brief Gets the current GUI system.
		* @return The current GUI system.
		**/
		AbstractGUI * getGUI() const;

		/**
		* @brief Destructor.
		**/
		virtual ~Core();

		pAbstractFile getFile(const string & filename);
		pAbstractImage getImage(const string & filename, int flags = 0);
		pAbstractFont getFont(const string & filename, int size,  int flags = 0);
		pAbstractFont getImageFont(const string & filename, const string & glyphs, int flags = 0);
		pAbstractSound getSound(const string & filename);
		pAbstractMusic getMusic(const string & filename);

		/**
		* @brief Intializes the Core.
		* Also inits all assigned devices.
		**/ 
		int init();

		/**
		* @brief Checks for games added via program params. 
		* @param parametes The program parameters.
		* @return LOVE_OK if no errors.
		**/
		int configure(Parameters * parametes);

		/**
		* @brief Updates the Core once.
		*
		* This must be called every frame. The core
		* calculates changes based on the time since last
		* frame, so as the dt gets smaller, the fps increases.
		**/
		void update(float dt);

		/**
		* @brief Renders the core once.
		*
		* You don't have to call this every frame, 
		* since no actual changes happen here, 
		* only rendering. (Meaning that the game does 
		* not lose it's precision due to lack of render-calls.)
		**/
		void render();

		/**
		* @brief Stops the engine.
		**/
		void quit();

		/**
		* @brief Adds a game to the core.
		* @param name The name of the game. (Used for storage in map, debugging, 
		* and identifying the game in general).
		* @param game A pointer to the new game.
		**/
		void addGame(const string & name, Game * game);

		/**
		* @brief Starts or resumes a game.
		* @param name The name of the game to start.
		* @param dmchange Whether the method should check for display mode changes or not.
		* @return LOVE_OK if no errors. 
		**/
		int startGame(const string & name, bool dmchange = true);

		/**
		* @brief Suspends the current game, and resumes the main menu.
		* @return LOVE_OK if no errors.
		**/
		int suspendGame();

		/**
		* @brief Stops the current game. (Unloads, does not delete)
		* @return LOVE_OK if no errors. 
		**/
		int stopGame();

		/**
		* @brief Prints a message to the internal LOVE console, and to stdout.
		* @param msg The formatted message to print.
		* @param ... A list of parameters.
		**/
		void printf(const char * msg, ...);

		/**
		* @brief Called when a key is pressed.
		* @param key The key that was pressed.
		**/
		void keyPressed(int key);

		/**
		* @brief Called when a key is released.
		* @param key The key that was released.
		**/
		void keyReleased(int key);

		/**
		* @brief Called when the mouse is moved.
		* @param x The x-coordinate of the current mouse position.
		* @param y The y-coordinate of the current mouse position.
		**/
		void mouseMoved(float x, float y);

		/**
		* @brief Called when a mouse button is pressed.
		* @param x The x-coordinate of the mouse.
		* @param y The x-coordinate of the mouse.
		* @param button The involved mouse button. (LOVE_MOUSE_LEFT, etc)
		**/
		void mousePressed(float x, float y, int button);

		/**
		* @brief Called when a mouse button is released.
		* @param x The x-coordinate of the mouse.
		* @param y The x-coordinate of the mouse.
		* @param button The involved mouse button. (LOVE_MOUSE_LEFT, etc)
		**/
		void mouseReleased(float x, float y, int button);

		/**
		* @brief Called when the display mode changes.
		**/
		void displayModeChanged();

		/**
		* @brief This is called every time an Event is fired.
		* @param e The Event that was just fired.
		**/
		void eventFired(pEvent e);

		/**
		* @brief Sends an error to the system.
		* @param text The error text.
		**/
		void error(const char * text, ...);

		/**
		* @brief Checks whether the system is verbose.
		* @return true if the system is verbose (anti-Rorschach).
		**/
		bool isVerbose();

		void reloadPersistent();
		void addPersistent(pLoadable persistent);
		void removePersistent(pLoadable & persistent);

	private:

		/**
		* @brief Adds games from the current game directory.
		* @return LOVE_OK if no errors.
		**/
		int addGames();

	};

	}// love

#endif
