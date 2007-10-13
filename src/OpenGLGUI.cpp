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
	}

	void OpenGLGUI::showError(const char * text)
	{
		error->clear(); // just to be sure

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setY( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		error->addImage(&errorError)->align(Menu::LOVE_ALIGN_LEFT);
		error->addMultilineLabel(text);
		error->addLabel("")->setHeight(20);

		Button * errorButton = error->addButton("OK");
		pAbstractColor borderColor(new Color(0xe9e9e9));
		errorButton->setBorderColor(&borderColor);
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		errorButton->addActionListener(this);
		errorButton->setActionEventId("ERRORBUTTON_OK");

		error->adjustContent();
		error->adjustSize();
		top->add(error.get());
	}

	void OpenGLGUI::showWarning(const char * text)
	{
		error->clear(); // just to be sure

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setX( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		error->addImage(&errorWarning);
		error->addMultilineLabel(text);
		error->addLabel("")->setHeight(20);

		Button * errorButton = error->addButton("OK");
		pAbstractColor borderColor(new Color(0xe9e9e9));
		errorButton->setBorderColor(&borderColor);
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		errorButton->addActionListener(this);
		errorButton->setActionEventId("ERRORBUTTON_OK");

		error->adjustContent();
		error->adjustSize();
		top->add(error.get());
	}

	void OpenGLGUI::action(const gcn::ActionEvent& actionEvent)
	{
		printf("ActionEvent: %s", actionEvent.getId().c_str());

		if(strcmp(actionEvent.getId().c_str(), "ERRORBUTTON_OK") == 0)
			top->remove(actionEvent.getSource()->getParent());
	}

	void OpenGLGUI::add(pMenu menu)
	{
		top->add(menu.get());
	}

	void OpenGLGUI::init()
	{
		const DisplayMode & display = core->getDisplayMode();
		const AbstractFileSystem & fs = core->getFilesystem();
		const AbstractImageDevice & imaging = core->getImaging();

		// Initialize GUIchan
		imageLoader = new gcn::OpenGLSDLImageLoader();
		gcn::Image::setImageLoader(imageLoader);

	    graphics = new gcn::OpenGLGraphics();
		graphics->setTargetPlane(display.getWidth(), display.getHeight());

		lovefont.reset<AbstractFont>(new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10));
		lovefont->load();
		lovecolor.reset<AbstractColor>(new love::Color(0x000000));

		top = new gcn::Container();
	    top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));

		top->setOpaque(false);
		gui = new gcn::Gui();
		gui->setGraphics(graphics);
		gui->setInput(gcn_input); // correct.
		gui->setTop(top);
		text = new love::GUIText(lovefont,lovecolor);
		gcn::Widget::setGlobalFont(text);
		graphics->setFont(text);

		gui = new gcn::Gui();
		gui->setGraphics(graphics);
		gui->setInput(gcn_input);
		gui->setTop(top);
		gcn::Widget::setGlobalFont(text); // the global font is static and must be set
		graphics->setFont(text);

		// load the default images
		errorBackground.reset<AbstractImage>(imaging.getImage(fs.getBaseFile("data/background.png")));
		errorBackground->load();
		errorWarning.reset<AbstractImage>(imaging.getImage(fs.getBaseFile("data/warning.png")));
		errorWarning->load();
		errorError.reset<AbstractImage>(imaging.getImage(fs.getBaseFile("data/error.png")));
		errorError->load();

		error.reset<Menu>(new Menu(core->graphics->getFont(), core->graphics->getColor()));
		error->setSize(356,217); // so that we have something to start with
		error->setPadding(18);
		//error->setFont(new Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10)); // i hate you and what you've done to me
		error->setFont(&lovefont);
		error->setColor(new pAbstractColor(new Color(0x000000)));
		//error->setPosition(50,50); // this is automatic now
		error->setBackgroundColor(new pAbstractColor(new Color(255,255,255,225)));
		//error->setBackground(errorBackground); // ugly and removed
		error->stretchContent(true);
	}

	void OpenGLGUI::render()
	{
		gui->draw();
	}

	void OpenGLGUI::update(float dt)
	{
		gui->logic();
	}
}