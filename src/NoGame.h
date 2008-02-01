/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_NO_GAME_H
#define LOVE_NO_GAME_H

// LOVE
#include "Game.h"
#include "Font.h"
#include "Image.h"
#include "AnimatedColor.h"

namespace love 
{

	/**
	* The Game that is started when no game was passed
	* as an argument.
	*
	* @author Anders Ruud
	* @date 2008-22-01
	**/
	class NoGame : public Game
	{
	private:
		pFont big, small;
		pImage logo_big, logo_small, mini_moose;

		// Mini-moose angle.
		float moose_angle;
		float flashb, flashi;
		bool render_nogame;

	public:

		NoGame();

		virtual ~NoGame();

		// From Game.
		bool load();
		void unload();
		void update(float dt);
		void render();
		void keyPressed(int key);

	}; // NoGame

} // love

#endif // LOVE_NO_GAME_H
