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

	int OpenGLGUI::init()
	{
		const DisplayMode & display = core->getDisplayMode();
		const AbstractFileSystem & fs = core->getFilesystem();
		//const AbstractImageDevice & imaging = core->getImaging();

		// Initialize GUIchan
		imageLoader = new gcn::OpenGLSDLImageLoader();
		gcn::Image::setImageLoader(imageLoader);

		graphics = new gcn::OpenGLGraphics();
		graphics->setTargetPlane(display.getWidth(), display.getHeight());

		font.reset<AbstractFont>(new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10));
		font->load();
		pAbstractColor black(new Color(0x000000));

		top = new gcn::Container();
	    top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));
		top->setOpaque(false);

		gui = new gcn::Gui();
		gui->setGraphics(graphics);
		gui->setInput(gcn_input); // correct.
		gui->setTop(top);
		text = new love::GUIText(font, black);
		gcn::Widget::setGlobalFont(text); // the global font is static and must be set
		graphics->setFont(text);

		clear();

		return LOVE_OK;
	}

	void OpenGLGUI::displayModeChanged()
	{
		const DisplayMode & display = core->getDisplayMode();
		graphics->setTargetPlane(display.getWidth(), display.getHeight());
		top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));

		font->load();
	}
}
