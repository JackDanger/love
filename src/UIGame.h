#ifndef LOVE_UI_GAME_H
#define LOVE_UI_GAME_H

#include "Game.h"
#include "AbstractImage.h"
#include "Color.h"
#include "GUIEvent.h"

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

using std::string;
using std::map;

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
		const static int MODE_DEFAULT = 0;
		const static int MODE_PAUSE = 1;
		const static int MODE_ERROR = 2;
		const static int MODE_SETTINGS = 3;
		const static int MODE_MENUPAUSE = 4;

		gcn::Container * top;
		Game * previous; // The suspeded game.
		pAbstractFont pauseFont;

		// Resources
		map<string, pAbstractImage> images;

		pAbstractFont titleFont;
		pAbstractFont subtitleFont;
		pAbstractFont defaultFont;


		// Widgets
		pMultilineLabel errorText;
		pButton tabPause;
		pButton tabSettings;
		pLabel pauseLabel;
		pLabel thumbLabel;
		pMultilineLabel gameTitle;
		pMultilineLabel gameCreator;
		pButton okButton;
		pButton cancelButton;

		pAbstractMenu pauseMenu;
		pAbstractMenu settingsMenu;

		Menu * error;
		Menu * pause;
		Menu * settings;

		// pause-menu settings
		pCheckBox settingsFullscreen;
		pCheckBox settingsVSync;
		pSlider settingsSound;
		pSlider settingsMusic;
		pCheckBox settingsMute;


		// main settings
		pAbstractMenu settingsGeneral;
		pButton generalTab;

		pAbstractMenu settingsVideo;
		pButton videoTab;
		pCheckBox settingsVideoFullscreen;
		pCheckBox settingsVideoVSync;
		pDropDown settingsVideoResolution;

		pAbstractMenu settingsAudio;
		pButton audioTab;
		pSlider settingsAudioSound;
		pSlider settingsAudioMusic;
		pCheckBox settingsAudioMute;
		pDropDown settingsAudioQuality;
		pDropDown settingsAudioLatency;

		pAbstractMenu settingsPaths;
		pButton pathsTab;
		pTextField settingsPathsConfig;
		pTextField settingsPathsResource;
		pTextField settingsPathsGamedir;


		int mode;

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
		* @brief Called when a key is pressed.
		* @param key The key that was pressed.
		**/
		virtual void keyPressed(int key);

		/**
		* @brief Called when a key is released.
		* @param key The key that was released.
		**/
		virtual void keyReleased(int key);

		/**
		 * @brief Updates the GUI to be the same size as the new display mode.
		 **/
		virtual void displayModeChanged();
	};
}

#endif
