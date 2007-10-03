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

		error->addImage(errorError)->align(Menu::LOVE_ALIGN_LEFT);
		error->addLabel("This is an example of some error text. Unfortunately")->align(Menu::LOVE_ALIGN_LEFT);
		error->addLabel("GUIchan doesn't handle '\\n' or automatic linebreaks,")->align(Menu::LOVE_ALIGN_LEFT);
		error->addLabel("but that is vital so I'll add it (later).")->align(Menu::LOVE_ALIGN_LEFT);
		error->addLabel("")->setHeight(40);
		Button * errorButton = error->addButton("OK");
		errorButton->setBorderColor(new Color(0xe9e9e9));
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		errorButton->addActionListener(this);

		error->adjustContent();
		error->adjustSize();
		top->add(error);
	}

	void OpenGLGUI::showWarning(const char * text)
	{
		error->clear(); // just to be sure

		error->setX( (core->display->getWidth() / 2) - (error->getWidth() / 2) );
		error->setX( (core->display->getHeight() / 2) - (error->getHeight() / 2) );

		error->addImage(errorWarning);
		error->addLabel("This is an example of some error text. Unfortunately")->align(Menu::LOVE_ALIGN_LEFT);
		//error->addLabel("GUIchan doesn't handle '\\n' or automatic linebreaks,")->align(Menu::LOVE_ALIGN_LEFT);
		//error->addLabel("but that is vital so I'll add it (later).")->align(Menu::LOVE_ALIGN_LEFT);
		error->addLabel("")->setHeight(40);
		Button * errorButton = error->addButton("OK");
		errorButton->setBorderColor(new Color(0xe9e9e9));
		errorButton->setWidth(70);
		errorButton->setBorderSize(1);
		errorButton->addActionListener(this);

		error->adjustContent();
		error->adjustSize();
		top->add(error);
	}

	void OpenGLGUI::action(const gcn::ActionEvent& actionEvent)
	{
		printf("ActionEvent: %s", actionEvent.getId());
		gcn::Widget * temp = actionEvent.getSource();
		top->remove(temp->getParent());
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

		lovefont = new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10);
		lovefont->load();
		lovecolor = new love::Color(0x000000);

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
		errorBackground = imaging.getImage(fs.getBaseFile("data/background.png"));
		errorBackground->load();
		errorWarning = imaging.getImage(fs.getBaseFile("data/warning.png"));
		errorWarning->load();
		errorError = imaging.getImage(fs.getBaseFile("data/error.png"));
		errorError->load();

		error = new Menu();
		error->setSize(356,217); // so that we have something to start with
		error->setPadding(18);
		//error->setFont(new Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10)); // i hate you and what you've done to me
		error->setFont(lovefont);
		error->setColor(new Color(0x000000));
		//error->setPosition(50,50); // this is automatic now
		error->setBackgroundColor(new love::Color(255,255,255,225));
		//error->setBackground(errorBackground); // ugly and removed
		error->stretchContent(true);

		top->add(error);
		top->remove(error); // this was just a test.. can be removed now (lol)
	}

	void OpenGLGUI::render()
	{
		gui->draw();
		//top->draw();
		//core->graphics->drawString("HELLO CLEVELAND", 50, 50);
	}

	void OpenGLGUI::update(float dt)
	{
		gui->logic();
	}
}