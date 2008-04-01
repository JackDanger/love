/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_NO_GAME_H
#define LOVE_NO_GAME_H

#include "Game.h"

namespace love
{
	/**
	* @author Anders Ruud
	* @date 2008-03-29
	**/
	class NoGame : public Game
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

#endif // LOVE_GAME_H
