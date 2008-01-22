/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef FONT_TEX_GAME_H
#define FONT_TEX_GAME_H

#include "using_gl.h"
#include "using_graphics.h"
#include "using_audio.h"

// LOVE
#include "Game.h"
#include "Animation.h"
#include "Label.h"
#include "Button.h"

namespace love 
{

	/**
	* The legendary FontTexGame. The one and only pure C++
	* test game that will never die. Ever.
	*
	* @author Anders Ruud
	* @date 2006-09-01
	**/
	class FontTexGame : public Game
	{
	private:
	public:

		float x, y, r;
		pImage img;
		pAnimation animation;
		pFont font;
		pFont imgfont;
		pParticlesystem psys;
		pSound sound;
		pMusic music;
		pLabel label;
		pButton button;

		/**
		* @brief Creates a new FontTexGame object.
		**/
		FontTexGame();

		virtual ~FontTexGame();

		// From Game.
		bool load();
		void unload();
		void update(float dt);
		void render();
		void keyPressed(int key);

	}; // FontTexGame

} // love

#endif // FONT_TEX_GAME_H
