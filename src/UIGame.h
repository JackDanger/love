#ifndef LOVE_UI_GAME_H
#define LOVE_UI_GAME_H

#include "Game.h"
#include "AbstractImage.h"
#include "Color.h"
#include "GUIEvent.h"

#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	 * @class UIGame
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-10-15
	 * @brief A game for handling the built-in UI events.
	 **/
	class UIGame : public Game
	{
	protected:
		// The suspeded game
		gcn::Container * top;
		Game * previous;
		pAbstractImage errorWarning;
		pAbstractImage errorError;
		pAbstractFont errorFont;
		pAbstractFont pauseFont;
		Menu * error;
		Menu * warning;
		Menu * pause;
		pMultilineLabel errorText;
		pMultilineLabel warningText;
		pButton errorButton;
		pButton warningButton;

		// If the UI is in error mode, the previous
		// game will not rendered.
		bool errorMode;

		virtual void resumeGame();
		virtual void reloadGame();
		virtual void quitGame();

	public:
		/**
		 * @brief Default constructor.
		 **/
		UIGame();

		/**
		 * @brief Deconstructor. Deletes pointers.
		 **/
		~UIGame();

		/**
		 * @brief Creates the GUI items.
		 **/
		virtual int init();

		/**
		 * @brief Does nothing.
		 **/
		virtual int load();

		/**
		 * @brief Does nothing.
		 **/
		virtual void unload();

		/**
		 * @brief Renders the previous game.
		 **/
		virtual void render();

		/**
		 * @brief Does nothing (the previous game isn't supposed to get any updates).
		 **/
		virtual void update(float dt);

		/**
		 * @brief Reloads the graphics of the previous game and all my fonts.
		 **/
		virtual void reloadGraphics();

		/**
		 * @param text The error text.
		 * @brief Shows an error message.
		 **/
		virtual void showError(const char * text);

		/**
		 * @param text The warning text.
		 * @brief Shows a warning message.
		 **/
		virtual void showWarning(const char * text);

		/**
		 * @brief Shows the pause menu.
		 **/
		virtual void showPause();

		/**
		 * @brief Unpauses.
		 **/
		virtual void hidePause();

		/**
		 * @return True if paused. False if not paused.
		 * @brief Checks if the system is paused.
		 **/
		virtual bool isPaused();

		/**
		 * @param e The event in question.
		 * @brief Handles events, like the clicking of buttons.
		 **/
		virtual void eventFired(pEvent e);

		/**
		 * @brief Updates the GUI to be the same size as the new display mode.
		 **/
		virtual void displayModeChanged();
	};
}

#endif