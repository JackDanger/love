#include "UIGame.h"

#include "love_keys.h"
#include "Core.h"
#include "love.h"
#include "AbstractDisplay.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"
#include "DisplayMode.h"

using boost::dynamic_pointer_cast;

namespace love
{
	void UIGame::resumeGame()
	{
		core->current = previous;
		previous = 0;
		core->gui->remove(top);
		core->current->resume();

		// Exits error mode.
		mode = MODE_DEFAULT;
	}

	void UIGame::reloadGame()
	{
		top->clear();
		core->gui->remove(top);

		core->current = previous;
		previous = 0;

		core->current->reload();
		printf("Reloaded: %s\n", core->current->getName().c_str());

		// Exits error mode.
		mode = MODE_DEFAULT;
	}

	void UIGame::quitGame()
	{
		previous->stop();
		previous->unload();
		previous = 0;
		top->clear();
		core->gui->remove(top);

		// Exits error mode.
		mode = MODE_DEFAULT;

		if(core->runningExternalGame)
			core->quit();
		else
			core->startGame("love-system-menu", false);
	}

	void UIGame::saveSettings()
	{
		if(mode == MODE_MENUPAUSE) // save all settings
		{
			core->config->addBool("fullscreen", settingsVideoFullscreen->isMarked());
			core->config->addBool("vsync", settingsVideoVSync->isMarked());
			core->config->addString("default_resolution", settingsVideoResolution->getSelectedElement());

			core->config->addInt("sound_volume", (float)settingsAudioSound->getValue());
			core->config->addInt("music_volume", (float)settingsAudioMusic->getValue());
			core->config->addBool("mute", settingsAudioMute->isMarked());
			string temp = settingsAudioQuality->getSelectedElement();
			int num = atoi(temp.substr(0, temp.find(' ')).c_str()); // removes anything beyond the number
			core->config->addInt("audio_quality", (float)num);
			temp = settingsAudioLatency->getSelectedElement();
			num = atoi(temp.substr(0, temp.find(' ')).c_str()); // ditto
			core->config->addInt("audio_latency", (float)num);

			core->config->addString("config_path", settingsPathsConfig->getText());
			core->config->addString("resource_path", settingsPathsResource->getText());
			core->config->addString("gamedir", settingsPathsGamedir->getText());
		}
		else // only save the in-game settings
		{
			core->config->addBool("fullscreen", settingsFullscreen->isMarked());
			core->config->addBool("vsync", settingsVSync->isMarked());
			core->config->addInt("sound_volume", (float)settingsSound->getValue());
			core->config->addInt("music_volume", (float)settingsMusic->getValue());
			core->config->addBool("mute", settingsMute->isMarked());
		}
		core->config->write();
		hideSettings();
	}

	UIGame::UIGame() : mode(MODE_DEFAULT)
	{
		images.clear();
		previous = 0;
		error = 0;
		pause = 0;
		settings = 0;
		top = 0;
		loaded = false;
	}

	UIGame::~UIGame()
	{
		if(error != 0) delete error;
		if(pause != 0) delete pause;
		if(settings != 0) delete settings;
		if(top != 0) delete top;
		images.clear();
	}

	int UIGame::init()
	{
		top = new gcn::Container();
		top->setDimension(gcn::Rectangle(0, 0, core->display->getCurrentDisplayMode().getWidth(), core->display->getCurrentDisplayMode().getHeight()));
		top->setBaseColor(gcn::Color(99,170,218,127));
		top->setOpaque(true);

		// resources
		images["errorBackground"] = core->graphics->getImage("data/gui/error_background.png");
		images["errorBackground"]->load();
		images["pauseBackground"] = core->graphics->getImage("data/gui/pause_background.png");
		images["pauseBackground"]->load();
		images["settingsBackground"] = core->graphics->getImage("data/gui/settings_background.png");
		images["settingsBackground"]->load();

		images["buttonDefault"] = core->graphics->getImage("data/gui/button_default.png");
		images["buttonDefault"]->load();
		images["buttonHover"] = core->graphics->getImage("data/gui/button_hover.png");
		images["buttonHover"]->load();
		images["buttonPressed"] = core->graphics->getImage("data/gui/button_pressed.png");
		images["buttonPressed"]->load();
		images["buttonQuit"] = core->graphics->getImage("data/gui/button_quit.png");
		images["buttonQuit"]->load();

		images["checkBoxDefault"] = core->graphics->getImage("data/gui/checkbox_default.png");
		images["checkBoxDefault"]->load();
		images["checkBoxHover"] = core->graphics->getImage("data/gui/checkbox_hover.png");
		images["checkBoxHover"]->load();
		images["checkBoxMarked"] = core->graphics->getImage("data/gui/checkbox_marked.png");
		images["checkBoxMarked"]->load();

		images["sliderBar"] = core->graphics->getImage("data/gui/slider_bar.png");
		images["sliderBar"]->load();
		images["slider"] = core->graphics->getImage("data/gui/slider.png");
		images["slider"]->load();

		images["dropDownBackground"] = core->graphics->getImage("data/gui/dropdown_background.png");
		images["dropDownBackground"]->load();
		images["dropDownButton"] = core->graphics->getImage("data/gui/dropdown_button.png");
		images["dropDownButton"]->load();
		images["dropDownButtonHover"] = core->graphics->getImage("data/gui/dropdown_button_hover.png");
		images["dropDownButtonHover"]->load();
		images["dropDownButtonPressed"] = core->graphics->getImage("data/gui/dropdown_button_pressed.png");
		images["dropDownButtonPressed"]->load();

		images["line"] = core->graphics->getImage("data/gui/line.png");
		images["line"]->load();

		images["tabDefault"] = core->graphics->getImage("data/gui/tab_default.png");
		images["tabDefault"]->load();
		images["tabHover"] = core->graphics->getImage("data/gui/tab_hover.png");
		images["tabHover"]->load();
		images["tabActive"] = core->graphics->getImage("data/gui/tab_active.png");
		images["tabActive"]->load();

		images["imageBackground"] = core->graphics->getImage("data/gui/image_background.png");
		images["imageBackground"]->load();
		images["imageDefault"] = core->graphics->getImage("data/gui/thumb_default.png");
		images["imageDefault"]->load();

		titleFont = core->graphics->getFont("data/fonts/VeraBd.ttf", 10);
		titleFont->load();
		subtitleFont = core->graphics->getFont("data/fonts/Vera.ttf", 10);
		subtitleFont->load();
		defaultFont = core->graphics->getFont("data/fonts/Vera.ttf", 8);
		defaultFont->load();
		
		pauseFont = core->graphics->getFont("data/fonts/FreeSans.ttf", 14);
		pauseFont->load();


		// temp variables
		pAbstractColor black(new Color(0x000000));
		pAbstractColor white(new Color(0xFFFFFF));
		pAbstractColor buttonColor(new Color(255,255,255,200));
		pAbstractColor quitColor(new Color(255,255,255,150));
		pAbstractColor dropDownBack(new Color(0x327BAC)); dropDownBack->setAlpha(153);
		pAbstractColor dropDownSelect(new Color(0xA8D6F5));
		pAbstractColor dropDownBorder(new Color(0X7AB6DF));
		pAbstractColor dropDownSelectColor(new Color(0x316081));

		pLabel label;
		pButton button;


		// error box
		error = new Menu(defaultFont, white);
		error->setSize((int)images["errorBackground"]->getWidth(), (int)images["errorBackground"]->getHeight());
		error->setBackground(images["errorBackground"]);
		
		label = error->addLabel("An error has occurred");
		label->setPosition(24, 69); label->setFont(titleFont); label->adjustSize();
		
		label = error->addImage(images["line"]);
		label->setPosition(24, 87);
		
		errorText = error->addMultilineLabel("");
		errorText->setPosition(24, 102); errorText->setSize(358, 202); errorText->align(Text::LOVE_ALIGN_LEFT); errorText->valign(Text::LOVE_ALIGN_TOP);
		
		button = error->addButton("CORE_ERROR_RESTART", "  Restart");
		button->setDefaultImage(images["buttonDefault"]); button->setHoverImage(images["buttonHover"]); button->setPressedImage(images["buttonPressed"]);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(141, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_CONTINUE", "  Continue");
		button->setDefaultImage(images["buttonDefault"]); button->setHoverImage(images["buttonHover"]); button->setPressedImage(images["buttonPressed"]);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(230, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_QUIT", "  Quit");
		button->setDefaultImage(images["buttonQuit"]); button->setHoverImage(images["buttonHover"]); button->setPressedImage(images["buttonPressed"]);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(319, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

		error->show();


		// pause menu
		pause = new Menu(defaultFont, white);
		pause->setSize((int)images["pauseBackground"]->getWidth(), (int)images["pauseBackground"]->getHeight());
		pause->setBackground(images["pauseBackground"]);

		pauseLabel = pause->addLabel("Game paused");
		pauseLabel->setPosition(33, 64); pauseLabel->setFont(titleFont); pauseLabel->adjustSize();

		label = pause->addImage(images["line"]);
		label->setPosition(33, 81);

		tabPause = pause->addButton("CORE_TAB_PAUSE", "Pause");
		tabPause->setDefaultImage(images["tabActive"]);
		tabPause->setPosition(45,25); tabPause->align(Text::LOVE_ALIGN_CENTER); tabPause->adjustSize();

		tabSettings = pause->addButton("CORE_TAB_SETTINGS", "Settings");
		tabSettings->setDefaultImage(images["tabDefault"]); tabSettings->setHoverImage(images["tabHover"]);
		tabSettings->setPosition(105,25); tabSettings->align(Text::LOVE_ALIGN_CENTER); tabSettings->adjustSize();

		pauseMenu = pause->addMenu(AbstractMenu::LOVE_MENU_HORIZONTAL, 358, 167);
		pauseMenu->setPosition(33,100);

		label = pauseMenu->addImage(images["imageBackground"]);
		label->setPosition(0,0);

		thumbLabel = pauseMenu->addImage(images["imageDefault"]);
		thumbLabel->setPosition(4, 4);

		gameTitle = pauseMenu->addMultilineLabel("Game Title", 143);
		gameTitle->setPosition(215, 0); gameTitle->align(Text::LOVE_ALIGN_LEFT); gameTitle->setFont(subtitleFont); gameTitle->adjustSize();

		gameCreator = pauseMenu->addMultilineLabel("by Unknown", 143);
		gameCreator->setPosition(215, 8 + gameTitle->getHeight()); gameCreator->align(Text::LOVE_ALIGN_LEFT); gameCreator->adjustSize();

		pauseMenu->show();

		settingsMenu = pause->addMenu(AbstractMenu::LOVE_MENU_HORIZONTAL, 358, 167);
		settingsMenu->setPosition(33,100);

		settingsFullscreen = settingsMenu->addCheckBox("CORE_SETTINGS_FULLSCREEN", "  Fullscreen");
		settingsFullscreen->setDefaultImage(images["checkBoxDefault"]); settingsFullscreen->setHoverImage(images["checkBoxHover"]); settingsFullscreen->setMarkedImage(images["checkBoxMarked"]);
		settingsFullscreen->setColor(buttonColor); settingsFullscreen->setHoverColor(white);  
		settingsFullscreen->setPosition(24,8); settingsFullscreen->adjustSize();

		settingsVSync = settingsMenu->addCheckBox("CORE_SETTINGS_FULLSCREEN", "  Vertical Sync");
		settingsVSync->setDefaultImage(images["checkBoxDefault"]); settingsVSync->setHoverImage(images["checkBoxHover"]); settingsVSync->setMarkedImage(images["checkBoxMarked"]);
		settingsVSync->setColor(buttonColor); settingsVSync->setHoverColor(white);  
		settingsVSync->setPosition(24,33); settingsVSync->adjustSize();

		label = settingsMenu->addImage(images["line"]);
		label->setPosition(0, 60);

		label = settingsMenu->addLabel("Sound Volume");
		label->setPosition(24, 80); label->adjustSize();

		settingsSound = settingsMenu->addSlider("CORE_SETTINGS_SOUND", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsSound->setBackgroundImage(images["sliderBar"]); settingsSound->setMarkerImage(images["slider"]); settingsSound->adjustSize();
		settingsSound->setPosition(140, 80); settingsSound->setBorderSize(0);

		label = settingsMenu->addLabel("Music Volume");
		label->setPosition(24, 110); label->adjustSize();

		settingsMusic = settingsMenu->addSlider("CORE_SETTINGS_MUSIC", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsMusic->setBackgroundImage(images["sliderBar"]); settingsMusic->setMarkerImage(images["slider"]); settingsMusic->adjustSize();
		settingsMusic->setPosition(140, 110); settingsMusic->setBorderSize(0);

		settingsMute = settingsMenu->addCheckBox("CORE_SETTINGS_MUTE", "  Mute");
		settingsMute->setDefaultImage(images["checkBoxDefault"]); settingsMute->setHoverImage(images["checkBoxHover"]); settingsMute->setMarkedImage(images["checkBoxMarked"]);
		settingsMute->setColor(buttonColor); settingsMute->setHoverColor(white);  
		settingsMute->setPosition(24,140); settingsMute->adjustSize();

		settingsMenu->hide();

		cancelButton = pause->addButton("CORE_CANCEL", "  Quit");
		cancelButton->setDefaultImage(images["buttonDefault"]); cancelButton->setHoverImage(images["buttonHover"]); cancelButton->setPressedImage(images["buttonPressed"]);
		cancelButton->setColor(quitColor); cancelButton->setHoverColor(white);  
		cancelButton->setPosition(24, 287); cancelButton->align(Text::LOVE_ALIGN_LEFT); cancelButton->adjustSize();

		okButton = pause->addButton("CORE_OK", "  Resume");
		okButton->setDefaultImage(images["buttonDefault"]); okButton->setHoverImage(images["buttonHover"]); okButton->setPressedImage(images["buttonPressed"]);
		okButton->setColor(buttonColor); okButton->setHoverColor(white);
		okButton->setPosition(316, 287); okButton->align(Text::LOVE_ALIGN_LEFT); okButton->adjustSize();

		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		pause->show();

		// settings menu
		settings = new Menu(defaultFont, white);
		settings->setSize((int)images["settingsBackground"]->getWidth(), (int)images["settingsBackground"]->getHeight());
		settings->setBackground(images["settingsBackground"]);

		generalTab = settings->addButton("CORE_TAB_GENERAL", "General");
		generalTab->setDefaultImage(images["tabActive"]);
		generalTab->setPosition(45,25); generalTab->align(Text::LOVE_ALIGN_CENTER); generalTab->adjustSize();

		videoTab = settings->addButton("CORE_TAB_VIDEO", "Video");
		videoTab->setDefaultImage(images["tabDefault"]); videoTab->setHoverImage(images["tabHover"]);
		videoTab->setPosition(105,25); videoTab->align(Text::LOVE_ALIGN_CENTER); videoTab->adjustSize();

		audioTab = settings->addButton("CORE_TAB_AUDIO", "Audio");
		audioTab->setDefaultImage(images["tabDefault"]); audioTab->setHoverImage(images["tabHover"]);
		audioTab->setPosition(165,25); audioTab->align(Text::LOVE_ALIGN_CENTER); audioTab->adjustSize();

		pathsTab = settings->addButton("CORE_TAB_PATHS", "Paths");
		pathsTab->setDefaultImage(images["tabDefault"]); pathsTab->setHoverImage(images["tabHover"]);
		pathsTab->setPosition(225,25); pathsTab->align(Text::LOVE_ALIGN_CENTER); pathsTab->adjustSize();

		label = settings->addLabel("Settings");
		label->setPosition(37, 65); label->setFont(titleFont); label->adjustSize();

		label = settings->addImage(images["line"]);
		label->setPosition(37, 80);

		settingsGeneral = settings->addMenu(Menu::LOVE_MENU_VERTICAL);
		settingsGeneral->setPosition(37,90); settingsGeneral->setSize(357,370);

		label = settingsGeneral->addMultilineLabel("General settings go here, like\n\"copy to game folder\"\n\"# of console lines\"\netc..");
		label->align(Text::LOVE_ALIGN_LEFT);
		label->setPosition(0, 0);

		settingsGeneral->show();

		settingsVideo = settings->addMenu(Menu::LOVE_MENU_VERTICAL);
		settingsVideo->setPosition(37,90); settingsVideo->setSize(357,370);

		settingsVideoFullscreen = settingsVideo->addCheckBox("LOVE_CORE_SETTINGS_VIDEO_FULLSCREEN", "  Fullscreen");
		settingsVideoFullscreen->setDefaultImage(images["checkBoxDefault"]); settingsVideoFullscreen->setHoverImage(images["checkBoxHover"]); settingsVideoFullscreen->setMarkedImage(images["checkBoxMarked"]);
		settingsVideoFullscreen->setColor(buttonColor); settingsVideoFullscreen->setHoverColor(white);  
		settingsVideoFullscreen->setPosition(24,11); settingsVideoFullscreen->adjustSize();

		settingsVideoVSync = settingsVideo->addCheckBox("CORE_SETTINGS_VIDEO_VSYNC", "  Vertical Sync (recommended)");
		settingsVideoVSync->setDefaultImage(images["checkBoxDefault"]); settingsVideoVSync->setHoverImage(images["checkBoxHover"]); settingsVideoVSync->setMarkedImage(images["checkBoxMarked"]);
		settingsVideoVSync->setColor(buttonColor); settingsVideoVSync->setHoverColor(white);  
		settingsVideoVSync->setPosition(24,36); settingsVideoVSync->adjustSize();

		label = settingsVideo->addImage(images["line"]);
		label->setPosition(0, 60);

		label = settingsVideo->addLabel("Default resolution");
		label->setPosition(24, 81);

		settingsVideoResolution = settingsVideo->addDropDown("CORE_SETTINGS_VIDEO_RESOLUTION");
		settingsVideoResolution->setBackgroundImage(images["dropDownBackground"]);
		settingsVideoResolution->setButtonImage(images["dropDownButton"]); settingsVideoResolution->setButtonHoverImage(images["dropDownButtonHover"]); settingsVideoResolution->setButtonPressedImage(images["dropDownButtonPressed"]);
		settingsVideoResolution->setListBackgroundColor(dropDownBack); settingsVideoResolution->setBorderColor(dropDownBorder);
		settingsVideoResolution->setHoverBackgroundColor(dropDownSelect); settingsVideoResolution->setHoverColor(dropDownSelectColor);
		settingsVideoResolution->setSelectedBackgroundColor(dropDownSelect); settingsVideoResolution->setSelectedColor(dropDownSelectColor);
		settingsVideoResolution->setPosition(24, 100); settingsVideoResolution->setPadding(5); settingsVideoResolution->setSpacing(5); settingsVideoResolution->adjustSize();
		settingsVideoResolution->setBorderSize(1); settingsVideoResolution->closeOnSelect(true);
		settingsVideoResolution->add("1280x1024");
		settingsVideoResolution->add("1024x768");
		settingsVideoResolution->add("800x600");
		settingsVideoResolution->add("640x480");
		settingsVideoResolution->add("320x240");
		settingsVideoResolution->setSelected(2);

		label = settingsVideo->addLabel("Information");
		label->setPosition(0, 180); label->setFont(titleFont); label->adjustSize();

		label = settingsVideo->addImage(images["line"]);
		label->setPosition(0, 195);

		label = settingsVideo->addLabel("How do I gett'd information?");
		label->setPosition(10, 215);
		label->align(Text::LOVE_ALIGN_LEFT);

		settingsVideo->show();

		settingsAudio = settings->addMenu(Menu::LOVE_MENU_VERTICAL);
		settingsAudio->setPosition(37,90); settingsAudio->setSize(357,370);

		label = settingsAudio->addLabel("Music Volume");
		label->setPosition(24, 13);

		settingsAudioMusic = settingsAudio->addSlider("CORE_SETTINGS_AUDIO_MUSIC", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsAudioMusic->setBackgroundImage(images["sliderBar"]); settingsAudioMusic->setMarkerImage(images["slider"]); settingsAudioMusic->adjustSize();
		settingsAudioMusic->setPosition(140, 11); settingsAudioMusic->setBorderSize(0);

		label = settingsAudio->addLabel("Sound Volume");
		label->setPosition(24, 43);

		settingsAudioSound = settingsAudio->addSlider("CORE_SETTINGS_AUDIO_SOUND", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsAudioSound->setBackgroundImage(images["sliderBar"]); settingsAudioSound->setMarkerImage(images["slider"]); settingsAudioSound->adjustSize();
		settingsAudioSound->setPosition(140, 41); settingsAudioSound->setBorderSize(0);

		settingsAudioMute = settingsAudio->addCheckBox("CORE_SETTINGS_AUDIO_MUTE", "  Mute");
		settingsAudioMute->setDefaultImage(images["checkBoxDefault"]); settingsAudioMute->setHoverImage(images["checkBoxHover"]); settingsAudioMute->setMarkedImage(images["checkBoxMarked"]);
		settingsAudioMute->setColor(buttonColor); settingsAudioMute->setHoverColor(white);  
		settingsAudioMute->setPosition(24,71); settingsAudioMute->adjustSize();

		label = settingsAudio->addImage(images["line"]);
		label->setPosition(0, 92);

		label = settingsAudio->addLabel("Audio quality");
		label->setPosition(24, 112);

		settingsAudioQuality = settingsAudio->addDropDown("CORE_SETTINGS_AUDIO_QUALITY");
		settingsAudioQuality->setBackgroundImage(images["dropDownBackground"]);
		settingsAudioQuality->setButtonImage(images["dropDownButton"]); settingsAudioQuality->setButtonHoverImage(images["dropDownButtonHover"]); settingsAudioQuality->setButtonPressedImage(images["dropDownButtonPressed"]);
		settingsAudioQuality->setListBackgroundColor(dropDownBack); settingsAudioQuality->setBorderColor(dropDownBorder);
		settingsAudioQuality->setHoverBackgroundColor(dropDownSelect); settingsAudioQuality->setHoverColor(dropDownSelectColor);
		settingsAudioQuality->setSelectedBackgroundColor(dropDownSelect); settingsAudioQuality->setSelectedColor(dropDownSelectColor);
		settingsAudioQuality->setPosition(24, 131); settingsAudioQuality->setPadding(5); settingsAudioQuality->setSpacing(5); settingsAudioQuality->adjustSize();
		settingsAudioQuality->setBorderSize(1); settingsAudioQuality->closeOnSelect(true);
		settingsAudioQuality->add("44100 kHz (high)");
		settingsAudioQuality->add("22050 kHz");
		settingsAudioQuality->add("0 kHz (impossible)");

		label = settingsAudio->addLabel("Latency");
		label->setPosition(24, 165);

		settingsAudioLatency = settingsAudio->addDropDown("CORE_SETTINGS_AUDIO_LATENCY");
		settingsAudioLatency->setBackgroundImage(images["dropDownBackground"]);
		settingsAudioLatency->setButtonImage(images["dropDownButton"]); settingsAudioLatency->setButtonHoverImage(images["dropDownButtonHover"]); settingsAudioLatency->setButtonPressedImage(images["dropDownButtonPressed"]);
		settingsAudioLatency->setListBackgroundColor(dropDownBack); settingsAudioLatency->setBorderColor(dropDownBorder);
		settingsAudioLatency->setHoverBackgroundColor(dropDownSelect); settingsAudioLatency->setHoverColor(dropDownSelectColor);
		settingsAudioLatency->setSelectedBackgroundColor(dropDownSelect); settingsAudioLatency->setSelectedColor(dropDownSelectColor);
		settingsAudioLatency->setPosition(24, 184); settingsAudioLatency->setPadding(5); settingsAudioLatency->setSpacing(5); settingsAudioLatency->adjustSize();
		settingsAudioLatency->setBorderSize(1); settingsAudioLatency->closeOnSelect(true);
		settingsAudioLatency->add("2048 ms");
		settingsAudioLatency->add("1024 ms");
		settingsAudioLatency->add("512 ms");

		settingsAudio->show();

		settingsPaths = settings->addMenu(Menu::LOVE_MENU_VERTICAL);
		settingsPaths->setPosition(37,90); settingsPaths->setSize(357,370);

		label = settingsPaths->addLabel("Configuration file");
		label->setPosition(0, 13);

		settingsPathsConfig = settingsPaths->addTextField("CORE_SETTINGS_PATHS_CONFIG", "../../data/love.config");
		settingsPathsConfig->setBackgroundImage(images["dropDownBackground"]); settingsPathsConfig->adjustSize();
		settingsPathsConfig->setBorderColor(dropDownBorder); settingsPathsConfig->setBorderSize(1);
		settingsPathsConfig->setColor(buttonColor); settingsPathsConfig->setActiveColor(white);
		settingsPathsConfig->setPosition(0, 30);

		label = settingsPaths->addLabel("Resource file");
		label->setPosition(0, 63);

		settingsPathsResource = settingsPaths->addTextField("CORE_SETTINGS_PATHS_RESOURCE", "../../data/love.data");
		settingsPathsResource->setBackgroundImage(images["dropDownBackground"]); settingsPathsResource->adjustSize();
		settingsPathsResource->setBorderColor(dropDownBorder); settingsPathsResource->setBorderSize(1);
		settingsPathsResource->setColor(buttonColor); settingsPathsResource->setActiveColor(white);
		settingsPathsResource->setPosition(0, 80);

		label = settingsPaths->addLabel("Game directory");
		label->setPosition(0, 113);

		settingsPathsGamedir = settingsPaths->addTextField("CORE_SETTINGS_PATHS_GAMEDIR", "../../data/games/");
		settingsPathsGamedir->setBackgroundImage(images["dropDownBackground"]); settingsPathsGamedir->adjustSize();
		settingsPathsGamedir->setBorderColor(dropDownBorder); settingsPathsGamedir->setBorderSize(1);
		settingsPathsGamedir->setColor(buttonColor); settingsPathsGamedir->setActiveColor(white);
		settingsPathsGamedir->setPosition(0, 130);

		settingsPaths->show();

		button = settings->addButton("CORE_SETTINGS_CANCEL", "  Cancel");
		button->setDefaultImage(images["buttonDefault"]); button->setHoverImage(images["buttonHover"]); button->setPressedImage(images["buttonPressed"]);
		button->setColor(quitColor); button->setHoverColor(white);  
		button->setPosition(24, 483); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

		button = settings->addButton("CORE_SETTINGS_OK", "  Ok");
		button->setDefaultImage(images["buttonDefault"]); button->setHoverImage(images["buttonHover"]); button->setPressedImage(images["buttonPressed"]);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(316, 483); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

		settings->setX( (core->display->getWidth() / 2) - (settings->getWidth() / 2) );
		settings->setY( (core->display->getHeight() / 2) - (settings->getHeight() / 2) );

		settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
		settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
		settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());

		settings->show();

		return load();
	}

	int UIGame::load()
	{
		this->loaded = true;
		return LOVE_OK;
	}

	void UIGame::unload()
	{
		this->loaded = false;
	}

	void UIGame::render()
	{
		if(!(mode == MODE_ERROR) && previous != 0)
			previous->render();
	}

	void UIGame::update(float dt)
	{
		//don't update the previous game
	}

	void UIGame::reloadGraphics()
	{
		//errorBackground->reload();
		//pauseBackground->reload();
		map<string, pAbstractImage>::iterator iter;
		for(iter = images.begin(); iter != images.end(); iter++)
		{
			iter->second->reload();
		}

		titleFont->reload();
		subtitleFont->reload();
		defaultFont->reload();

		pauseFont->reload();
		if(!(mode == MODE_ERROR) && previous != 0)
			previous->reloadGraphics();
	}

	void UIGame::showError(const char * text)
	{
		// Why are you re-erroring yourself? Tsk tsk, little one.
		if(mode == MODE_ERROR) return;

		// Entering error mode ...
		mode = MODE_ERROR;

		errorText->setCaption(text);

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		top->clear();
		top->add(error);
		core->gui->add(top);

		core->current->suspend();
		previous = core->current;
		core->current = this;
	}

	void UIGame::showPause()
	{
		if(previous != 0) return; //if we are already paused

		top->clear();
		top->add(pause);
		core->gui->add(top);

		core->current->suspend();
		previous = core->current;
		core->current = this;

		//grapical stuff
		tabPause->setDefaultImage(images["tabActive"]);
		tabPause->setHoverImage(images["tabActive"]);
		tabSettings->setDefaultImage(images["tabDefault"]);
		tabSettings->setHoverImage(images["tabHover"]);
		okButton->setCaption("  Resume");
		cancelButton->setCaption("  Quit");
		settingsMenu->hide();
		pauseMenu->show();

		pauseLabel->setCaption("Game paused"); pauseLabel->adjustSize();
		if(previous->config->getThumb() != 0)
			thumbLabel->setBackgroundImage(previous->config->getThumb());
		else
			thumbLabel->setBackgroundImage(images["imageDefault"]);
		thumbLabel->adjustSize();
		gameTitle->setCaption(previous->config->getTitle());
		gameTitle->adjustSize();
		gameCreator->setCaption(string("by ") + previous->config->getAuthor());
		gameCreator->adjustSize();
		gameCreator->setY(8 + gameTitle->getHeight());

		mode = MODE_PAUSE;
	}

	void UIGame::hidePause()
	{
		if(mode == MODE_SETTINGS || mode == MODE_MENUPAUSE)
			hideSettings();
		else
			resumeGame();
	}

	void UIGame::showSettings()
	{
		if(core->config->isBool("fullscreen"))
		{
			settingsFullscreen->setMarked(core->config->getBool("fullscreen"));
			settingsVideoFullscreen->setMarked(core->config->getBool("fullscreen"));
		}
		if(core->config->isBool("vsync"))
		{
			settingsVSync->setMarked(core->config->getBool("vsync"));
			settingsVideoVSync->setMarked(core->config->getBool("vsync"));
		}
		if(core->config->isString("default_resolution"))
		{
			string temp = core->config->getString("default_resolution");
			for(int i = 0; i < settingsVideoResolution->getNumberOfElements(); i++)
			{
				if(settingsVideoResolution->getElementAt(i) == temp)
					settingsVideoResolution->setSelected(i);
			}
		}
		if(core->config->isInt("sound_volume"))
		{
			settingsSound->setValue(core->config->getInt("sound_volume"));
			settingsAudioSound->setValue(core->config->getInt("sound_volume"));
		}
		if(core->config->isInt("music_volume"))
		{
			settingsMusic->setValue(core->config->getInt("music_volume"));
			settingsAudioMusic->setValue(core->config->getInt("music_volume"));
		}
		if(core->config->isBool("mute"))
		{
			settingsMute->setMarked(core->config->getBool("mute"));
			settingsAudioMute->setMarked(core->config->getBool("mute"));
		}
		if(core->config->isInt("audio_quality"))
		{
			int num = core->config->getInt("audio_quality");
			for(int i = 0; i < settingsAudioQuality->getNumberOfElements(); i++)
			{
				string temp = settingsAudioQuality->getElementAt(i);
				temp = temp.substr(0, temp.find(' '));
				if(num == atoi(temp.c_str()))
					settingsAudioQuality->setSelected(i);
			}
		}
		if(core->config->isInt("audio_latency"))
		{
			int num = core->config->getInt("audio_latency");
			for(int i = 0; i < settingsAudioLatency->getNumberOfElements(); i++)
			{
				string temp = settingsAudioLatency->getElementAt(i);
				temp = temp.substr(0, temp.find(' '));
				if(num == atoi(temp.c_str()))
					settingsAudioLatency->setSelected(i);
			}
		}
		if(core->config->isString("config_path"))
		{
			settingsPathsConfig->setText(core->config->getString("config_path"));
		}
		if(core->config->isString("resource_path"))
		{
			settingsPathsResource->setText(core->config->getString("resource_path"));
		}
		if(core->config->isString("gamedir"))
		{
			settingsPathsGamedir->setText(core->config->getString("gamedir"));
		}

		if(mode != MODE_PAUSE)
		{
			// the settings menu to display when pausing from the menu
			top->clear();
			top->add(settings);
			core->gui->add(top);

			core->current->suspend();
			previous = core->current;
			core->current = this;

			mode = MODE_MENUPAUSE;
		}
		else
		{
			tabPause->setDefaultImage(images["tabDefault"]);
			tabPause->setHoverImage(images["tabHover"]);
			tabSettings->setDefaultImage(images["tabActive"]);
			tabSettings->setHoverImage(images["tabActive"]);
			pauseLabel->setCaption("Settings");
			pauseLabel->adjustSize();
			okButton->setCaption("  Ok");
			cancelButton->setCaption("  Cancel");
			pauseMenu->hide();
			settingsMenu->show();
			mode = MODE_SETTINGS;
		}
	}

	void UIGame::hideSettings()
	{
		if(mode == MODE_SETTINGS)
		{
			tabPause->setDefaultImage(images["tabActive"]);
			tabPause->setHoverImage(images["tabActive"]);
			tabSettings->setDefaultImage(images["tabDefault"]);
			tabSettings->setHoverImage(images["tabHover"]);
			pauseLabel->setCaption("Game paused");
			pauseLabel->adjustSize();
			okButton->setCaption("  Resume");
			cancelButton->setCaption("  Quit");
			settingsMenu->hide();
			pauseMenu->show();
			mode = MODE_PAUSE;
		}
		else // mode == MODE_MENUPAUSE
		{
			if(generalTab->getDefaultImage() != images["tabActive"])
			{
				if(videoTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
					videoTab->setDefaultImage(images["tabDefault"]); videoTab->setHoverImage(images["tabHover"]);
				}
				else if(audioTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
					audioTab->setDefaultImage(images["tabDefault"]); audioTab->setHoverImage(images["tabHover"]);
				}
				else if(pathsTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());
					pathsTab->setDefaultImage(images["tabDefault"]); pathsTab->setHoverImage(images["tabHover"]);
				}

				settings->add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsGeneral).get());
				generalTab->setDefaultImage(images["tabActive"]); generalTab->setHoverImage(images["tabActive"]);
			}

			resumeGame();
		}
	}

	bool UIGame::isPaused()
	{
		if(mode != MODE_DEFAULT)
			return true;
		else
			return false;

		/*if(previous != 0) //this means that it is paused
			return true;
		else
			return false;*/
	}

	void UIGame::eventFired(pEvent e)
	{
		if(e->getType() == LOVE_TYPE_GUI_EVENT)
		{
			pGUIEvent pme = dynamic_pointer_cast<GUIEvent, Event>(e);
			if(strcmp(pme->getName(), "CORE_ERROR_CONTINUE") == 0)
				resumeGame();
			if(strcmp(pme->getName(), "CORE_ERROR_RESTART") == 0)
				reloadGame();
			if(strcmp(pme->getName(), "CORE_ERROR_QUIT") == 0)
				quitGame();
			else if(strcmp(pme->getName(), "CORE_SETTINGS_OK") == 0)
				saveSettings();
			else if(strcmp(pme->getName(), "CORE_SETTINGS_CANCEL") == 0)
				hideSettings();
			else if(strcmp(pme->getName(), "CORE_OK") == 0)
				if(mode == MODE_SETTINGS)
					saveSettings();
				else
					resumeGame();
			else if(strcmp(pme->getName(), "CORE_CANCEL") == 0)
				if(mode == MODE_SETTINGS)
					hideSettings();
				else
					quitGame();
			else if(strcmp(pme->getName(), "CORE_TAB_PAUSE") == 0)
			{
				if(mode != MODE_PAUSE)
					hideSettings();
			}
			else if(strcmp(pme->getName(), "CORE_TAB_SETTINGS") == 0)
			{
				if(mode != MODE_SETTINGS)
					showSettings();
			}
			else if(strcmp(pme->getName(), "CORE_TAB_GENERAL") == 0)
			{
				if(generalTab->getDefaultImage() == images["tabActive"])
				{
					return;
				}
				else if(videoTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
					videoTab->setDefaultImage(images["tabDefault"]); videoTab->setHoverImage(images["tabHover"]);
				}
				else if(audioTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
					audioTab->setDefaultImage(images["tabDefault"]); audioTab->setHoverImage(images["tabHover"]);
				}
				else if(pathsTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());
					pathsTab->setDefaultImage(images["tabDefault"]); pathsTab->setHoverImage(images["tabHover"]);
				}

				settings->add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsGeneral).get());
				generalTab->setDefaultImage(images["tabActive"]); generalTab->setHoverImage(images["tabActive"]);
			}
			else if(strcmp(pme->getName(), "CORE_TAB_VIDEO") == 0)
			{
				if(videoTab->getDefaultImage() == images["tabActive"])
				{
					return;
				}
				else if(generalTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsGeneral).get());
					generalTab->setDefaultImage(images["tabDefault"]); generalTab->setHoverImage(images["tabHover"]);
				}
				else if(audioTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
					audioTab->setDefaultImage(images["tabDefault"]); audioTab->setHoverImage(images["tabHover"]);
				}
				else if(pathsTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());
					pathsTab->setDefaultImage(images["tabDefault"]); pathsTab->setHoverImage(images["tabHover"]);
				}

				settings->add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
				videoTab->setDefaultImage(images["tabActive"]); videoTab->setHoverImage(images["tabActive"]);
			}
			else if(strcmp(pme->getName(), "CORE_TAB_AUDIO") == 0)
			{
				if(audioTab->getDefaultImage() == images["tabActive"])
				{
					return;
				}
				else if(generalTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsGeneral).get());
					generalTab->setDefaultImage(images["tabDefault"]); generalTab->setHoverImage(images["tabHover"]);
				}
				else if(videoTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
					videoTab->setDefaultImage(images["tabDefault"]); videoTab->setHoverImage(images["tabHover"]);
				}
				else if(pathsTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());
					pathsTab->setDefaultImage(images["tabDefault"]); pathsTab->setHoverImage(images["tabHover"]);
				}

				settings->add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
				audioTab->setDefaultImage(images["tabActive"]); audioTab->setHoverImage(images["tabActive"]);
			}
			else if(strcmp(pme->getName(), "CORE_TAB_PATHS") == 0)
			{
				if(pathsTab->getDefaultImage() == images["tabActive"])
				{
					return;
				}
				else if(generalTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsGeneral).get());
					generalTab->setDefaultImage(images["tabDefault"]); generalTab->setHoverImage(images["tabHover"]);
				}
				else if(videoTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsVideo).get());
					videoTab->setDefaultImage(images["tabDefault"]); videoTab->setHoverImage(images["tabHover"]);
				}
				else if(audioTab->getDefaultImage() == images["tabActive"])
				{
					settings->remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsAudio).get());
					audioTab->setDefaultImage(images["tabDefault"]); audioTab->setHoverImage(images["tabHover"]);
				}

				settings->add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(settingsPaths).get());
				pathsTab->setDefaultImage(images["tabActive"]); pathsTab->setHoverImage(images["tabActive"]);
			}
		}
	}

	void UIGame::keyPressed(int key)
	{
		if(key == LOVE_KEY_ESCAPE && isPaused())
			hidePause();
	}

	void UIGame::keyReleased(int key)
	{}

	void UIGame::displayModeChanged()
	{
		top->setSize(core->display->getCurrentDisplayMode().getWidth(),core->display->getCurrentDisplayMode().getHeight());

		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		error->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		settings->setX( (core->display->getWidth() / 2) - (settings->getWidth() / 2) );
		settings->setY( (core->display->getHeight() / 2) - (settings->getHeight() / 2) );

		if(!(mode == MODE_ERROR) && previous != 0)
			previous->displayModeChanged();

		reloadGraphics();
	}
}
