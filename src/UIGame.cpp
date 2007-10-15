#include "UIGame.h"

#include "Core.h"
#include "love.h"
#include "AbstractDisplay.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"

using boost::dynamic_pointer_cast;

namespace love
{
	UIGame::UIGame()
	{
		previous = 0;
		error = 0;
		warning = 0;
		pause = 0;
		gui = 0;
	}

	UIGame::~UIGame()
	{
		if(error != 0) delete error;
		if(warning != 0) delete warning;
		if(pause != 0) delete pause;
		if(gui != 0) delete gui;
	}

	int UIGame::init()
	{
		gui = new gcn::Container();
		gui->setDimension(gcn::Rectangle(0, 0, core->display->getCurrentDisplayMode().getWidth(), core->display->getCurrentDisplayMode().getHeight()));
		gui->setOpaque(false);

		// resources
		errorWarning.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/warning.png")));
		errorWarning->load();
		errorError.reset<AbstractImage>(core->imaging->getImage(core->filesystem->getBaseFile("data/error.png")));
		errorError->load();
		pAbstractFont errorFont(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 10));
		errorFont->load();
		pAbstractFont pauseFont(new Font(core->filesystem->getBaseFile("data/fonts/FreeSans.ttf"), 14));
		pauseFont->load();
		pAbstractColor borderColor(new Color(0xe9e9e9));
		pAbstractColor black(new Color(0x000000));
		pAbstractColor slightlyWhite(new Color(255,255,255,200));

		// error box
		error = new Menu(errorFont, black);
		error->setSize(356,217); // so that we have something to start with
		error->setPadding(18);
		error->setColor(&black);
		error->setBackgroundColor(&slightlyWhite);
		error->stretchContent(true);
		error->addImage(&errorError)->align(Text::LOVE_ALIGN_LEFT);
		errorText.reset<MultilineLabel>(error->addMultilineLabel(""));
		error->addLabel("")->setHeight(20);
		errorButton.reset<Button>(error->addButton("CORE_ERROR_OK", "OK"));
		errorButton->setBorderColor(&borderColor);
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		error->show();
		// warning box
		warning = new Menu(errorFont, black);
		warning->setSize(356,217); // so that we have something to start with
		warning->setPadding(18);
		warning->setColor(&black);
		warning->setBackgroundColor(&slightlyWhite);
		warning->stretchContent(true);
		warning->addImage(&errorWarning)->align(Text::LOVE_ALIGN_LEFT);
		warningText.reset<MultilineLabel>(warning->addMultilineLabel(""));
		warning->addLabel("")->setHeight(20);
		warningButton.reset<Button>(warning->addButton("CORE_WARNING_OK", "OK"));
		warningButton->setBorderColor(&borderColor);
		warningButton->setWidth(70);
		warningButton->setBorderSize(1);
		warning->show();
		// pause menu
		pause = new Menu(pauseFont, black);
		pause->setSize(150,200); // so that we have something to start with
		pause->setPadding(10);
		pause->setColor(&black);
		pause->setBackgroundColor(&slightlyWhite);
		pause->stretchContent(true);
		pause->addButton("CORE_RESUME", "Resume");
		pause->addButton("CORE_SAVE", "Save");
		pause->addButton("CORE_LOAD", "Load");
		pause->addButton("CORE_OPTIONS", "Options");
		pause->addButton("CORE_RELOAD", "Restart");
		pause->addButton("CORE_QUIT", "Quit");
		pause->adjustContent();
		pause->adjustSize();
		pause->setX( (core->display->getWidth() / 2) - (pause->getWidth() / 2) );
		pause->setY( (core->display->getHeight() / 2) - (pause->getHeight() / 2) );
		pause->show();

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
		if(previous != 0)
			previous->render();
	}

	void UIGame::update(float dt)
	{
		//don't update the previous game
	}

	void UIGame::reloadGraphics()
	{
		if(previous != 0)
			previous->reloadGraphics();
	}

	void UIGame::showError(const char * text)
	{
		errorText->setCaption(text);
		//errorText->adjustContent();
		errorText->adjustSize();

		error->adjustContent();
		error->adjustSize();

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		gui->clear();
		gui->add(error);
		core->gui->add(gui);

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

		gui->clear();
		gui->add(warning);
		core->gui->add(gui);

		core->current->suspend();
		previous = core->current;
		core->current = this;
	}

	void UIGame::showPause()
	{
		if(previous != 0) return; //if we are already paused

		gui->clear();
		gui->add(pause);
		core->gui->add(gui);

		core->current->suspend();
		previous = core->current;
		core->current = this;
	}

	void UIGame::eventFired(pEvent e)
	{
		if(e->getType() == EventListener::LOVE_EVENT_GUI)
		{
			pGUIEvent pme = dynamic_pointer_cast<GUIEvent, Event>(e);
			if(strcmp(pme->getName(), "CORE_ERROR_OK") == 0)
			{
				core->current = previous;
				previous = 0;
				core->current->resume();
				core->gui->remove(gui);
			}
			else if(strcmp(pme->getName(), "CORE_WARNING_OK") == 0)
			{
				core->current = previous;
				previous = 0;
				core->current->resume();
				core->gui->remove(gui);
			}
			else if(strcmp(pme->getName(), "CORE_RESUME") == 0)
			{
				core->current = previous;
				previous = 0;
				core->current->resume();
				core->gui->remove(gui);
			}	
			else if(strcmp(pme->getName(), "CORE_SAVE") == 0)
				printf("save");
			else if(strcmp(pme->getName(), "CORE_LOAD") == 0)
				printf("load");
			else if(strcmp(pme->getName(), "CORE_OPTIONS") == 0)
				printf("options");
			else if(strcmp(pme->getName(), "CORE_RELOAD") == 0)
			{
				core->current = previous;
				previous = 0;		
				core->current->reload();
				core->gui->remove(gui);
				printf("Reloaded: %s\n", core->current->getName().c_str());
			}
			else if(strcmp(pme->getName(), "CORE_QUIT") == 0)
			{
				previous->stop();
				previous = 0;
				core->startGame("love-system-menu", false);
				core->gui->remove(gui);
			}
		}
	}

	void UIGame::displayModeChanged()
	{
		gui->setSize(core->display->getCurrentDisplayMode().getWidth(),core->display->getCurrentDisplayMode().getHeight());
		if(previous != 0)
			previous->displayModeChanged();
	}
}