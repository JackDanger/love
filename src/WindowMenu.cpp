#include "WindowMenu.h"
#include "GUIText.h"
#include "Core.h"
#include "love.h"

namespace love
{
	WindowMenu::WindowMenu(pAbstractFont font, pAbstractColor color, int type) : AbstractMenu(font, color, type)
	{
		gcn::Window();
		gcn::Window::setOpaque(false); //makes the background invisible
		menuType = LOVE_MENU_WINDOW;
		setOpaque(true); //we deal with the visibility ourselves
		if(this->font != 0)
			setTitleBarHeight(this->font->getHeight() + 2);
	}

	WindowMenu::~WindowMenu()
	{
		gcn::Window::clear();
		children.clear();
	}

	void WindowMenu::show()
	{
		gcn::Window::setVisible(true);
	}

	void WindowMenu::hide()
	{
		gcn::Window::setVisible(false);
	}

	bool WindowMenu::isVisible()
	{
		return gcn::Window::isVisible();
	}

	void WindowMenu::setSize(int width, int height)
	{
		gcn::Window::setSize(width, height);
	}

	void WindowMenu::setWidth(int width)
	{
		gcn::Window::setWidth(width);
	}

	void WindowMenu::setHeight(int height)
	{
		gcn::Window::setHeight(height);
	}

	void WindowMenu::setBorderSize(unsigned int size)
	{
		gcn::Window::setBorderSize(size);
	}

	void WindowMenu::setPosition(int x, int y)
	{
		gcn::Window::setPosition(x,y);
	}

	void WindowMenu::setX(int x)
	{
		gcn::Window::setX(x);
	}

	void WindowMenu::setY(int y)
	{
		gcn::Window::setY(y);
	}

	void WindowMenu::setCaption(const char * caption)
	{
		gcn::Window::setCaption(caption);
		if(font != 0)
			setTitleBarHeight(font->getHeight() + 2);
	}

	void WindowMenu::setTitleBarHeight(unsigned int height)
	{
		gcn::Window::setTitleBarHeight(height);
	}

	void WindowMenu::setFont(const pAbstractFont & font)
	{
		AbstractMenu::setFont(font);
		gcn::Window::setFont(this->font.get());
	}

	void WindowMenu::setBackgroundColor(const pAbstractColor & color)
	{
		AbstractMenu::setBackgroundColor(color);
	}

	int WindowMenu::getWidth()
	{
		return gcn::Window::getWidth();
	}

	int WindowMenu::getHeight()
	{
		return gcn::Window::getHeight();
	}

	int WindowMenu::getX()
	{
		return gcn::Window::getX();
	}

	int WindowMenu::getY()
	{
		return gcn::Window::getY();
	}

	unsigned int WindowMenu::getBorderSize()
	{
		return gcn::Window::getBorderSize();
	}

	const char * WindowMenu::getCaption()
	{
		return gcn::Window::getCaption().c_str();
	}

	unsigned int WindowMenu::getTitleBarHeight()
	{
		return gcn::Window::getTitleBarHeight();
	}

	pAbstractFont WindowMenu::getFont()
	{
		return font->getFont();
	}

	pAbstractColor WindowMenu::getBackgroundColor()
	{
		return AbstractMenu::getBackgroundColor();
	}

	void WindowMenu::adjustSize()
	{
		adjustWidth();
		adjustHeight();
	}

	void WindowMenu::adjustWidth()
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

	void WindowMenu::adjustHeight()
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

			break;
		case LOVE_MENU_HORIZONTAL:
			height = 0;

			for(iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(height < (*iter)->getHeight())
					height = (*iter)->getHeight();
			}
			
			height += getPaddingTop() + getPaddingBottom();

			break;
		}

		height += getTitleBarHeight();
		setHeight(height);

		//compensates for the background image
		if(background != 0)
		{
			if(getHeight() < background->getHeight())
				setHeight((int)background->getHeight());
		}
	}

	int WindowMenu::adjustContent()
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
				size += (*iter)->getHeight() + spacing + getTitleBarHeight();
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

		if(font != 0)
			setTitleBarHeight(font->getHeight() + 2);

		return size;
	}

	void WindowMenu::positionItem(gcn::Widget * item)
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

	void WindowMenu::draw(gcn::Graphics* graphics)
	{
		if(!visible) return;

		if(color != 0)
			gcn::Window::setForegroundColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
		if(backgroundColor != 0)
			gcn::Window::setBaseColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));

		gcn::Window::draw(graphics);
		return;

		//glPushMatrix();

		if(font != 0)
			graphics->setFont(font.get());

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

	void WindowMenu::drawBorder(gcn::Graphics* graphics)
	{
		if(!visible) return;

		if(borderColor != 0)
			gcn::Window::setBaseColor(gcn::Color(borderColor->getRed(), borderColor->getGreen(), borderColor->getBlue(), borderColor->getAlpha()));
		gcn::Window::drawBorder(graphics);
		return;

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

	void WindowMenu::drawChildren(gcn::Graphics* graphics)
	{
		gcn::Window::drawChildren(graphics);
	}

	void WindowMenu::add(gcn::Widget * widget)
	{
		gcn::Window::add(widget);
	}
}
