/**
* @file SelectGame.h
* @author Anders Ruud
* @date 2007-01-13
* @brief Contains definition for class SelectGame.
**/

#ifndef LOVE_SELECTGAME_H
#define LOVE_SELECTGAME_H

// LOVE
#include "Game.h"
#include "ImageFromFile.h"
#include "Text.h"

// STL
#include <vector>
using std::vector;

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	struct gameListElement
	{
		string str;
		string gameName;
		int x;
		int y;
		bool running;
	};

	/**
	* @class SelectGame
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-01-13
	* @brief 
	**/
	class SelectGame : public Game
	{
	private:

		pText text;
		pImageFromFile loveLogo;
		pImageFromFile hidoi;

		pFont gameFont;
		pColor gameColor;
		pColor black;

		int selectedgame;

		vector<gameListElement> gameList;

	public:

		/**
		* @brief Contructs an empty SelectGame.
		**/
		SelectGame();
		virtual ~SelectGame();

		void init();
		void render();
		void update(float dt);

		void renderGameList();

		void mousePressed(float x, float y, int button);

		void resume();

		void reloadGraphics();


	};

	typedef boost::shared_ptr<SelectGame> pSelectGame;

} // love

#endif

