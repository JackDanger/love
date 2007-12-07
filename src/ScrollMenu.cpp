#include "ScrollMenu.h"

namespace love
{
	ScrollMenu::ScrollMenu(pAbstractFont font, pAbstractColor color, int type) : AbstractMenu(font, color, type)
	{
		container = new gcn::Container();
		gcn::ScrollArea(container);
		menuType = LOVE_MENU_SCROLL;
	}

	ScrollMenu::~ScrollMenu()
	{
		if(container != 0)
			delete container;
	}

	void ScrollMenu::show()
	{
		gcn::ScrollArea::setVisible(true);
	}

	void ScrollMenu::hide()
	{
		gcn::ScrollArea::setVisible(false);
	}

	bool ScrollMenu::isVisible()
	{
		return gcn::ScrollArea::isVisible();
	}

	void ScrollMenu::setSize(int width, int height)
	{
		gcn::ScrollArea::setSize(width, height);
	}

	void ScrollMenu::setWidth(int width)
	{
		gcn::ScrollArea::setWidth(width);
	}

	void ScrollMenu::setHeight(int height)
	{
		gcn::ScrollArea::setHeight(height);
	}

	void ScrollMenu::setBorderSize(unsigned int size)
	{
		gcn::ScrollArea::setBorderSize(size);
	}

	void ScrollMenu::setPosition(int x, int y)
	{
		gcn::ScrollArea::setPosition(x,y);
	}

	void ScrollMenu::setX(int x)
	{
		gcn::ScrollArea::setX(x);
	}

	void ScrollMenu::setY(int y)
	{
		gcn::ScrollArea::setY(y);
	}

	void ScrollMenu::setFont(const pAbstractFont & font)
	{
		AbstractMenu::setFont(font);
		gcn::ScrollArea::setFont(this->font.get());
	}

	void ScrollMenu::setBackgroundColor(const pAbstractColor& color)
	{
		AbstractMenu::setBackgroundColor(color);
	}

	int ScrollMenu::getWidth()
	{
		return gcn::ScrollArea::getWidth();
	}

	int ScrollMenu::getHeight()
	{
		return gcn::ScrollArea::getHeight();
	}

	int ScrollMenu::getX()
	{
		return gcn::ScrollArea::getX();
	}

	int ScrollMenu::getY()
	{
		return gcn::ScrollArea::getY();
	}

	unsigned int ScrollMenu::getBorderSize()
	{
		return gcn::ScrollArea::getBorderSize();
	}

	pAbstractFont ScrollMenu::getFont()
	{
		return AbstractMenu::getFont();
	}

	pAbstractColor ScrollMenu::getBackgroundColor()
	{
		return AbstractMenu::getBackgroundColor();
	}

	void ScrollMenu::adjustSize()
	{
		int width = 0;
		int height = 0;
		std::list<gcn::Widget *>::iterator iter;

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

	void ScrollMenu::adjustWidth()
	{
		int width = 0;
		std::list<gcn::Widget *>::iterator iter;

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

	void ScrollMenu::adjustHeight()
	{
		int height = 0;
		std::list<gcn::Widget *>::iterator iter;

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

	int ScrollMenu::adjustContent()
	{
		int size = 0;
		std::list<gcn::Widget *>::iterator iter;

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

	void ScrollMenu::positionItem(gcn::Widget * item)
	{
		std::list<gcn::Widget *>::iterator iter;

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

	void ScrollMenu::draw(gcn::Graphics* graphics)
	{
		if(!visible) return;

		if(backgroundColor != 0)
		{
			//gcn::ScrollArea::setBackgroundColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));
			graphics->setColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));
		}

		if (mVBarVisible)
		{
			drawUpButton(graphics);
			drawDownButton(graphics);
			drawVBar(graphics);
			drawVMarker(graphics);
		}
		
		if (mHBarVisible)
		{
			drawLeftButton(graphics);
			drawRightButton(graphics);
			drawHBar(graphics);
			drawHMarker(graphics);
		}

		int temp = getHorizontalScrollAmount();
		graphics->pushClipArea(gcn::Rectangle(-temp, 0, getWidth() + temp, getHeight()));

		graphics->setColor(gcn::Color(0xFF00FF));
		graphics->fillRectangle(gcn::Rectangle(0,0,100,100));

		drawChildren(graphics);

		graphics->popClipArea();

		//gcn::ScrollArea::draw(graphics);
	}

	void ScrollMenu::drawBorder(gcn::Graphics* graphics)
	{
		if(!visible) return;

		gcn::ScrollArea::drawBorder(graphics);
		return;

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

	void ScrollMenu::drawChildren(gcn::Graphics* graphics)
	{
		gcn::ScrollArea::drawChildren(graphics);
		return;

		graphics->pushClipArea(getChildrenArea());
		
		WidgetListIterator iter;
		for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
		{
			// Compensates for the children having their own fonts
			graphics->setFont(font.get());
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

	void ScrollMenu::add(gcn::Widget * widget)
	{
		gcn::ScrollArea::add(widget);
	}

	void ScrollMenu::setCaption(const char * caption)
	{}

	void ScrollMenu::setTitleBarHeight(unsigned int height)
	{}

	const char * ScrollMenu::getCaption()
	{
		return "";
	}

	unsigned int ScrollMenu::getTitleBarHeight()
	{
		return 0;
	}
}
