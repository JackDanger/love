/**
* @file Game.h
* @brief Contains definition of class Game.
* @date 2006-03-10
* @author Anders Ruud
**/

#ifndef LOVE_GAME_H
#define LOVE_GAME_H

// LOVE
#include "AbstractEntity.h"
#include "KeyListener.h"
#include "MouseListener.h"
#include "MouseMotionListener.h"
#include "EventListener.h"
#include "Container.h"
#include "Resumable.h"
#include "DisplayModeListener.h"
#include "Display.h"
#include "Loadable.h"
#include "AbstractImage.h"
#include "GameConfiguration.h"
#include "Initializable.h"
#include "Menu.h"

// GUIchan
#include <guichan.hpp>

// STL
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace love
{

	class GUIGameListElement;

	/**
	* @class Game
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-10
	* @brief Represents an actual Game.
	* This class is the abtract superclass of all games.
	**/
	class Game : public AbstractEntity, public KeyListener, public MouseListener, 
				 public EventListener, public Resumable, public DisplayModeListener, 
				 public Loadable, public Initializable
	{
	protected:

		friend class GUIGameListElement;
		friend class LoveMenu4;
		friend class Core;
		
		// Used for loading of title, author, thumbnail, etc.
		GameConfiguration * config;

		// For holding all the gui items in the game
		gcn::Container * gui;

		// The base diretory for this game.
		string source;

		bool suspended;

	public:

		/**
		* @brief Creates a new Game object.
		**/
		Game();

		/**
		* @brief Descructor.
		**/
		virtual ~Game();

		/**
		* @brief Called when the mouse is pressed.
		* @param x The x-coordinate of the mousepress.
		* @param y The y-coordinate of the mousepress.
		* @param button The button that was pressed.
		**/
		virtual void mousePressed(float x, float y, int button);

		/**
		* @brief Called when the mouse is released.
		* @param x The x-coordinate of the mouserelease.
		* @param y The y-coordinate of the mouserelease.
		* @param button The button that was released.
		**/
		virtual void mouseReleased(float x, float y, int button);

		/**
		* @brief Called every time the mouse is moved.
		* @param x The current position of the mouse along the x axis.
		* @param y The current position of the mouse along the y axis.
		**/
		virtual void mouseMoved(float x, float y);

		/**
		* @brief Called when a key is pressed.
		* @param key The ASCII key code.
		**/
		virtual void keyPressed(int key);

		/**
		* @brief Called when a key is released.
		* @param key The ASCII key code.
		**/
		virtual void keyReleased(int key);

		/**
		* @brief Called every time an Event is fired.
		* @param e The Event that just was fired.
		**/
		virtual void eventFired(pEvent e);

		/**
		* @brief Called when a Game is suspended and we return to the menu.
		**/
		virtual void suspend();

		/**
		* @brief Called when a Game is resumed (from suspension).
		**/
		virtual void resume();

		/**
		* @brief Called when the core stops the game.
		**/
		virtual void stop();

		/**
		 * @brief Checks to see if the game has been suspended.
		 * @return Whether the game is suspended or not.
		 **/
		virtual bool isSuspended();

		/**
		* @brief Called from love::core when graphics needs to be reloaded.
		**/ 
		virtual void reloadGraphics() = 0;

		/**
		 * @brief Returns the gui item so that it can be manipulated outside of the game istelf.
		 * @return A GUIchan Container class.
		 **/ 
		virtual gcn::Container * getGUI();

		/**
		* @brief Returns the source of this game.
		* @return The source for this game.
		**/
		const string & getSource() const;
	};

	typedef boost::shared_ptr<Game> pGame;
		
}// love

#endif
