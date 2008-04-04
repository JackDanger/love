/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-04-04
*/

#ifndef LOVE_LUA_GAME_H
#define LOVE_LUA_GAME_H

// LOVE
#include "Game.h"
#include "LuaVM.h"

// STD
#include <vector>

namespace love
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
		CALLBACK_EVENT, 
		CALLBACK_SIZE
	};

	class LuaGame : public Game
	{
	protected:

		// The Lua virtual machine. ("LOVE Machine")
		LuaVM vm;

		// List of present callback functions.
		bool callbacks[CALLBACK_SIZE];

		// A list of function pointers that provide
		// Lua interfaces.
		std::vector<fptr_luaopen> libs;

	public:

		/**
		* Creates a new game.
		**/
		LuaGame();

		virtual ~LuaGame();

		// From Game.
		virtual bool require(Module & m);
		virtual bool load();
		virtual bool unload();
		virtual void update(float dt);
		virtual void draw();
		virtual void keyPressed(int key);
		virtual void keyReleased(int key);
		virtual void mousePressed(int x, int y, int button);
		virtual void mouseReleased(int x, int y, int button);
		virtual void mouseMoved(int xrel, int yrel);

	}; // LuaGame

} // love

#endif // LOVE_LUA_GAME_H
