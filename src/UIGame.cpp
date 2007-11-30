#include "UIGame.h"

#include "love_keys.h"
#include "Core.h"
#include "love.h"
#include "AbstractDisplay.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"

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
		core->startGame("love-system-menu", false);

		// Exits error mode.
		mode = MODE_DEFAULT;
	}

	void UIGame::saveSettings()
	{
		core->config->addBool("settings_fullscreen", settingsFullscreen->isMarked());
		core->config->addBool("settings_vsync", settingsVSync->isMarked());
		if(settingsResolution->getSelected() >= 0)
			core->config->addString("settings_resolution", settingsResolution->getSelectedElement());
		core->config->addInt("settings_sound", (float)settingsSound->getValue());
		core->config->addInt("settings_music", (float)settingsMusic->getValue());
		core->config->write();
		hideSettings();
	}

	UIGame::UIGame() : mode(MODE_DEFAULT)
	{
		previous = 0;
		error = 0;
		pause = 0;
		top = 0;
		loaded = false;
	}

	UIGame::~UIGame()
	{
		if(error != 0) delete error;
		if(pause != 0) delete pause;
		if(top != 0) delete top;
	}

	int UIGame::init()
	{
		top = new gcn::Container();
		top->setDimension(gcn::Rectangle(0, 0, core->display->getCurrentDisplayMode().getWidth(), core->display->getCurrentDisplayMode().getHeight()));
		top->setBaseColor(gcn::Color(99,170,218,127));
		top->setOpaque(true);

		// resources
		errorBackground = core->graphics->getImage("data/gui/error_background.png");
		errorBackground->load();
		pauseBackground = core->graphics->getImage("data/gui/pause_background.png");
		pauseBackground->load();

		buttonDefault = core->graphics->getImage("data/gui/button_default.png");
		buttonDefault->load();
		buttonHover = core->graphics->getImage("data/gui/button_hover.png");
		buttonHover->load();
		buttonPressed = core->graphics->getImage("data/gui/button_pressed.png");
		buttonPressed->load();
		buttonQuit = core->graphics->getImage("data/gui/button_quit.png");
		buttonQuit->load();
		checkBoxDefault = core->graphics->getImage("data/gui/checkbox_default.png");
		checkBoxDefault->load();
		checkBoxHover = core->graphics->getImage("data/gui/checkbox_hover.png");
		checkBoxHover->load();
		checkBoxMarked = core->graphics->getImage("data/gui/checkbox_marked.png");
		checkBoxMarked->load();
		sliderBar = core->graphics->getImage("data/gui/slider_bar.png");
		sliderBar->load();
		slider = core->graphics->getImage("data/gui/slider.png");
		slider->load();
		dropDownBackground = core->graphics->getImage("data/gui/dropdown_background.png");
		dropDownBackground->load();
		dropDownButton = core->graphics->getImage("data/gui/dropdown_button.png");
		dropDownButton->load();

		line = core->graphics->getImage("data/gui/line.png");
		line->load();

		tabDefault = core->graphics->getImage("data/gui/tab_default.png");
		tabDefault->load();
		tabHover = core->graphics->getImage("data/gui/tab_hover.png");
		tabHover->load();
		tabActive = core->graphics->getImage("data/gui/tab_active.png");
		tabActive->load();

		imageBackground = core->graphics->getImage("data/gui/image_background.png");
		imageBackground->load();
		imageDefault = core->graphics->getImage("data/gui/thumb_default.png");
		imageDefault->load();

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
		error->setSize((int)errorBackground->getWidth(), (int)errorBackground->getHeight());
		error->setBackground(errorBackground);
		
		label = error->addLabel("An error has occurred");
		label->setPosition(24, 69); label->setFont(titleFont); label->adjustSize();
		
		label = error->addImage(line);
		label->setPosition(24, 87);
		
		errorText = error->addMultilineLabel("");
		errorText->setPosition(24, 102); errorText->setSize(358, 202); errorText->align(Text::LOVE_ALIGN_LEFT); errorText->valign(Text::LOVE_ALIGN_TOP);
		
		button = error->addButton("CORE_ERROR_RESTART", "  Restart");
		button->setDefaultImage(buttonDefault); button->setHoverImage(buttonHover); button->setPressedImage(buttonPressed);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(141, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_CONTINUE", "  Continue");
		button->setDefaultImage(buttonDefault); button->setHoverImage(buttonHover); button->setPressedImage(buttonPressed);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(230, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_QUIT", "  Quit");
		button->setDefaultImage(buttonQuit); button->setHoverImage(buttonHover); button->setPressedImage(buttonPressed);
		button->setColor(buttonColor); button->setHoverColor(white);
		button->setPosition(319, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

		error->show();


		// new pause menu
		pause = new Menu(defaultFont, white);
		pause->setSize((int)pauseBackground->getWidth(), (int)pauseBackground->getHeight());
		pause->setBackground(pauseBackground);

		pauseLabel = pause->addLabel("Game paused");
		pauseLabel->setPosition(33, 64); pauseLabel->setFont(titleFont); pauseLabel->adjustSize();

		label = pause->addImage(line);
		label->setPosition(33, 81);

		tabPause = pause->addButton("CORE_TAB_PAUSE", "Pause");
		tabPause->setDefaultImage(tabActive);
		tabPause->setPosition(45,25); tabPause->align(Text::LOVE_ALIGN_CENTER); tabPause->adjustSize();

		tabSettings = pause->addButton("CORE_TAB_SETTINGS", "Settings");
		tabSettings->setDefaultImage(tabDefault); tabSettings->setHoverImage(tabHover);
		tabSettings->setPosition(105,25); tabSettings->align(Text::LOVE_ALIGN_CENTER); tabSettings->adjustSize();

		pauseMenu = pause->addMenu(AbstractMenu::LOVE_MENU_HORIZONTAL, 358, 167);
		pauseMenu->setPosition(33,100);

		label = pauseMenu->addImage(imageBackground);
		label->setPosition(0,0);

		thumbLabel = pauseMenu->addImage(imageDefault);
		thumbLabel->setPosition(4, 4);

		gameTitle = pauseMenu->addMultilineLabel("Game Title", 143);
		gameTitle->setPosition(215, 0); gameTitle->align(Text::LOVE_ALIGN_LEFT); gameTitle->setFont(subtitleFont); gameTitle->adjustSize();

		gameCreator = pauseMenu->addMultilineLabel("by Unknown", 143);
		gameCreator->setPosition(215, 8 + gameTitle->getHeight()); gameCreator->align(Text::LOVE_ALIGN_LEFT); gameCreator->adjustSize();

		pauseMenu->show();

		settingsMenu = pause->addMenu(AbstractMenu::LOVE_MENU_HORIZONTAL, 358, 167);
		settingsMenu->setPosition(33,100);

		settingsFullscreen = settingsMenu->addCheckBox("CORE_SETTINGS_FULLSCREEN", "  Fullscreen");
		settingsFullscreen->setDefaultImage(checkBoxDefault); settingsFullscreen->setHoverImage(checkBoxHover); settingsFullscreen->setMarkedImage(checkBoxMarked);
		settingsFullscreen->setColor(buttonColor); settingsFullscreen->setHoverColor(white);  
		settingsFullscreen->setPosition(24,8); settingsFullscreen->adjustSize();

		settingsVSync = settingsMenu->addCheckBox("CORE_SETTINGS_FULLSCREEN", "  Vertical Sync");
		settingsVSync->setDefaultImage(checkBoxDefault); settingsVSync->setHoverImage(checkBoxHover); settingsVSync->setMarkedImage(checkBoxMarked);
		settingsVSync->setColor(buttonColor); settingsVSync->setHoverColor(white);  
		settingsVSync->setPosition(24,33); settingsVSync->adjustSize();

		label = settingsMenu->addLabel("Resolution");
		label->setPosition(167, 8);

		settingsResolution = settingsMenu->addDropDown("CORE_SETTINGS_RESOLUTION");
		settingsResolution->setBackgroundImage(dropDownBackground); settingsResolution->setButton(dropDownButton);
		settingsResolution->setListBackgroundColor(dropDownBack); settingsResolution->setBorderColor(dropDownBorder);
		settingsResolution->setHoverBackgroundColor(dropDownSelect); settingsResolution->setHoverColor(dropDownSelectColor);
		settingsResolution->setSelectedBackgroundColor(dropDownSelect); settingsResolution->setSelectedColor(dropDownSelectColor);
		settingsResolution->setPosition(167, 30); settingsResolution->setPadding(5); settingsResolution->setSpacing(5); settingsResolution->adjustSize();
		settingsResolution->setBorderSize(1); settingsResolution->closeOnSelect(true);
		settingsResolution->add("1280x1024");
		settingsResolution->add("1024x768");
		settingsResolution->add("800x600");
		settingsResolution->add("640x480");
		settingsResolution->add("320x240");

		label = settingsMenu->addImage(line);
		label->setPosition(0, 60);

		label = settingsMenu->addLabel("Sound Volume");
		label->setPosition(24, 90); label->adjustSize();

		settingsSound = settingsMenu->addSlider("CORE_SETTINGS_SOUND", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsSound->setBackgroundImage(sliderBar); settingsSound->setMarkerImage(slider); settingsSound->adjustSize();
		settingsSound->setPosition(140, 90); settingsSound->setBorderSize(0);

		label = settingsMenu->addLabel("Music Volume");
		label->setPosition(24, 120); label->adjustSize();

		settingsMusic = settingsMenu->addSlider("CORE_SETTINGS_MUSIC", Slider::LOVE_SLIDER_HORIZONTAL, 0, 100);
		settingsMusic->setBackgroundImage(sliderBar); settingsMusic->setMarkerImage(slider); settingsMusic->adjustSize();
		settingsMusic->setPosition(140, 120); settingsMusic->setBorderSize(0);

		settingsMenu->hide();

		cancelButton = pause->addButton("CORE_CANCEL", "  Quit");
		cancelButton->setDefaultImage(buttonDefault); cancelButton->setHoverImage(buttonHover); cancelButton->setPressedImage(buttonPressed);
		cancelButton->setColor(quitColor); cancelButton->setHoverColor(white);  
		cancelButton->setPosition(24, 287); cancelButton->align(Text::LOVE_ALIGN_LEFT); cancelButton->adjustSize();

		okButton = pause->addButton("CORE_OK", "  Resume");
		okButton->setDefaultImage(buttonDefault); okButton->setHoverImage(buttonHover); okButton->setPressedImage(buttonPressed);
		okButton->setColor(buttonColor); okButton->setHoverColor(white);
		okButton->setPosition(316, 287); okButton->align(Text::LOVE_ALIGN_LEFT); okButton->adjustSize();

		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		pause->show();


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
		errorBackground->reload();
		pauseBackground->reload();
		buttonDefault->reload();
		buttonQuit->reload();
		buttonHover->reload();
		buttonPressed->reload();
		buttonQuit->reload();
		checkBoxDefault->reload();
		checkBoxHover->reload();
		checkBoxMarked->reload();
		sliderBar->reload();
		slider->reload();
		dropDownBackground->reload();
		dropDownButton->reload();
		line->reload();
		tabDefault->reload();
		tabHover->reload();
		tabActive->reload();
		imageBackground->reload();
		imageDefault->reload();

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
		tabPause->setDefaultImage(tabActive);
		tabPause->setHoverImage(tabActive);
		tabSettings->setDefaultImage(tabDefault);
		tabSettings->setHoverImage(tabHover);
		okButton->setCaption("  Resume");
		cancelButton->setCaption("  Quit");
		settingsMenu->hide();
		pauseMenu->show();

		pauseLabel->setCaption("Game paused"); pauseLabel->adjustSize();
		if(previous->config->getThumb() != 0)
			thumbLabel->setBackgroundImage(previous->config->getThumb());
		else
			thumbLabel->setBackgroundImage(imageDefault);
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
		{
			mode = MODE_DEFAULT;
			resumeGame();
		}
	}

	void UIGame::showSettings()
	{
		if(core->config->isBool("settings_fullscreen"))
			settingsFullscreen->setMarked(core->config->getBool("settings_fullscreen"));
		if(core->config->isBool("settings_vsync"))
			settingsVSync->setMarked(core->config->getBool("settings_vsync"));
		if(core->config->isInt("settings_sound"))
			settingsSound->setValue(core->config->getInt("settings_sound"));
		if(core->config->isInt("settings_music"))
			settingsMusic->setValue(core->config->getInt("settings_music"));
		if(core->config->isString("settings_resolution"))
		{
			string temp = core->config->getString("settings_resolution");
			for(int i = 0; i < settingsResolution->getNumberOfElements(); i++)
			{
				if(settingsResolution->getElementAt(i) == temp)
					settingsResolution->setSelected(i);
			}
		}
		if(mode != MODE_PAUSE)
		{
			// the settings menu to display when pausing from the menu
			mode = MODE_MENUPAUSE;
		}
		else
		{
			tabPause->setDefaultImage(tabDefault);
			tabPause->setHoverImage(tabHover);
			tabSettings->setDefaultImage(tabActive);
			tabSettings->setHoverImage(tabActive);
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
			tabPause->setDefaultImage(tabActive);
			tabPause->setHoverImage(tabActive);
			tabSettings->setDefaultImage(tabDefault);
			tabSettings->setHoverImage(tabHover);
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
			top->clear();
			core->gui->remove(top);
			mode = MODE_DEFAULT;
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

		if(!(mode == MODE_ERROR) && previous != 0)
			previous->displayModeChanged();
		reloadGraphics();
	}
}
