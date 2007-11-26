#include "AbstractMenu.h"
#include "GUIText.h"
#include "Core.h"
#include "love.h"
#include "Menu.h"
#include "ScrollMenu.h"
#include "WindowMenu.h"

namespace love
{
	AbstractMenu::AbstractMenu(pAbstractFont font, pAbstractColor color, int type)
	{
		//font.reset<GUIText>(new GUIText(font, color));
		this->font.reset<GUIText>(new GUIText(font));
		this->color = color;
		this->type = type;
		spacing = 0;
		position = 0;
		stretch = false;
		visible = false;
		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
		menuType = LOVE_MENU_DEFAULT;
		children.clear();
	}

	AbstractMenu::~AbstractMenu()
	{
		children.clear();
	}

	void AbstractMenu::show()
	{
		visible = true;
	}

	void AbstractMenu::hide()
	{
		visible = false;
	}

	void AbstractMenu::setFont(const pAbstractFont * font)
	{
		GUIElement::setFont(font);
	}

	void AbstractMenu::setColor(const pAbstractColor * color)
	{
		GUIElement::setColor(color);
	}

	void AbstractMenu::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void AbstractMenu::setBackground(const pAbstractImage * image)
	{
		background = *image;
	}

	void AbstractMenu::setSpacing(int spacing)
	{
		this->spacing = spacing;
	}

	void AbstractMenu::stretchContent(bool stretch)
	{
		this->stretch = stretch;
	}

	void AbstractMenu::align(int alignment)
	{
		this->alignment = alignment;
	}

	void AbstractMenu::valign(int alignment)
	{
		verticalAlignment = alignment;
	}

	pAbstractFont AbstractMenu::getFont()
	{
		return font->getFont();
	}

	pAbstractColor AbstractMenu::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	int AbstractMenu::getSpacing()
	{
		return spacing;
	}

	int AbstractMenu::getMenuType() const
	{
		return menuType;
	}

	pAbstractMenu AbstractMenu::addMenu(int type, int width, int height)
	{
		pMenu temp(new Menu(font->getFont(), color, type));

		temp->setSize(width, height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		temp->show();
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pAbstractMenu AbstractMenu::addScrollMenu(int type, int width, int height)
	{
		pScrollMenu temp(new ScrollMenu(font->getFont(), color, type));

		temp->setSize(width, height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		temp->show();
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pAbstractMenu AbstractMenu::addWindowMenu(int type, const char * caption, int width, int height)
	{
		pWindowMenu temp(new WindowMenu(font->getFont(), color, type));

		temp->setCaption(caption);
		temp->setSize(width, height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		temp->show();
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pLabel AbstractMenu::addLabel(const char * caption, int width, int height)
	{
		pLabel temp(new Label(caption));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pMultilineLabel AbstractMenu::addMultilineLabel(const char * caption, int width, int height)
	{
		pMultilineLabel temp(new MultilineLabel(caption));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		if(width != 0)
			temp->setWidth(width);
		else
			temp->setWidth(getWidth() - getPaddingLeft() - getPaddingRight());
		if(height != 0)
			temp->setHeight(height);
		temp->adjustContent();
		temp->adjustSize();
		temp->align(alignment);
		temp->valign(verticalAlignment);
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pLabel AbstractMenu::addImage(const pAbstractImage * image)
	{
		pLabel temp(new Label());
		temp->setFont(&font->getFont());
		temp->setColor(&color);
		temp->setBackground(image);

		temp->adjustSize();
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		pAbstractImage tempimg = temp->getBackground();
		return temp;
	}

	pButton AbstractMenu::addButton(const char * name, const char * caption, int width, int height)
	{
		pButton temp(new Button(caption));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		//temp->align(alignment);
		//temp->valign(verticalAlignment);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pTextField AbstractMenu::addTextField(const char * name, const char * text, int width, int height)
	{
		pTextField temp(new TextField(text));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pDropDown AbstractMenu::addDropDown(const char * name, int width, int height)
	{
		GUIList * tlist = new GUIList();
		pDropDown temp(new DropDown(tlist));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustHeight();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pRadioButton AbstractMenu::addRadioButton(const char * name, const char * caption, int width, int height)
	{
		pRadioButton temp(new RadioButton(caption));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pCheckBox AbstractMenu::addCheckBox(const char * name, const char * caption, int width, int height)
	{
		pCheckBox temp(new CheckBox(caption));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pSlider AbstractMenu::addSlider(const char * name, unsigned int orientation, double scaleStart, double scaleEnd, int width, int height)
	{
		pSlider temp(new Slider(scaleStart, scaleEnd));
		temp->setOrientation(orientation);
		//temp->setFont(&font->getFont());
		//temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pListBox AbstractMenu::addListBox(const char * name, int width, int height)
	{
		GUIList * tlist = new GUIList();
		pListBox temp(new ListBox(tlist));
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pTextBox AbstractMenu::addTextBox(const char * name, int width, int height)
	{
		pTextBox temp(new TextBox());
		temp->setFont(&font->getFont());
		temp->setColor(&color);

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}
}
