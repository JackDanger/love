#include "Menu.h"
#include "GUIText.h"
#include "Core.h"
#include "love.h"

namespace love
{
	Menu::Menu(pAbstractFont font, pAbstractColor color, int type)
	{
		gcn::Container();
		gcn::Container::setOpaque(false); //makes the background invisible

		text = new GUIText(font, color);
		this->type = type;
		spacing = 0;
		position = 0;
		stretch = false;
		visible = false;
		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
		setOpaque(true); //we deal with the visibility ourselves
	}

	Menu::~Menu()
	{
		if(text != 0)
			delete text;
	}

	void Menu::setSize(int width, int height)
	{
		gcn::Container::setSize(width, height);
	}

	void Menu::setWidth(int width)
	{
		gcn::Container::setWidth(width);
	}

	void Menu::setHeight(int height)
	{
		gcn::Container::setHeight(height);
	}

	void Menu::setBorderSize(unsigned int size)
	{
		gcn::Container::setBorderSize(size);
	}

	void Menu::setPosition(int x, int y)
	{
		gcn::Container::setPosition(x,y);
	}

	void Menu::setX(int x)
	{
		gcn::Container::setX(x);
	}

	void Menu::setY(int y)
	{
		gcn::Container::setY(y);
	}

	void Menu::show()
	{
		visible = true;
	}

	void Menu::hide()
	{
		visible = false;
	}

	void Menu::setFont(AbstractFont * font)
	{
		text->setFont(font);
	}

	void Menu::setFont(const pAbstractFont * font)
	{
		text->setFont(*font);
	}

	void Menu::setColor(const pAbstractColor * color)
	{
		this->color = *color;
		text->setColor(*color);
	}

	void Menu::setBackgroundColor(const pAbstractColor * color)
	{
		backgroundColor = *color;
	}

	void Menu::setBorderColor(const pAbstractColor * color)
	{
		borderColor = *color;
	}

	void Menu::setBackground(const pAbstractImage * image)
	{
		background = *image;
	}

	void Menu::stretchContent(bool stretch)
	{
		this->stretch = stretch;
	}

	void Menu::align(int alignment)
	{
		this->alignment = alignment;
	}

	void Menu::valign(int alignment)
	{
		verticalAlignment = alignment;
	}

	void Menu::setSpacing(int spacing)
	{
		this->spacing = spacing;
		adjustContent();
	}

	int Menu::getWidth()
	{
		return gcn::Container::getWidth();
	}

	int Menu::getHeight()
	{
		return gcn::Container::getHeight();
	}

	int Menu::getX()
	{
		return gcn::Container::getX();
	}

	int Menu::getY()
	{
		return gcn::Container::getY();
	}

	unsigned int Menu::getBorderSize()
	{
		return gcn::Container::getBorderSize();
	}

	int Menu::getSpacing()
	{
		return spacing;
	}

	void Menu::adjustSize()
	{
		int width = 0;
		int height = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			width = 0;
			height = getPaddingTop();

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(width < (*iter)->getWidth())
					width = (*iter)->getWidth();
				height += (*iter)->getHeight() + spacing + ((*iter)->getBorderSize());
			}

			width += getPaddingLeft() + getPaddingRight();
			height += getPaddingBottom() - spacing;
			setSize(width, height);

			break;
		case LOVE_MENU_HORIZONTAL:
			width = getPaddingLeft();
			height = 0;

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(height < (*iter)->getHeight())
					height = (*iter)->getHeight();
				width += (*iter)->getWidth() + spacing + ((*iter)->getBorderSize());
			}
			
			width += getPaddingRight() - spacing;
			height += getPaddingTop() + getPaddingBottom();
			setSize(width, height);

			break;
		}

		//compensates for the background image
		if(background != 0)
		{
			if(getWidth() < background->getWidth())
				setWidth((int)background->getWidth());
			if(getHeight() < background->getHeight())
				setHeight((int)background->getHeight());
		}
	}

	void Menu::adjustWidth()
	{
		int width = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			width = 0;

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(width < (*iter)->getWidth())
					width = (*iter)->getWidth();
			}

			width += getPaddingLeft() + getPaddingRight();
			setWidth(width);

			break;
		case LOVE_MENU_HORIZONTAL:
			width = getPaddingLeft();

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				width += (*iter)->getWidth() + spacing + ((*iter)->getBorderSize());
			}
			
			width += getPaddingRight() - spacing;
			setWidth(width);

			break;
		}

		//compensates for the background image
		if(background != 0)
		{
			if(getWidth() < background->getWidth())
				setWidth((int)background->getWidth());
		}
	}

	void Menu::adjustHeight()
	{
		int height = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			height = getPaddingTop();

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				height += (*iter)->getHeight() + spacing + ((*iter)->getBorderSize());
			}

			height += getPaddingBottom() - spacing;
			setHeight(height);

			break;
		case LOVE_MENU_HORIZONTAL:
			height = 0;

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(height < (*iter)->getHeight())
					height = (*iter)->getHeight();
			}
			
			height += getPaddingTop() + getPaddingBottom();
			setHeight(height);

			break;
		}

		//compensates for the background image
		if(background != 0)
		{
			if(getHeight() < background->getHeight())
				setHeight((int)background->getHeight());
		}
	}

	int Menu::adjustContent()
	{
		int size = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			size = getPaddingTop();
			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(stretch && (*iter)->getWidth() <= 0)
					(*iter)->setWidth(getWidth() - getPaddingRight() - getPaddingLeft() - (*iter)->getBorderSize());

				switch(alignment)
				{
				default:
				case Text::LOVE_ALIGN_CENTER:
					(*iter)->setPosition( (getWidth() / 2) - ((*iter)->getWidth() / 2), size + (*iter)->getBorderSize());
					break;
				case Text::LOVE_ALIGN_LEFT:
					(*iter)->setPosition(getPaddingLeft() + (*iter)->getBorderSize(), size + (*iter)->getBorderSize());
					break;
				case Text::LOVE_ALIGN_RIGHT:
					(*iter)->setPosition(getWidth() - (*iter)->getWidth() - getPaddingRight()- (*iter)->getBorderSize(), size + (*iter)->getBorderSize());
					break;
				}
				size += (*iter)->getHeight() + spacing;
			}
			size -= (spacing + getPaddingTop()); //to return only the content size
			break;
		case LOVE_MENU_HORIZONTAL:
			size = getPaddingLeft();
			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(stretch && (*iter)->getHeight() <= 0)
					(*iter)->setHeight(getHeight() - getPaddingTop() - getPaddingBottom() - (*iter)->getBorderSize());

				switch(verticalAlignment)
				{
				default:
				case Text::LOVE_ALIGN_CENTER:
					(*iter)->setPosition(size + (*iter)->getBorderSize(), (getHeight() / 2) - ((*iter)->getHeight() / 2));
					break;
				case Text::LOVE_ALIGN_TOP:
					(*iter)->setPosition(size + (*iter)->getBorderSize(), getPaddingTop() + (*iter)->getBorderSize());
					break;
				case Text::LOVE_ALIGN_BOTTOM:
					(*iter)->setPosition(size + (*iter)->getBorderSize(), getHeight() - (*iter)->getHeight() - getPaddingBottom() - (*iter)->getBorderSize());
					break;
				}
				size += (*iter)->getWidth() + spacing;
			}
			size -= (spacing + getPaddingLeft()); //to return only the content size
			break;
		}

		return size;
	}

	void Menu::positionItem(gcn::Widget * item)
	{
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			if(stretch)
				item->setWidth(getWidth() - getPaddingRight() - getPaddingLeft());
			
			switch(alignment)
			{
			default:
			case Text::LOVE_ALIGN_CENTER:
				item->setX( (getWidth() / 2) - (item->getWidth() / 2) );
				break;
			case Text::LOVE_ALIGN_LEFT:
				item->setX(getPaddingLeft() + item->getBorderSize());
				break;
			case Text::LOVE_ALIGN_RIGHT:
				item->setX(getWidth() - item->getWidth() - getPaddingRight() - item->getBorderSize());
				break;
			}
	
			position = getPaddingTop();
			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
				position += (*iter)->getHeight() + spacing;
	
			item->setY(position);
			break;
		case LOVE_MENU_HORIZONTAL:
			if(stretch)
				item->setHeight(getHeight() - getPaddingTop() - getPaddingBottom());
			
			switch(alignment)
			{
			default:
			case Text::LOVE_ALIGN_CENTER:
				item->setY( (getHeight() / 2) - (item->getHeight() / 2) );
				break;
			case Text::LOVE_ALIGN_TOP:
				item->setY(getPaddingTop());
				break;
			case Text::LOVE_ALIGN_BOTTOM:
				item->setY(getHeight() - item->getHeight() - getPaddingBottom());
				break;
			}
	
			position = getPaddingLeft();
			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
				position += (*iter)->getWidth() + spacing;
	
			item->setX(position);
			break;
		}
	}

	void Menu::draw(gcn::Graphics* graphics)
	{
		if(!visible) return;

		//glPushMatrix();

		if(text != 0)
			graphics->setFont(text);

		if (isOpaque())
		{
			if(backgroundColor != 0)
			{
				graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
				graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
			}

			if(background != 0)
			{
				int x = 0;
				int y = 0;
				switch(alignment)
				{
				default:
				case Text::LOVE_ALIGN_CENTER:
					x = (int)((getWidth() / 2) - (background->getWidth() / 2));
					break;
				case Text::LOVE_ALIGN_LEFT:
					//do nothing (leave the values as they are)
					break;
				case Text::LOVE_ALIGN_RIGHT:
					x = (int)(getWidth() - background->getWidth());
					break;
				}
				switch(verticalAlignment)
				{
				default:
				case Text::LOVE_ALIGN_CENTER:
					y = (int)((getHeight() / 2) - (background->getHeight() / 2));
					break;
				case Text::LOVE_ALIGN_TOP:
					break;
				case Text::LOVE_ALIGN_BOTTOM:
					y = (int)(getHeight() - background->getHeight());
					break;
				}
				graphics->setColor(gcn::Color(0xFFFFFF)); // to remove the effects of the background color
				background->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			}
		}

		drawChildren(graphics);

		//glPopMatrix();
	}

	void Menu::drawBorder(gcn::Graphics* graphics)
	{
		if(!visible) return;

		//gcn::Container::drawBorder(graphics);

		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(getBaseColor());

		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}

	void Menu::drawChildren(gcn::Graphics* graphics)
	{
		graphics->pushClipArea(getChildrenArea());
		
		WidgetListIterator iter;
		for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
		{
			// Compensates for the children having their own fonts
			graphics->setFont(text);
			if ((*iter)->isVisible())
			{
				// If the widget has a border,
				// draw it before drawing the widget
				if ((*iter)->getBorderSize() > 0)
				{
					gcn::Rectangle rec = (*iter)->getDimension();
					rec.x -= (*iter)->getBorderSize();
					rec.y -= (*iter)->getBorderSize();
					rec.width += 2 * (*iter)->getBorderSize();
					rec.height += 2 * (*iter)->getBorderSize();
					graphics->pushClipArea(rec);
					(*iter)->drawBorder(graphics);
					graphics->popClipArea();
				}
				
				graphics->pushClipArea((*iter)->getDimension());
				(*iter)->draw(graphics);
				graphics->popClipArea();
			}
		}
		graphics->popClipArea();
	}

	Menu * Menu::addMenu(int type, int width, int height)
	{
		Menu * temp = new Menu(text->getFont(), color, type);

		temp->setSize(width, height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		temp->show();
		positionItem(temp);

		add(temp);
		return temp;
	}

	Label * Menu::addLabel(const char * caption, int width, int height)
	{
		Label * temp = new Label(caption);
		temp->setFont(text);
		temp->setColor(&text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp);

		add(temp);
		return temp;
	}

	MultilineLabel * Menu::addMultilineLabel(const char * caption, int width, int height)
	{
		MultilineLabel * temp = new MultilineLabel(caption);
		temp->setFont(text);
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
		positionItem(temp);

		add(temp);
		return temp;
	}

	Label * Menu::addImage(const pAbstractImage * image)
	{
		Label * temp = new Label();
		temp->setBackground(image);

		temp->adjustSize();
		//temp->addActionListener(core->getGUI()); //not needed here
		positionItem(temp);

		add(temp);
		return temp;
	}

	Button * Menu::addButton(const char * name, const char * caption, int width, int height)
	{
		Button * temp = new Button(caption);
		temp->setFont(text);
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
		positionItem(temp);

		add(temp);
		return temp;
	}

	TextField * Menu::addTextField(const char * name, const char * text, int width, int height)
	{
		TextField * temp = new TextField(text);
		temp->setFont(this->text);
		temp->setColor(&this->text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp);

		add(temp);
		return temp;
	}

	DropDown * Menu::addDropDown(const char * name, int width, int height)
	{
		GUIList * tlist = new GUIList();
		DropDown * temp = new DropDown(tlist);
		temp->setFont(text);
		temp->setColor(&text->getColor());

		temp->adjustHeight();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp);

		add(temp);
		return temp;
	}

	RadioButton * Menu::addRadioButton(const char * name, const char * caption, int width, int height)
	{
		RadioButton * temp = new RadioButton(caption);
		temp->setFont(text);
		temp->setColor(&text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->addActionListener(core->getGUI());
		temp->setName(name);
		positionItem(temp);

		add(temp);
		return temp;
	}
}