#include "DropDown.h"

namespace love
{
	DropDown::DropDown(GUIList * list)
	{
		gcn::DropDown();
		setListModel(list);
		this->list = list;

		gcn::DropDown::setForegroundColor(gcn::Color(0,0,0,255));
		gcn::DropDown::setBackgroundColor(gcn::Color(255,255,255,255));
		gcn::DropDown::setSelectionColor(gcn::Color(255,255,255,255));
	}

	DropDown::~DropDown()
	{
	}

	void DropDown::setSize(int width, int height)
	{
		gcn::DropDown::setSize(width, height);
	}

	void DropDown::setWidth(int width)
	{
		gcn::DropDown::setWidth(width);
	}
	
	void DropDown::setHeight(int height)
	{
		gcn::DropDown::setHeight(height);
	}

	void DropDown::setBorderSize(unsigned int size)
	{
		gcn::DropDown::setBorderSize(size);
	}

	void DropDown::setName(const char * name)
	{
		gcn::DropDown::setActionEventId(name);
	}

	void DropDown::setColor(const pAbstractColor * color)
	{
		if(color != 0)
			this->color = *color;
	}

	void DropDown::setActiveColor(const pAbstractColor * color)
	{
		if(color != 0)
			activeColor = *color;
	}

	void DropDown::setBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			backgroundColor = *color;
	}

	void DropDown::setActiveBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			activeBackgroundColor = *color;
	}

	void DropDown::setSelectionBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			selectionBackgroundColor = *color;
	}

	void DropDown::setBorderColor(const pAbstractColor * color)
	{
		if(color != 0)
			borderColor = *color;
	}

	void DropDown::setButtonColor(const pAbstractColor * color)
	{
		if(color != 0)
			buttonColor = *color;
	}

	void DropDown::setButtonBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			buttonBackgroundColor = *color;
	}

	int DropDown::getWidth()
	{
		return gcn::DropDown::getWidth();
	}

	int DropDown::getHeight()
	{
		return gcn::DropDown::getHeight();
	}

	unsigned int DropDown::getBorderSize()
	{
		return gcn::DropDown::getBorderSize();
	}

	const char * DropDown::getName()
	{
		return gcn::DropDown::getActionEventId().c_str();
	}

	void DropDown::adjustSize()
	{
		gcn::DropDown::adjustHeight();
	}

	void DropDown::add(const char * text)
	{
		list->add(text);
	}

	void DropDown::remove(int i)
	{
		list->remove(i);
	}

	void DropDown::clear()
	{
		list->clear();
	}

	void DropDown::draw(gcn::Graphics * graphics)
	{
		if(color.get() != 0)
			gcn::DropDown::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		if(backgroundColor.get() != 0)
			gcn::DropDown::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		if(activeBackgroundColor.get() != 0)
			gcn::DropDown::setSelectionColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		if(selectionBackgroundColor.get() != 0)
		{
			WidgetListIterator iter;
			for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
				(*iter)->setSelectionColor(gcn::Color(selectionBackgroundColor->getRed(),selectionBackgroundColor->getGreen(),selectionBackgroundColor->getBlue(),selectionBackgroundColor->getAlpha()));
		}

		gcn::DropDown::draw(graphics);
	}

	void DropDown::drawBorder(gcn::Graphics * graphics)
	{
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;
		
		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(getForegroundColor());
		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}

	void DropDown::drawButton(gcn::Graphics *graphics)
	{
		if(buttonBackgroundColor.get() != 0)
			setBaseColor(gcn::Color(buttonBackgroundColor->getRed(),buttonBackgroundColor->getGreen(),buttonBackgroundColor->getBlue(),buttonBackgroundColor->getAlpha()));
		else
			setBaseColor(getBackgroundColor());

		gcn::Color faceColor, highlightColor, shadowColor;
		int offset;
		int alpha = getBaseColor().a;

		if (mPushed)
		{
			faceColor = getBaseColor() - 0x303030;
			faceColor.a = alpha;
			highlightColor = faceColor - 0x303030;
			highlightColor.a = alpha;
			shadowColor = faceColor + 0x303030;
			shadowColor.a = alpha;
			offset = 1;
		}
		else
		{
			faceColor = getBaseColor();
			faceColor.a = alpha;
			highlightColor = faceColor + 0x303030;
			highlightColor.a = alpha;
			shadowColor = faceColor - 0x303030;
			shadowColor.a = alpha;
			offset = 0;
		}
		
		int h;
		if (mDroppedDown)
		{
			h = mOldH;
		}
		else
		{
			h = getHeight();
		}
		int x = getWidth() - h;
		int y = 0;
		
		graphics->setColor(faceColor);
		graphics->fillRectangle(gcn::Rectangle(x, y, h, h));
		
		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(getForegroundColor());
		//graphics->drawLine(x, y, x+h-1, y);
		graphics->drawLine(x, y, x, y+h);
		
		//graphics->setColor(shadowColor);
		//graphics->drawLine(x+h-1, y+1, x+h-1, y+h-1);
		//graphics->drawLine(x+1, y+h-1, x+h-2, y+h-1);
		
		if(buttonColor.get() != 0)
			graphics->setColor(gcn::Color(buttonColor->getRed(),buttonColor->getGreen(),buttonColor->getBlue(),buttonColor->getAlpha()));
		else
			graphics->setColor(getForegroundColor());
		
		int i;
		int hh = h / 3;
		int hx = x + h / 2;
		int hy = y + (h * 2) / 3;
		for (i=0; i<hh; i++)
		{
			graphics->drawLine(hx - i + offset,
								hy - i + offset,
								hx + i + offset,
								hy - i + offset);
		}

		setBaseColor(getForegroundColor());
	}
}