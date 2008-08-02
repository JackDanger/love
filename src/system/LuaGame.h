/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-04-04
*/

#ifndef LOVE_MOD_SYSTEM_LUA_GAME_H
#define LOVE_MOD_SYSTEM_LUA_GAME_H

// LOVE
#include <love/Game.h>
#include <love/Core.h>
#include <love/File.h>

// STD
#include <vector>

// Lua
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace love_system
{
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
		CALLBACK_GAMEPADAXISMOVED,
		CALLBACK_GAMEPADBUTTONPRESSED,
		CALLBACK_GAMEPADBUTTONRELEASED,
		CALLBACK_GAMEPADBALLMOVED,
		CALLBACK_GAMEPADHATMOVED,
		CALLBACK_MESSAGE,
		CALLBACK_EVENT, 
		CALLBACK_SIZE
	};

	class LuaGame : public love::Game
	{
	protected:

		// Pointer to core.
		love::Core * core;

		// The Lua virtual machine. ("LOVE Machine")
		lua_State * L;

		// List of present callback functions.
		bool callbacks[CALLBACK_SIZE];

	public:

		/**
		* Creates a new game.
		**/
		LuaGame(love::pFile file, love::Core * core);

		virtual ~LuaGame();

		// From Resource.
		bool load();
		void unload();

		// From Game.
		bool isLoaded() const;
		void update(float dt);
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseMoved(int xrel, int yrel);
		void gamepadAxisMoved(int index, int axis, int value);
		void gamepadButtonPressed(int index, int button);
		void gamepadButtonReleased(int index, int button);
		void gamepadBallMoved(int index, int ball, int x, int y);
		void gamepadHatMoved(int index, int direction, int value);

		void message(const char * msg, int tag);

		// Lua AUX functions.

		/**
		* Parses the contents of file as Lua code.
		* @param file A file containing Lua code.
		* @return False if file couldn't be parsed.
		**/
		bool parse(love::pFile file);

		/**
		* Checks if a function exists in the global table.
		**/
		bool isFunction(const std::string function);

		/**
		* Calls the chunk currently pushed onto the stack.
		* @param narg Number of arguments.
		* @param nres Number of results.
		**/
		int call(int narg, int nres);

		/**
		* Creates the global love table, and adds constants.
		**/
		void installConstants();

	}; // LuaGame

	typedef boost::shared_ptr<LuaGame> pLuaGame;

} // love_system

#endif // LOVE_MOD_SYSTEM_LUA_GAME_H
