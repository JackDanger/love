/**
* @file LoveMenu4.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class LoveMenu4.
**/

#ifndef LOVE_LoveMenu4_H
#define LOVE_LoveMenu4_H

// LOVE
#include "Game.h"
#include "GUIDynamicBackground.h"
#include "GUIGameList2.h"
#include "GUIRadialKnob.h"
#include "Text.h"
#include "Container.h"
#include "GUICircleButton.h"
#include "Vector.h"

#include "AbstractSound.h"
#include "AbstractMusic.h"

// STL

#include <map>
using std::map;
using std::string;
// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class ConfigLoader;

	/**
	* @class LoveMenu4
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class LoveMenu4 : public Game
	{
	private:

		AbstractMusic * music;
		AbstractSound * sound;

		Container<Game> * games;

		map<string, pAbstractImage> images;
		map<string, pAbstractFont> fonts;



		pGUICircleButton exit;
		pGUIRadialKnob knob;

		GUIDynamicBackground bg;
		GUIGameList2 list;
		//pText text;

		ConfigLoader * configLoader;

	public:

		/**
		* @brief Contructs an empty LoveMenu4.
		**/
		LoveMenu4();
		LoveMenu4(Container<Game> * games);
		virtual ~LoveMenu4();

		int init();
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

	private:

		//Vector positionFunc(float t);

	};

	typedef boost::shared_ptr<LoveMenu4> pLoveMenu4;

} // love

#endif

