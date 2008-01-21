/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_GAME_H
#define LOVE_GAME_H

// LOVE
#include "Configuration.h"

// STD
#include <string>

namespace love
{

	/**
	* Abstract Game class.
	*
	* @author Anders Ruud
	* @date 2006-03-10
	**/
	class Game
	{
	protected:

		// The name of the game. Not to be confused with title.
		std::string name;

		// The source for this game's files. (Can be folder
		// or archive).
		std::string source;

	public:

		virtual ~Game();

		/**
		* Loads the game.
		**/
		virtual bool load() = 0;

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
		virtual void render() = 0;

		/**
		* Called when the mouse is pressed.
		* @param x The x-coordinate of the mousepress.
		* @param y The y-coordinate of the mousepress.
		* @param button The button that was pressed.
		**/
		virtual void mousePressed(float x, float y, int button);

		/**
		* Called when the mouse is released.
		* @param x The x-coordinate of the mouserelease.
		* @param y The y-coordinate of the mouserelease.
		* @param button The button that was released.
		**/
		virtual void mouseReleased(float x, float y, int button);

		/**
		* Called every time the mouse is moved.
		* @param x The current position of the mouse along the x axis.
		* @param y The current position of the mouse along the y axis.
		**/
		virtual void mouseMoved(float x, float y);

		/**
		* Called when a key is pressed.
		* @param key The ASCII key code.
		**/
		virtual void keyPressed(int key);

		/**
		* Called when a key is released.
		* @param key The ASCII key code.
		**/
		virtual void keyReleased(int key);

		/**
		* Gets the game's source. (Directory or archive).
		**/
		const std::string & getSource() const;

	protected:

		/**
		* Should free all resources allocated by load.
		**/
		virtual void unload() = 0;

	}; // Game
		
}// love

#endif // LOVE_GAME_H
