/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_GAME_H
#define LOVE_GAME_H

#include "LuaVM.h"
#include <vector>

namespace love
{

	// Forward declarations.
	class Module;
	class Filesystem;

	// Callback constants.
	enum
	{
		CALLBACK_LOAD, 
		CALLBACK_UPDATE, 
		CALLBACK_DRAW, 
		CALLBACK_KEYPRESSED, 
		CALLBACK_KEYRELEASED, 
		CALLBACK_MOUSEPRESSED, 
		CALLBACK_MOUSERELEASED, 
		CALLBACK_MOUSEMOVED, 
		CALLBACK_EVENT, 
		CALLBACK_SIZE
	};


	/**
	* @author Anders Ruud
	* @date 2006-03-10
	**/
	class Game
	{
		friend bool init(int argc, char* argv[]);
	protected:

		Filesystem * filesystem;

		// The Lua virtual machine. ("LOVE Machine")
		LuaVM vm;

		// List of present callback functions.
		bool callbacks[CALLBACK_SIZE];

		// A list of function pointers that provide
		// Lua interfaces.
		std::vector<fptr_luaopen> libs;

		// True if console is visible.
		bool consoleVisible;

	public:

		/**
		* Creates a new game.
		**/
		Game();

		virtual ~Game();

		/**
		* Adds a Module to the list of required libraries.
		* (Will be reloaded automatically on reloads).
		**/
		bool require(Module & m);
		
		/**
		* Sets the Filesystem pointer.
		**/
		void setFilesystem(Filesystem * fs);

		bool isConsoleVisible() const;
		void setConsoleVisible(bool visible);

		/**
		* Loads the game.
		**/
		virtual bool load();

		/**
		* Unloads the game.
		**/
		bool unload();

		/**
		* Calls unload, then load. Returns result from load.
		**/
		bool reload();

		/**
		* Called each time the Game should be updated.
		* @param dt The time since last frame.
		**/
		void update(float dt);

		/**
		* Called each time the Game should be rendered.
		**/
		void draw();

		/**
		* Called when a key is pressed.
		* @param key The ASCII key code.
		**/
		void keyPressed(int key);

		/**
		* Called when a key is released.
		* @param key The ASCII key code.
		**/
		void keyReleased(int key);

		/**
		* Called when the mouse is pressed.
		* @param x The x-coordinate of the mousepress.
		* @param y The y-coordinate of the mousepress.
		* @param button The button that was pressed.
		**/
		void mousePressed(int x, int y, int button);

		/**
		* Called when the mouse is released.
		* @param x The x-coordinate of the mouserelease.
		* @param y The y-coordinate of the mouserelease.
		* @param button The button that was released.
		**/
		void mouseReleased(int x, int y, int button);

		/**
		* Called every time the mouse is moved.
		* @param x The current position of the mouse along the x axis.
		* @param y The current position of the mouse along the y axis.
		**/
		void mouseMoved(int xrel, int yrel);

	}; // Game

} // love

#endif // LOVE_GAME_H
