#include "FontTexGame.h"
#include "Core.h"
#include "love.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "DisplayMode.h"
#include "GameConfiguration.h"

using love::GameConfiguration;

namespace love {
FontTexGame::FontTexGame()
{
}

FontTexGame::~FontTexGame()
{

}

class DemoListModel : public gcn::ListModel
{
public:
    int getNumberOfElements()
    {
        return 5;
    }

    std::string getElementAt(int i)
    {
        switch(i)
        {
          case 0:
              return std::string("zero");
          case 1:
              return std::string("one");
          case 2:
              return std::string("two");
          case 3:
              return std::string("three");
          case 4:
              return std::string("four");
          default: // Just to keep warnings away
              return std::string("");
        }
    }
};



DemoListModel demoListModel;



int FontTexGame::load()
{
	const love::AbstractFileSystem & fs = love::core->getFilesystem();
	const love::DisplayMode & display = love::core->getDisplayMode();


	/**
	ConfigLoader c("data/love.conf");
	c.load();
	c.addBool("shizzle", false);
	c.write();
	**/


	/** leave be plz*
	PHYSFS_addToSearchPath("testfist.zip", 1);

	 char **rc = PHYSFS_enumerateFiles("fists");
	 char **i;

	 for (i = rc; *i != NULL; i++)
		 printf(" * We've got [%s].\n", *i);

	 PHYSFS_freeList(rc);

	 **/

	/*

	imageLoader = new gcn::OpenGLSDLImageLoader();
    gcn::Image::setImageLoader(imageLoader);

    graphics = new gcn::OpenGLGraphics();
	graphics->setTargetPlane(display.getWidth(), display.getHeight());

	lovefont = new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 10);
	lovefont->load();
	lovecolor = new love::Color(0x000000);

	top = new gcn::Container();
    top->setDimension(gcn::Rectangle(0, 0, display.getWidth(), display.getHeight()));

	//top->setOpaque(false);
    gui = new gcn::Gui();
    gui->setGraphics(graphics);
	gui->setInput(gcn_input); // Correct.
    gui->setTop(top);
	font = new love::GUIText(lovefont,lovecolor);
    gcn::Widget::setGlobalFont(font);
	graphics->setFont(font);

	/*label = new gcn::Label("Label");

    image = gcn::Image::load("../../data/gcn/gui-chan.bmp");
    icon = new gcn::Icon(image);

    button = new gcn::Button("Button");

    textField = new gcn::TextField("Text field");

    textBox = new gcn::TextBox("Multiline\nText box\nWhere is my baselines?\nWhy teh fawk is is the gjy etc cut off?");
    textBoxScrollArea = new gcn::ScrollArea(textBox);
    textBoxScrollArea->setWidth(200);
    textBoxScrollArea->setHeight(100);
    textBoxScrollArea->setBorderSize(1);
	textBoxScrollArea->setForegroundColor(gcn::Color(255, 0, 0));
	textBoxScrollArea->setBackgroundColor(gcn::Color(0xFF0000));

    listBox = new gcn::ListBox(&demoListModel);
    listBox->setBorderSize(1);

    dropDown = new gcn::DropDown(&demoListModel);

    checkBox1 = new gcn::CheckBox("Checkbox 1");
    checkBox2 = new gcn::CheckBox("Checkbox 2");

    radioButton1 = new gcn::RadioButton("RadioButton 1", "radiogroup", true);
    radioButton2 = new gcn::RadioButton("RadioButton 2", "radiogroup");
    radioButton3 = new gcn::RadioButton("RadioButton 3", "radiogroup");

    slider = new gcn::Slider(0, 10);
    slider->setSize(100, 10);

    window = new gcn::Window("I am a window  Drag me");
    window->setBaseColor(gcn::Color(255, 150, 200, 190));

    darkbitsImage = gcn::Image::load("../../data/gcn/darkbitslogo_by_haiko.bmp");
    darkbitsIcon = new gcn::Icon(darkbitsImage);
    window->add(darkbitsIcon);
    window->resizeToContent();

    nestedSlider = new gcn::Slider(0, 10);
    nestedSlider->setSize(100, 10);
    
    nestedContainer = new gcn::Container();
    nestedContainer->setSize(400, 200);
    nestedContainer->add(nestedSlider, 50, 70);

    nestedScrollArea = new gcn::ScrollArea(nestedContainer);
    nestedScrollArea->setSize(180, 90);
    nestedScrollArea->setBorderSize(1);*/

    /*
     * Add them to the top container
     */

	/*

	top->setBaseColor(gcn::Color(0xFFFFFF));

	Font * testfont = new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 12);
	testfont->load();

	shiny = new love::AnimatedColor();
	shiny->addColor(&pColor(new Color(0xFF7F96)), 6.0);
	shiny->addColor(&pColor(new Color(0x817FFF)), 6.0);
	shiny->addColor(&pColor(new Color(0x7FFF84)), 6.0);

	menu = new love::Menu(Menu::LOVE_MENU_VERTICAL);
	menu->setFont(testfont);
	menu->setSize(640,480);
	menu->setPosition(10,10);
	menu->setBackgroundColor(shiny);
	menu->setPadding(10);
	menu->setSpacing(5);
	//menu->stretchContent(true);
	menu->align(Menu::LOVE_ALIGN_LEFT);

	top->add(menu);

	Label * testlabel = menu->addLabel("THIS. IS. GUICHAN! (it's also fucking ugly)", 620);
	testlabel->setColor(new love::Color(0xFFFFFF));
	testlabel->setBackgroundColor(new love::Color(0xEE9DC8));
	testlabel->align(Text::LOVE_ALIGN_CENTER);
	testlabel->setBorderColor(new love::Color(0xEF1D92));
	testlabel->setBorderSize(1);

	menu->addButton("standard button");
	menu->addButton("resized button", 300, 50)->setBorderSize(2);
	menu->addButton("clipped button", 100, 12);
	Button * testbutton = menu->addButton("colo(red) button");
	testbutton->setColor(new love::Color(0xFFFFFF));
	testbutton->setBackgroundColor(new love::Color(0xFF0000));
	menu->addLabel("", 50, 50); //this acts as a separator

	Menu * godfist = menu->addMenu(Menu::LOVE_MENU_HORIZONTAL);
	godfist->align(Menu::LOVE_ALIGN_CENTER);
	godfist->setHeight(50);
	godfist->setFont(lovefont);
	//godfist->setBackgroundColor(new Color(0xF0F0F0));
	godfist->setSpacing(5);
	godfist->addLabel("This is another menu:", 200);
	godfist->addButton("button");
	godfist->addButton("button");
	godfist->addButton("button");
	godfist->adjustContent();
	godfist->adjustSize();
	menu->adjustContent();

	TextField * testfield = menu->addTextField("Enter your name here (textfield).", 200);
	testfield->setColor(new love::Color(0,0,0,100));
	testfield->setBackgroundColor(new love::Color(255,255,255,100));
	testfield->setActiveColor(new love::Color(0,0,0,200));
	testfield->setActiveBackgroundColor(new love::Color(255,255,255,200));

	alsoshiny = new love::AnimatedColor();
	alsoshiny->addColor(&pColor(new love::Color(0xFFFFFF)), 0.1f);
	alsoshiny->addColor(&pColor(new love::Color(0x000000)), 0.1f);

	DropDown * testdowns = menu->addDropDown(200);
	testdowns->setButtonBackgroundColor(alsoshiny);
	testdowns->add("this");
	testdowns->add("is");
	testdowns->add("GUIchan");
	//testdowns->setColor(new Color(0xFFFFFF));
	//testdowns->setBackgroundColor(new Color(0xFF0000));
	//testdowns->setActiveBackgroundColor(new Color(0xFF0000));
	//testdowns->setSelectionBackgroundColor(new Color(0x000000));

	//menu->adjustSize();

	Menu * nono = new love::Menu();
	nono->setSize(150,300);
	nono->setPadding(10);
	nono->setFont(lovefont);
	nono->setColor(new love::Color(0xFFFFFF));
	nono->setPosition(820,10);
	nono->setBackgroundColor(new love::Color(0x1a84d5));
	nono->stretchContent(true);
	//nono->align(Menu::LOVE_ALIGN_RIGHT);

	Button * button;
	nono->addLabel("NoNo Menu Example:");
	nono->addLabel("", 0, 20);
	button = nono->addButton("Random Game");
	button->align(Text::LOVE_ALIGN_RIGHT); //buttons automatically align to center
	button->setHeight(14);
	button = nono->addButton("Puzzle Game");
	button->align(Text::LOVE_ALIGN_RIGHT); //buttons automatically align to center
	button->setHeight(14);
	button = nono->addButton("Options");
	button->align(Text::LOVE_ALIGN_RIGHT); //buttons automatically align to center
	button->setHeight(14);
	button = nono->addButton("Clear");
	button->align(Text::LOVE_ALIGN_RIGHT); //buttons automatically align to center
	button->setHeight(14);
	nono->addLabel("", 0, 50);
	button = nono->addButton("Exit");
	button->align(Text::LOVE_ALIGN_RIGHT); //buttons automatically align to center
	button->setHeight(14);

	top->add(nono);

	// WONDERFUL ERROR MESSAGE LOL(I)
	bgimage.reset<AbstractImage>(love::core->getImaging().getImage(fs.getBaseFile("data/background.png")));
	bgimage->load();
	errorimage.reset<AbstractImage>(love::core->getImaging().getImage(fs.getBaseFile("data/error.png")));
	errorimage->load();

	Menu * error = new love::Menu();
	error->setSize(356,217); //this can be replaced with a error->adjustSize() which will adjust to the background image size
	error->setPadding(28);
	error->setFont(lovefont);
	error->setColor(new love::Color(0x000000));
	error->setPosition(334,275);
	//error->setBackgroundColor(new love::Color(0xFF0000));
	error->setBackground(bgimage.get());
	error->stretchContent(true);

	error->addImage(errorimage.get());
	error->addLabel("This is an example of some error text. Unfortunately")->align(Menu::LOVE_ALIGN_LEFT);
	error->addLabel("GUIchan doesn't handle '\\n' or automatic linebreaks,")->align(Menu::LOVE_ALIGN_LEFT);
	error->addLabel("but that is vital so I'll add it (later).")->align(Menu::LOVE_ALIGN_LEFT);
	error->addLabel("")->setHeight(40);
	Button * errorb = error->addButton("OK");
	errorb->setBorderColor(new love::Color(0xe9e9e9));
	errorb->setWidth(70);
	errorb->setBorderSize(1);

	error->adjustContent();

	top->add(error);


	//menu->add(textBoxScrollArea, 200, 50);
	

	/*
    top->add(label, 10, 10);
	top->add(icon, 10, 30);
    top->add(button, 200, 10);
    top->add(textField, 250, 10);
    top->add(textBoxScrollArea, 200, 50);
    top->add(listBox, 200, 200);
    top->add(dropDown, 500, 10);
    top->add(checkBox1, 500, 130);
    top->add(checkBox2, 500, 150);
    top->add(radioButton1, 500, 200);
    top->add(radioButton2, 500, 220);
    top->add(radioButton3, 500, 240);
    top->add(slider, 500, 300);
    top->add(window, 100, 350);
    top->add(nestedScrollArea, 440, 350);
	**/

	loaded = true;

	return LOVE_OK;
}

void FontTexGame::unload()
{
	//THIS COULD BE IMPORTANT LOL
	//Mix_CloseAudio();
}


int FontTexGame::init()
{
	
	config = new love::GameConfiguration();
	config->setTitle("FontTexGame");
	config->setAuthor("Grammaton Cleric Preston");
	config->setDisplayMode(DisplayMode(1024, 768));
	config->load();

	inited = true;
	return LOVE_OK;
}

void FontTexGame::render()
{
	glColor4ub(255,255,255,255);
	
	glBegin(GL_QUADS);
		glVertex2i(-2000,-2000);
		glVertex2i(-2000,2000);
		glVertex2i(2000,2000);
		glVertex2i(2000,-2000);
	glEnd();
	
	gui->draw();

	/*Color tempc = shiny->getColor(0.8f);
	glColor4ub(tempc.getRed(),tempc.getGreen(),tempc.getBlue(),tempc.getAlpha());
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glVertex2i(-200,-200);
		glVertex2i(-200,200);
		glVertex2i(200,200);
		glVertex2i(200,-200);
	glEnd();*/
}

void FontTexGame::update(float dt)
{
	gui->logic();
	//shiny->update(dt);
	//alsoshiny->update(dt);
}

void FontTexGame::keyPressed(int key)
{
	printf("Key: %d\n", key);
}

void FontTexGame::reloadGraphics()
{
	inited = inited;
}

} // love
