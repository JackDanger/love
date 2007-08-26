/**
* @file GUIGameListElement.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUIGameListElement.
**/

#ifndef LOVE_GUIGAMELISTELEMENT_H
#define LOVE_GUIGAMELISTELEMENT_H

// LOVE
#include "GUIEntity.h"
#include "ImageFromFile.h"
#include "Font.h"
#include "GUICircleButton.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	class Game;

	/**
	* @class GUIGameListElement
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GUIGameListElement : public GUIEntity
	{
	private:

		friend class GUIGameList;
		friend class GUIGameList2;

		// game
		Game * game;

		// scale
		float scale;

		float angle;

		pGUICircleButton play;
		pGUICircleButton restart;
		pGUICircleButton stop;

		float initialButtonX;
		float initialButtonY;

		float buttonPaddingX;
		float buttonPaddingY;


		AbstractImage * defaultThumb;
		AbstractImage *  defaultThumbDither;

		AbstractImage * playImage;
		AbstractImage * stopImage;
		AbstractImage * restartImage;

		Font * font;
		Font * smallFont;

		float buttonsAlpha;


	public:




		/**
		* @brief Contructs an empty GUIGameListElement.
		**/
		GUIGameListElement(AbstractImage * defaultThumb, AbstractImage * defaultThumbDither, Font * font, Font * smallFont, AbstractImage * playImage, AbstractImage * stopImage, AbstractImage * restartImage);
		virtual ~GUIGameListElement();

		/**
		* @brief Gets Game.
		* @return Game.
		**/
		Game * getGame();


		/**
		* @brief Sets Game.
		* @param Game 
		**/
		void setGame(Game * game);


		/**
		* @brief Gets scale.
		* @return scale.
		**/
		float getScale() const;


		/**
		* @brief Sets scale.
		* @param scale 
		**/
		void setScale(float scale);

		void render();
		void update(float dt);

		int load();
		void unload();

		void mousePressed(float x, float y, int button);


	};

	typedef boost::shared_ptr<GUIGameListElement> pGUIGameListElement;

} // love

#endif

