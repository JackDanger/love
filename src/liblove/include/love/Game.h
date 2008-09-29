/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2006-03-10
*/

#ifndef LOVE_GAME_H
#define LOVE_GAME_H

// LOVE
#include "luax.h"

namespace love
{
	class Core;

	/**
	* Abstract Game class.
	**/
	class Game
	{
		// Friends
		friend class Core;

	private:

		// The Lua state.
		lua_State * L;

	public:

		Game();
		~Game();

		bool isLoaded() const;
		bool load();
		void unload();

	}; // Game

} // love

#endif // LOVE_GAME_H
