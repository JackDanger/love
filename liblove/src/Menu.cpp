#include "Menu.h"
#include "GUIText.h"

namespace love
{
	Menu::Menu(int type)
	{
		gcn::Container();
		gcn::Container::setOpaque(false); //makes the background invisible

		text = new GUIText(0,0);
		color = 0;
		backgroundColor = 0;
		this->type = type;
		spacing = 0;
		position = 0;
		stretch = false;
		align(LOVE_ALIGN_CENTER);
		valign(LOVE_ALIGN_CENTER);
	}

	Menu::~Menu()
	{
	}

	void Menu::setFont(Font * font)
	{
		text->setFont(font);
	}

	void Menu::setColor(AbstractColor * color)
	{
		this->color = color;
		text->setColor(color);
	}

	void Menu::setBackgroundColor(AbstractColor * color)
	{
		backgroundColor = color;
		gcn::Container::setOpaque(true);
	}

	void Menu::align(int alignment)
	{
		this->alignment = alignment;
	}

	void Menu::valign(int alignment)
	{
		verticalAlignment = alignment;
	}

	void Menu::setBackgroundColor(const char * name)
	{
		//not ready yet
	}

	void Menu::setSpacing(int spacing)
	{
		this->spacing = spacing;
		adjustContent();
	}

	int Menu::getSpacing()
	{
		return spacing;
	}

	void Menu::adjustSize()
	{
		int size = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			size = getPaddingTop();

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
				size += (*iter)->getHeight() + spacing + ((*iter)->getBorderSize());
			setHeight(size + getPaddingBottom() - spacing);
			break;
		case LOVE_MENU_HORIZONTAL:
			size = getPaddingLeft();

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
				size += (*iter)->getWidth() + spacing + ((*iter)->getBorderSize());
			setWidth(size + getPaddingRight() - spacing);
			break;
		}
	}

	int Menu::adjustContent()
	{
		//THIS SHOULD BE CHANGED DEPENDING ON THE TYPE OF MENU (VERTICAL FOR NOW)
		int size = 0;
		std::list<Widget *>::iterator iter;

		switch(type)
		{
		default:
		case LOVE_MENU_VERTICAL:
			size = getPaddingTop();
			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(stretch)
					(*iter)->setWidth(getWidth() - getPaddingRight() - getPaddingLeft() - (*iter)->getBorderSize());

				switch(alignment)
				{
				default:
				case LOVE_ALIGN_CENTER:
					(*iter)->setPosition( (getWidth() / 2) - ((*iter)->getWidth() / 2), size + (*iter)->getBorderSize());
					break;
				case LOVE_ALIGN_LEFT:
					(*iter)->setPosition(getPaddingLeft() + (*iter)->getBorderSize(), size + (*iter)->getBorderSize());
					break;
				case LOVE_ALIGN_RIGHT:
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
				if(stretch)
					(*iter)->setHeight(getHeight() - getPaddingTop() - getPaddingBottom() - (*iter)->getBorderSize());

				switch(verticalAlignment)
				{
				default:
				case LOVE_ALIGN_CENTER:
					(*iter)->setPosition(size + (*iter)->getBorderSize(), (getHeight() / 2) - ((*iter)->getHeight() / 2));
					break;
				case LOVE_ALIGN_TOP:
					(*iter)->setPosition(size + (*iter)->getBorderSize(), getPaddingTop() + (*iter)->getBorderSize());
					break;
				case LOVE_ALIGN_BOTTOM:
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

	void Menu::stretchContent(bool stretch)
	{
		this->stretch = stretch;
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
			case LOVE_ALIGN_CENTER:
				item->setX( (getWidth() / 2) - (item->getWidth() / 2) );
				break;
			case LOVE_ALIGN_LEFT:
				item->setX(getPaddingLeft() + item->getBorderSize());
				break;
			case LOVE_ALIGN_RIGHT:
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
			case LOVE_ALIGN_CENTER:
				item->setY( (getHeight() / 2) - (item->getHeight() / 2) );
				break;
			case LOVE_ALIGN_TOP:
				item->setY(getPaddingTop());
				break;
			case LOVE_ALIGN_BOTTOM:
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
		if(text != 0)
			graphics->setFont(text);

		if (isOpaque())
		{
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
		}

		drawChildren(graphics);
	}

	Menu * Menu::addMenu(int type, int width, int height)
	{
		Menu * temp = new Menu(type);

		temp->setFont(text->getFont());
		temp->setSize(width, height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		positionItem(temp);

		add(temp);
		return temp;
	}

	Label * Menu::addLabel(const char * caption, int width, int height)
	{
		Label * temp = new Label(caption);
		temp->setFont(text);
		temp->setColor(text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		temp->align(alignment);
		temp->valign(verticalAlignment);
		positionItem(temp);

		add(temp);
		return temp;
	}

	Button * Menu::addButton(const char * caption, int width, int height)
	{
		Button * temp = new Button(caption);
		temp->setFont(text);
		temp->setColor(text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		//temp->align(alignment);
		//temp->valign(verticalAlignment);
		positionItem(temp);

		add(temp);
		return temp;
	}

	TextField * Menu::addTextField(const char * text, int width, int height)
	{
		TextField * temp = new TextField(text);
		temp->setFont(this->text);
		temp->setColor(this->text->getColor());

		temp->adjustSize();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		positionItem(temp);

		add(temp);
		return temp;
	}

	DropDown * Menu::addDropDown(int width, int height)
	{
		GUIList * tlist = new GUIList();
		DropDown * temp = new DropDown(tlist);
		temp->setFont(text);
		temp->setColor(text->getColor());

		temp->adjustHeight();
		if(width != 0)
			temp->setWidth(width);
		if(height != 0)
			temp->setHeight(height);
		positionItem(temp);

		add(temp);
		return temp;
	}
}