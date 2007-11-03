#include "AbstractMenu.h"
#include "GUIText.h"
#include "Core.h"
#include "love.h"
#include "Menu.h"

namespace love
{
	AbstractMenu::AbstractMenu(pAbstractFont font, pAbstractColor color, int type)
	{
		text.reset<GUIText>(new GUIText(font, color));
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
		text->setFont(*font);
	}

	/*void AbstractMenu::setColor(const pAbstractColor * color)
	{
		GUIElement::setColor(color);
		text->setColor(*color);
	}*/

	void AbstractMenu::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	/*void AbstractMenu::setBorderColor(const pAbstractColor * color)
	{
		GUIElement::setBorderColor(color);
	}*/

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
		return text->getFont();
	}

	/*pAbstractColor AbstractMenu::getColor()
	{
		return GUIElement::getColor();
	}*/

	pAbstractColor AbstractMenu::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	/*pAbstractColor AbstractMenu::getBorderColor()
	{
		return GUIElement::getBorderColor();
	}*/

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
		pMenu temp(new Menu(text->getFont(), color, type));

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		temp->setBackground(image);

		temp->adjustSize();
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp.get());

		add(temp.get());
		children.push_back(temp);
		return temp;
	}

	pButton AbstractMenu::addButton(const char * name, const char * caption, int width, int height)
	{
		pButton temp(new Button(caption));
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		temp->setFont(this->text.get());
		temp->setColor(&this->text->getColor());

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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
		//temp->setFont(text);
		//temp->setColor(&text->getColor());

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
		temp->setFont(text.get());
		temp->setColor(&text->getColor());

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

	/*
	TextBox * AbstractMenu::addTextBox(const char * name, int width, int height)
	{
		TextBox * temp = new TextBox();
		temp->setFont(this->text.get());
		temp->setColor(&this->text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp);

		//add(temp);
		add(textBoxScrollArea);
		return temp;
	}
	*/
}
