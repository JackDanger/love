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
		gcn::Container * top;
		Game * previous; // The suspeded game.
		pAbstractImage errorWarning;
		pAbstractImage errorError;
		pAbstractFont errorFont;
		pAbstractFont pauseFont;
		Menu * error;
		Menu * warning;
		Menu * pause;
		Menu * settings;
		pMultilineLabel errorText;
		pMultilineLabel warningText;
		pButton errorButton;
		pButton warningButton;

		pCheckBox settingsFullscreen;
		pCheckBox settingsVSync;
		pDropDown settingsResolution;
		pSlider settingsSound;
		pSlider settingsMusic;

		bool errorMode; // If the UI is in error mode, the previous game will not rendered.
		bool pauseMode; // If in pause mode, it will go to the pause menu after settings.
		bool settingsMode; // If in settings mode, it will show the pause menu (and hide the settings) if hidePause() is called.

		virtual void resumeGame();
		virtual void reloadGame();
		virtual void quitGame();
		virtual void saveSettings();

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
		 * @brief Creates the GUI items and calls load().
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
		 * @brief Shows the settings menu.
		 **/
		virtual void showSettings();

		/**
		 * @brief Hides the pause menu (and unpauses).
		 **/
		virtual void hideSettings();

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
