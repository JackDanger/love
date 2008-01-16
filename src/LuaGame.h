/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_LUA_GAME_H
#define LOVE_LUA_GAME_H

// LOVE
#include "Game.h"
#include "LuaVM.h"

// STD
#include <set>

namespace love
{

	// Callback constants.
	enum
	{
		LOVE_CALLBACK_LOAD, 
		LOVE_CALLBACK_UPDATE, 
		LOVE_CALLBACK_RENDER, 
		LOVE_CALLBACK_KEYPRESSED, 
		LOVE_CALLBACK_KEYRELEASED, 
		LOVE_CALLBACK_MOUSEPRESSED, 
		LOVE_CALLBACK_MOUSERELEASED, 
		LOVE_CALLBACK_EVENT, 
		LOVE_CALLBACK_SIZE
	};

	/**
	* Lua-scriptable Game class.
	*
	* @author Anders Ruud
	* @date 2006-11-06
	**/
	class LuaGame : public Game
	{
	private:

		// The Lua virtual machine used by the Game.
		LuaVM vm;

		// List of present callback functions.
		bool callbacks[LOVE_CALLBACK_SIZE];

		// A list of all included files.
		std::set<std::string> included;

	public:

		/**
		* Creates a new LuaGame.
		* @param source The source for the game. Can be directory or archive file. (.love only)
		**/
		LuaGame(const std::string & source);

		virtual ~LuaGame();

		/**
		* Reads and parses a Lua-file.
		* This method checks if the file already is included, and
		* does not include if it is.
		* 
		* @param filename The filname and path to the file.
		**/
		void include(const std::string & filename);
		
		// From Game.
		bool load();
		void unload();
		void render();
		void update(float dt);
		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);

	}; // LuaGame

} // love

#endif // LOVE_LUA_GAME_H
