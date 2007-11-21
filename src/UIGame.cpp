#include "UIGame.h"

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
		errorMode = false;
	}

	void UIGame::reloadGame()
	{
		top->clear();
		core->gui->remove(top);

		// To Mike: Reloading will never change the display mode.
		//core->gui->displayModeChanged(); // to reset the gui

		core->current = previous;
		previous = 0;

		core->current->reload();
		printf("Reloaded: %s\n", core->current->getName().c_str());

		// Exits error mode.
		errorMode = false;
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
		errorMode = false;
	}

	UIGame::UIGame() : errorMode(false)
	{
		previous = 0;
		error = 0;
		warning = 0;
		pause = 0;
		top = 0;
		pauseMode = false;
	}

	UIGame::~UIGame()
	{
		if(error != 0) delete error;
		if(warning != 0) delete warning;
		if(pause != 0) delete pause;
		if(settings != 0) delete settings;
		if(top != 0) delete top;
	}

	int UIGame::init()
	{
		top = new gcn::Container();
		top->setDimension(gcn::Rectangle(0, 0, core->display->getCurrentDisplayMode().getWidth(), core->display->getCurrentDisplayMode().getHeight()));
		top->setOpaque(false);

		// resources
		errorWarning.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/warning.png")));
		errorWarning->load();
		errorError.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/error.png")));
		errorError->load();
		errorFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 8));
		errorFont->load();
		pauseFont.reset<AbstractFont>(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 14));
		pauseFont->load();
		pAbstractColor borderColor(new Color(0xe9e9e9));
		pAbstractColor black(new Color(0x000000));
		pAbstractColor white(new Color(0xFFFFFF));
		pAbstractColor slightlyWhite(new Color(255,255,255,200));

		// error box
		error = new Menu(errorFont, black);
		error->setSize(500,217); // so that we have something to start with
		error->setPadding(12);
		error->setColor(&black);
		error->setBackgroundColor(&slightlyWhite);
		error->stretchContent(true);
		error->addImage(&errorError)->align(Text::LOVE_ALIGN_LEFT);
		errorText = error->addMultilineLabel("");
		errorText->align(Text::LOVE_ALIGN_LEFT);
		error->addLabel("")->setHeight(20);
		pAbstractMenu nested = error->addMenu(Menu::LOVE_MENU_HORIZONTAL, 0, 40);
		nested->setSpacing(10);
		errorButton = nested->addButton("CORE_ERROR_CONTINUE", "Continue");
		errorButton->setBorderColor(&borderColor);
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		pButton tempb(nested->addButton("CORE_ERROR_RESTART", "Restart"));
		tempb->setBorderColor(&borderColor);
		tempb->setWidth(70);
		tempb->setBorderSize(1);
		tempb = nested->addButton("CORE_ERROR_QUIT", "Quit");
		tempb->setBorderColor(&borderColor);
		tempb->setWidth(70);
		tempb->setBorderSize(1);
		nested->adjustWidth();
		nested->adjustContent();
		error->show();
		// warning box
		warning = new Menu(errorFont, black);
		warning->setSize(356,217); // so that we have something to start with
		warning->setPadding(18);
		warning->setColor(&black);
		warning->setBackgroundColor(&slightlyWhite);
		warning->stretchContent(true);
		warning->addImage(&errorWarning)->align(Text::LOVE_ALIGN_LEFT);
		warningText = warning->addMultilineLabel("");
		warning->addLabel("")->setHeight(20);
		warningButton = warning->addButton("CORE_WARNING_OK", "OK");
		warningButton->setBorderColor(&borderColor);
		warningButton->setWidth(70);
		warningButton->setBorderSize(1);
		warning->show();
		// pause menu
		pause = new Menu(pauseFont, black);
		pause->setSize(150,200); // so that we have something to start with
		pause->setPadding(10);
		pause->setSpacing(1);
		pause->setColor(&black);
		pause->setBackgroundColor(&slightlyWhite);
		pause->stretchContent(true);
		pause->addButton("CORE_RESUME", "Resume");
		//pause->addButton("CORE_SAVE", "Save");
		//pause->addButton("CORE_LOAD", "Load");
		pause->addButton("CORE_SETTINGS", "Settings");
		pause->addButton("CORE_RELOAD", "Restart");
		pause->addButton("CORE_QUIT", "Quit");
		pause->adjustContent();
		pause->adjustSize();
		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );
		pause->show();

		settings = new Menu(pauseFont, black);
		settings->align(Text::LOVE_ALIGN_LEFT);
		settings->setSize(150,200);
		settings->setPadding(10);
		settings->setSpacing(1);
		settings->setColor(&black);
		settings->setBackgroundColor(&slightlyWhite);
		settings->stretchContent(true);
		settings->addLabel("SETTINGS");
		settings->addLabel(" ");
		settings->addLabel("Graphics:");
		nested = settings->addMenu(Menu::LOVE_MENU_HORIZONTAL);
		nested->addLabel("Resolution")->setWidth(150);
		pDropDown down = nested->addDropDown("CORE_SETTINGS_RESOLUTION");
		down->add("800x600"); down->add("1024x768");
		nested->adjustSize();
		nested->adjustContent();
		nested = settings->addMenu(Menu::LOVE_MENU_HORIZONTAL);
		nested->addLabel("Fullscreen")->setWidth(150);
		pCheckBox check = nested->addCheckBox("CORE_SETTINGS_FULLSCREEN");
		nested->adjustSize();
		nested->adjustContent();
		settings->addLabel(" ");
		settings->addLabel("Sound:");
		nested = settings->addMenu(Menu::LOVE_MENU_HORIZONTAL);
		nested->addLabel("Sound Volume")->setWidth(150);
		pSlider slid = nested->addSlider("CORE_SETTINGS_SOUND", Slider::LOVE_SLIDER_HORIZONTAL, 0, 1, 200, 15);
		slid->setColor(&white);
		nested->adjustSize();
		nested->adjustContent();
		nested = settings->addMenu(Menu::LOVE_MENU_HORIZONTAL);
		nested->addLabel("Music Volume")->setWidth(150);
		slid = nested->addSlider("CORE_SETTINGS_MUSIC", Slider::LOVE_SLIDER_HORIZONTAL, 0, 1, 200, 15);
		slid->setColor(&white);
		nested->adjustSize();
		nested->adjustContent();
		settings->adjustSize();
		nested = settings->addMenu(Menu::LOVE_MENU_HORIZONTAL, 0, 40);
		nested->setSpacing(5);
		nested->addButton("CORE_SETTINGS_OK", "Ok");
		nested->addButton("CORE_SETTINGS_CANCEL", "Cancel");
		nested->adjustContent();
		settings->adjustSize();
		settings->adjustContent();
		settings->setX( (core->display->getWidth() / 2) - (settings->getWidth() / 2) );
		settings->setY( (core->display->getHeight() / 2) - (settings->getHeight() / 2) );
		settings->show();

		return LOVE_OK;
	}

	int UIGame::load()
	{
		return LOVE_OK;
	}

	void UIGame::unload()
	{}

	void UIGame::render()
	{
		if(!errorMode && previous != 0)
			previous->render();
	}

	void UIGame::update(float dt)
	{
		//don't update the previous game
	}

	void UIGame::reloadGraphics()
	{
		errorWarning->reload();
		errorError->reload();
		errorFont->reload();
		pauseFont->reload();
		if(!errorMode && previous != 0)
			previous->reloadGraphics();
	}

	void UIGame::showError(const char * text)
	{
		// Why are you re-erroring yourself? Tsk tsk, little one.
		if(errorMode) return;

		// Entering error mode ...
		errorMode = true;

		errorText->setCaption(text);
		//errorText->adjustContent();
		errorText->adjustSize();

		error->adjustContent();
		error->adjustSize();

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		top->clear();
		top->add(error);
		core->gui->add(top);

		core->current->suspend();
		previous = core->current;
		core->current = this;
	}

	void UIGame::showWarning(const char * text)
	{
		warningText->setCaption(text);
		//errorText->adjustContent();
		warningText->adjustSize();

		warning->adjustContent();
		warning->adjustSize();

		warning->setX( (core->display->getWidth() / 2) - (warning->getWidth() / 2) );
		warning->setY( (core->display->getHeight() / 2) - (warning->getHeight() / 2) );

		top->clear();
		top->add(warning);
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
		pauseMode = true;
	}

	void UIGame::hidePause()
	{
		pauseMode = false;
		resumeGame();
	}

	void UIGame::showSettings()
	{
		top->clear();
		top->add(settings);
		if(!pauseMode)
		{
			core->gui->add(top);
			core->current->suspend();
			previous = core->current;
			core->current = this;
		}
		//printf("settings");
	}

	void UIGame::hideSettings()
	{
	}

	bool UIGame::isPaused()
	{
		if(previous != 0) //this means that it is paused
			return true;
		else
			return false;
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
			else if(strcmp(pme->getName(), "CORE_WARNING_OK") == 0)
				resumeGame();
			else if(strcmp(pme->getName(), "CORE_RESUME") == 0)
				resumeGame();
			else if(strcmp(pme->getName(), "CORE_SAVE") == 0)
				printf("save");
			else if(strcmp(pme->getName(), "CORE_LOAD") == 0)
				printf("load");
			else if(strcmp(pme->getName(), "CORE_SETTINGS") == 0)
				showSettings();
			else if(strcmp(pme->getName(), "CORE_RELOAD") == 0)
				reloadGame();
			else if(strcmp(pme->getName(), "CORE_QUIT") == 0)
				quitGame();
		}
	}

	void UIGame::displayModeChanged()
	{
		top->setSize(core->display->getCurrentDisplayMode().getWidth(),core->display->getCurrentDisplayMode().getHeight());

		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		error->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		warning->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		warning->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );

		if(!errorMode && previous != 0)
			previous->displayModeChanged();
		//reloadGraphics();
	}
}
