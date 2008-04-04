/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-04-04
*/

#ifndef LOVE_NO_GAME_H
#define LOVE_NO_GAME_H

// LOVE
#include "LuaGame.h"

namespace love
{
	/**
	* This game is activated when no game is specified.
	**/
	class NoGame : public LuaGame
	{
	public:

		/**
		* Creates a new game.
		**/
		NoGame();

		~NoGame();

		/**
		* Loads the game.
		**/
		bool load();

	}; // NoGame

} // love

#endif // LOVE_NO_GAME_H
