/**
* @file LoveMenu.h
* @author Anders Ruud
* @date 2007-04-28
* @brief Contains definition for class LoveMenu.
**/

#ifndef LOVE_LOVEMENU_H
#define LOVE_LOVEMENU_H

// LOVE
#include "Game.h"
#include "Container.h"
#include "ImageFromFile.h"
#include "Font.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* @class LoveMenu
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-04-28
	* @brief 
	**/
	class LoveMenu : public Game
	{
	private:

		Container<Game> * games;

		pAbstractImage defaultThumb;
		pAbstractImage defaultThumbDither;

		pAbstractImage loveBottomRight;

		pFont font;

		static const int T_WIDTH = 216;
		static const int T_HEIGHT = 166;
		static const int X_PAD = 10;
		static const int Y_PAD = 10;
		static const int X_TEXT_PAD = X_PAD + 12;
		static const int Y_TEXT_PAD = Y_PAD + 23;

		int W;

		int displayWidth;
		int displayHeight;

		float xMouse;
		float yMouse;

		float xMouseWorld;
		float yMouseWorld;

		bool mouseDown;

		float xLastMouseDown;
		float yLastMouseDown;

		float xpos;
		float ypos;

		float worldWidth;
		float worldHeight;

	public:

		/**
		* @brief Contructs an empty LoveMenu.
		**/
		LoveMenu();

		LoveMenu(Container<Game> * games);

		virtual ~LoveMenu();

		/**
		* @brief Initializes the game.
		**/
		void init();

		/**
		* @brief Renders the entire game once.
		**/
		void render();

		void renderThumb(const pAbstractImage & img, float x, float y, int alpha = 128);
		void renderText(const string & s, float x, float y, int alpha = 128);

		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);

		/**
		* @brief Updates the entire game.
		* @param dt The time since last frame (in seconds).
		**/
		void update(float dt);

		int load();

		void unload();

		void resume();

		void reloadGraphics();
	};

	typedef boost::shared_ptr<LoveMenu> pLoveMenu;

} // love

#endif
