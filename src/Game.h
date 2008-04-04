/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2006-03-10
*/

#ifndef LOVE_GAME_H
#define LOVE_GAME_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	// Forward declarations.
	class Module;
	class Filesystem;

	/**
	* Abstract Game class.
	**/
	class Game
	{
		friend bool init(int argc, char* argv[]);
	protected:

		// Pointer to Filesystem functions.
		Filesystem * filesystem;

		// True if console is visible.
		bool consoleVisible;

	public:

		/**
		* Creates a new game.
		**/
		Game();

		virtual ~Game();
		
		/**
		* Sets the Filesystem pointer.
		**/
		void setFilesystem(Filesystem * fs);

		/**
		* If this message returns true, the console will be displayed.
		**/
		virtual bool isConsoleVisible() const;

		/**
		* Changes console visibilty.
		**/
		void setConsoleVisible(bool visible);

		/**
		* Adds a Module to the list of required libraries.
		* (Will be reloaded automatically on reloads).
		**/
		virtual bool require(Module & m) = 0;

		/**
		* Loads the game.
		**/
		virtual bool load() = 0;

		/**
		* Unloads the game.
		**/
		virtual bool unload() = 0;

		/**
		* Calls unload, then load. Returns result from load.
		**/
		bool reload();

		/**
		* Called each time the Game should be updated.
		* @param dt The time since last frame.
		**/
		virtual void update(float dt) = 0;

		/**
		* Called each time the Game should be rendered.
		**/
		virtual void draw() = 0;

		/**
		* Called when a key is pressed.
		* @param key The ASCII key code.
		**/
		virtual void keyPressed(int key) = 0;

		/**
		* Called when a key is released.
		* @param key The ASCII key code.
		**/
		virtual void keyReleased(int key) = 0;

		/**
		* Called when the mouse is pressed.
		* @param x The x-coordinate of the mousepress.
		* @param y The y-coordinate of the mousepress.
		* @param button The button that was pressed.
		**/
		virtual void mousePressed(int x, int y, int button) = 0;

		/**
		* Called when the mouse is released.
		* @param x The x-coordinate of the mouserelease.
		* @param y The y-coordinate of the mouserelease.
		* @param button The button that was released.
		**/
		virtual void mouseReleased(int x, int y, int button) = 0;

		/**
		* Called every time the mouse is moved.
		* @param x The current position of the mouse along the x axis.
		* @param y The current position of the mouse along the y axis.
		**/
		virtual void mouseMoved(int xrel, int yrel) = 0;

	}; // Game

	typedef boost::shared_ptr<Game> pGame;

} // love

#endif // LOVE_GAME_H
