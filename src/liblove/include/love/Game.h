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

// LOVE
#include "Resource.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class Core;

	/**
	* Abstract Game class.
	**/
	class Game : public Resource
	{
	public:

		/**
		* Creates a new game.
		**/
		Game(pFile file);

		virtual ~Game();

		/**
		* Should return true if the game has been loaded.
		**/
		virtual bool isLoaded() const = 0;
		
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

		/**
		* Called every time a button on a gamepad is pressed.
		* @param index The index of the gamepad.
		* @param button The button which was pressed.
		**/
		virtual void joystickPressed(int index, int button) = 0;

		/**
		* Called every time a button on a gamepad is released.
		* @param index The index of the gamepad.
		* @param button The button which was released.
		**/
		virtual void joystickReleased(int index, int button) = 0;

	}; // Game

	typedef boost::shared_ptr<Game> pGame;

} // love

#endif // LOVE_GAME_H
