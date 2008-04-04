/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SUSPEND_GAME_H
#define LOVE_SUSPEND_GAME_H

// LOVE
#include "Game.h"

namespace love
{
	/**
	* @author Anders Ruud
	* @date 2008-04-02
	**/
	class SuspendGame : public Game
	{
	public:

		/**
		* Creates a new game.
		**/
		SuspendGame();
		~SuspendGame();

		// From Game.
		bool isConsoleVisible() const; // Always true.
		bool require(Module & m);
		bool load();
		bool unload();
		void update(float dt);
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseMoved(int xrel, int yrel);

	}; // SuspendGame

} // love

#endif // LOVE_SUSPEND_GAME_H
