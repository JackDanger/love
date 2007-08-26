/**
* @file LoveMenu3.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class LoveMenu3.
**/

#ifndef LOVE_LOVEMENU3_H
#define LOVE_LOVEMENU3_H

// LOVE
#include "Game.h"
#include "GUIDynamicBackground.h"
#include "GUIGameList.h"
#include "GUIRadialKnob.h"
#include "Text.h"
#include "Container.h"
#include "GUICircleButton.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class LoveMenu3
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class LoveMenu3 : public Game
	{
	private:

		Container<Game> * games;

		Container<AbstractImage> images;
		Container<Font> fonts;

		pGUICircleButton exit;
		pGUIRadialKnob knob;

		GUIDynamicBackground bg;
		GUIGameList list;
		pText text;

	public:

		/**
		* @brief Contructs an empty LoveMenu3.
		**/
		LoveMenu3();
		LoveMenu3(Container<Game> * games);
		virtual ~LoveMenu3();

		void init();
		void render();
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);
		void update(float dt);
		int load();
		void unload();
		void resume();
		void reloadGraphics();

		void keyPressed(int key);

		void eventFired(pEvent e);

	};

	typedef boost::shared_ptr<LoveMenu3> pLoveMenu3;

} // love

#endif

