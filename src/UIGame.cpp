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
		core->config->addInt("settings_resolution", (float)settingsResolution->getSelected());
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
		top->setOpaque(false);

		// resources
		errorBackground.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/error_background.png")));
		errorBackground->load();
		pauseBackground.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/pause_background.png")));
		pauseBackground->load();

		buttonDefault.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/button_default.png")));
		buttonDefault->load();
		buttonHover.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/button_hover.png")));
		buttonHover->load();
		buttonPressed.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/button_pressed.png")));
		buttonPressed->load();
		buttonQuit.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/button_quit.png")));
		buttonQuit->load();

		line.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/line.png")));
		line->load();

		tabDefault.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/tab_default.png")));
		tabDefault->load();
		tabHover.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/tab_hover.png")));
		tabHover->load();
		tabActive.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/tab_active.png")));
		tabActive->load();

		imageBackground.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/image_background.png")));
		imageBackground->load();
		imageDefault.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/gui/thumb_default.png")));
		imageDefault->load();

		titleFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/VeraBd.ttf"), 10));
		titleFont->load();
		subtitleFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/Vera.ttf"), 10));
		subtitleFont->load();
		defaultFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/Vera.ttf"), 8));
		defaultFont->load();
		
		pauseFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 14));
		pauseFont->load();


		// temp variables
		pAbstractColor black(new Color(0x000000));
		pAbstractColor white(new Color(0xFFFFFF));
		pAbstractColor buttonColor(new Color(255,255,255,200));
		pAbstractColor quitColor(new Color(255,255,255,150));

		pLabel label;
		pButton button;


		// error box
		error = new Menu(defaultFont, white);
		error->setSize((int)errorBackground->getWidth(), (int)errorBackground->getHeight());
		error->setBackground(&errorBackground);
		
		label = error->addLabel("An error has occurred");
		label->setPosition(24, 69); label->setFont(&titleFont); label->adjustSize();
		
		label = error->addImage(&line);
		label->setPosition(24, 87);
		
		errorText = error->addMultilineLabel("");
		errorText->setPosition(24, 102); errorText->setSize(358, 202); errorText->align(Text::LOVE_ALIGN_LEFT); errorText->valign(Text::LOVE_ALIGN_TOP);
		
		button = error->addButton("CORE_ERROR_RESTART", "  Restart");
		button->setDefaultImage(&buttonDefault); button->setHoverImage(&buttonHover); button->setPressedImage(&buttonPressed);
		button->setColor(&buttonColor); button->setHoverColor(&white);
		button->setPosition(141, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_CONTINUE", "  Continue");
		button->setDefaultImage(&buttonDefault); button->setHoverImage(&buttonHover); button->setPressedImage(&buttonPressed);
		button->setColor(&buttonColor); button->setHoverColor(&white);
		button->setPosition(230, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();
		
		button = error->addButton("CORE_ERROR_QUIT", "  Quit");
		button->setDefaultImage(&buttonQuit); button->setHoverImage(&buttonHover); button->setPressedImage(&buttonPressed);
		button->setColor(&buttonColor); button->setHoverColor(&white);
		button->setPosition(319, 333); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

		error->show();


		// new pause menu
		pause = new Menu(defaultFont, white);
		pause->setSize((int)pauseBackground->getWidth(), (int)pauseBackground->getHeight());
		pause->setBackground(&pauseBackground);

		pauseLabel = pause->addLabel("Game paused");
		pauseLabel->setPosition(33, 64); pauseLabel->setFont(&titleFont); pauseLabel->adjustSize();

		label = pause->addImage(&line);
		label->setPosition(33, 81);

		tabPause = pause->addButton("CORE_TAB_PAUSE", "Pause");
		tabPause->setDefaultImage(&tabActive);
		tabPause->setPosition(45,25); tabPause->align(Text::LOVE_ALIGN_CENTER); tabPause->adjustSize();

		tabSettings = pause->addButton("CORE_TAB_SETTINGS", "Settings");
		tabSettings->setDefaultImage(&tabDefault); tabSettings->setHoverImage(&tabHover);
		tabSettings->setPosition(105,25); tabSettings->align(Text::LOVE_ALIGN_CENTER); tabSettings->adjustSize();

		label = pause->addImage(&imageBackground);
		label->setPosition(33, 100);

		thumbLabel = pause->addImage(&imageDefault);
		thumbLabel->setPosition(37, 104);

		gameTitle = pause->addMultilineLabel("Game Title", 143);
		gameTitle->setPosition(248, 100); gameTitle->align(Text::LOVE_ALIGN_LEFT); gameTitle->setFont(&subtitleFont); gameTitle->adjustSize();

		gameCreator = pause->addMultilineLabel("by Someone", 143);
		gameCreator->setPosition(248, 108 + gameTitle->getHeight()); gameCreator->align(Text::LOVE_ALIGN_LEFT); gameCreator->adjustSize();

		pButton qbutton = pause->addButton("CORE_QUIT", "  Quit");
		qbutton->setDefaultImage(&buttonDefault); qbutton->setHoverImage(&buttonHover); qbutton->setPressedImage(&buttonPressed);
		qbutton->setColor(&quitColor); qbutton->setHoverColor(&white);
		qbutton->setPosition(24, 287); qbutton->align(Text::LOVE_ALIGN_LEFT); qbutton->adjustSize();

		button = pause->addButton("CORE_RESUME", "  Resume");
		button->setDefaultImage(&buttonDefault); button->setHoverImage(&buttonHover); button->setPressedImage(&buttonPressed);
		button->setColor(&buttonColor); button->setHoverColor(&white);
		button->setPosition(316, 287); button->align(Text::LOVE_ALIGN_LEFT); button->adjustSize();

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
		buttonDefault->reload();
		buttonHover->reload();
		buttonPressed->reload();
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
		tabPause->setDefaultImage(&tabActive);
		tabPause->setHoverImage(0);
		tabSettings->setDefaultImage(&tabDefault);
		tabSettings->setHoverImage(&tabHover);

		pauseLabel->setCaption("Game paused"); pauseLabel->adjustSize();
		if(previous->config->getThumb() != 0)
		{
			thumbLabel->setBackground(&pAbstractImage(previous->config->getThumb())); thumbLabel->adjustSize();
		}
		else
			thumbLabel->setBackground(&imageDefault); thumbLabel->adjustSize();
		gameTitle->setCaption(previous->config->getTitle());
		gameTitle->adjustSize();
		gameCreator->setCaption(string("by ") + previous->config->getAuthor());
		gameCreator->adjustSize();
		gameCreator->setY(108 + gameTitle->getHeight());

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
		if(mode != MODE_PAUSE)
		{
			// the settings menu to display when pausing from the menu
			mode = MODE_MENUPAUSE;
		}
		else
		{
			tabPause->setDefaultImage(&tabDefault);
			tabPause->setHoverImage(&tabHover);
			tabSettings->setDefaultImage(&tabActive);
			tabSettings->setHoverImage(0);
			pauseLabel->setCaption("Settings");
			pauseLabel->adjustSize();
			mode = MODE_SETTINGS;
		}
	}

	void UIGame::hideSettings()
	{
		if(mode == MODE_SETTINGS)
		{
			tabPause->setDefaultImage(&tabActive);
			tabPause->setHoverImage(0);
			tabSettings->setDefaultImage(&tabDefault);
			tabSettings->setHoverImage(&tabHover);
			pauseLabel->setCaption("Game paused");
			pauseLabel->adjustSize();
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
			else if(strcmp(pme->getName(), "CORE_RESUME") == 0)
				resumeGame();
			else if(strcmp(pme->getName(), "CORE_SAVE") == 0)
				printf("save");
			else if(strcmp(pme->getName(), "CORE_LOAD") == 0)
				printf("load");
			else if(strcmp(pme->getName(), "CORE_QUIT") == 0)
				quitGame();
			else if(strcmp(pme->getName(), "CORE_TAB_PAUSE") == 0)
				hideSettings();
			else if(strcmp(pme->getName(), "CORE_TAB_SETTINGS") == 0)
				showSettings();
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
