#include "OpenGLGUI.h"
#include "Core.h"
#include "love.h"
#include "AbstractDisplay.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "DisplayMode.h"
#include "GameConfiguration.h"

namespace love
{
	OpenGLGUI::OpenGLGUI()
	{
		gui = 0;
		guifont = 0;
		graphics = 0;
		top = 0;
	}

	OpenGLGUI::~OpenGLGUI()
	{
		if(gui != 0) delete gui;
		if(guifont != 0) delete guifont;
		if(graphics != 0) delete graphics;
		if(top != 0) delete top;
	}

	void OpenGLGUI::action(const gcn::ActionEvent& actionEvent)
	{
		printf("ActionEvent: %s\n", actionEvent.getId().c_str());

		pEvent temp(new Event());
		temp->setType(EventListener::LOVE_EVENT_GUI);
		temp->setName(actionEvent.getId());
		core->eventFired(temp);
	}

	void OpenGLGUI::add(pMenu menu)
	{
		top->add(menu.get());
	}

	void OpenGLGUI::add(gcn::Widget * widget)
	{
		top->add(widget);
	}

	void OpenGLGUI::remove(gcn::Widget * widget)
	{
		top->remove(widget);
	}

	void OpenGLGUI::clear()
	{
		top->clear();
		top->add(new Label("Worst. Bugfix. Ever."));
	}

	pAbstractFont OpenGLGUI::getFont()
	{
		return text->getFont();
	}

	pAbstractColor OpenGLGUI::getColor()
	{
		return text->getColor();
	}

	void OpenGLGUI::init()
	{
		const DisplayMode & display = core->getDisplayMode();
		const AbstractFileSystem & fs = core->getFilesystem();
		//const AbstractImageDevice & imaging = core->getImaging();

		// Initialize GUIchan
		imageLoader = new gcn::OpenGLSDLImageLoader();
		gcn::Image::setImageLoader(imageLoader);

	    graphics = new gcn::OpenGLGraphics();
		graphics->setTargetPlane(display.getWidth(), display.getHeight());

		lovefont.reset<AbstractFont>(new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10));
		lovefont->load();

		top = new gcn::Container();
	    top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));
		top->setOpaque(false);

		gui = new gcn::Gui();
		gui->setGraphics(graphics);
		gui->setInput(gcn_input); // correct.
		gui->setTop(top);
		text = new love::GUIText(lovefont,core->graphics->getColor());
		gcn::Widget::setGlobalFont(text);
		graphics->setFont(text);

		gui = new gcn::Gui();
		gui->setGraphics(graphics);
		gui->setInput(gcn_input);
		gui->setTop(top);
		gcn::Widget::setGlobalFont(text); // the global font is static and must be set
		graphics->setFont(text);

		clear();
	}

	void OpenGLGUI::render()
	{
		gui->draw();
	}

	void OpenGLGUI::update(float dt)
	{
		gui->logic();
	}

	void OpenGLGUI::displayModeChanged()
	{
		const DisplayMode & display = core->getDisplayMode();
		graphics->setTargetPlane(display.getWidth(), display.getHeight());
		top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));
	}
}