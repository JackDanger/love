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

		color = 0;
		backgroundColor = 0;
		activeColor = 0;
		activeBackgroundColor = 0;
		selectionBackgroundColor = 0;
		borderColor = 0;
		buttonColor = 0;
		buttonBackgroundColor = 0;
	}

	DropDown::~DropDown()
	{
	}

	void DropDown::setColor(AbstractColor * color)
	{
		if(color != 0)
			this->color = color;
	}

	void DropDown::setActiveColor(AbstractColor * color)
	{
		if(color != 0)
			activeColor = color;
	}

	void DropDown::setBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			backgroundColor = color;
	}

	void DropDown::setActiveBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			activeBackgroundColor = color;
	}

	void DropDown::setSelectionBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			selectionBackgroundColor = color;
	}

	void DropDown::setBorderColor(AbstractColor * color)
	{
		if(color != 0)
			borderColor = color;
	}

	void DropDown::setButtonColor(AbstractColor * color)
	{
		if(color != 0)
			buttonColor = color;
	}

	void DropDown::setButtonBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			buttonBackgroundColor = color;
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
		if(color != 0)
			gcn::DropDown::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		if(backgroundColor != 0)
			gcn::DropDown::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		if(activeBackgroundColor != 0)
			gcn::DropDown::setSelectionColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		if(selectionBackgroundColor != 0)
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
		
		if(borderColor != 0)
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
		if(buttonBackgroundColor != 0)
			setBaseColor(gcn::Color(buttonBackgroundColor->getRed(),buttonBackgroundColor->getGreen(),buttonBackgroundColor->getBlue(),buttonBackgroundColor->getAlpha()));

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
		
		if(borderColor != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(getForegroundColor());
		//graphics->drawLine(x, y, x+h-1, y);
		graphics->drawLine(x, y, x, y+h);
		
		//graphics->setColor(shadowColor);
		//graphics->drawLine(x+h-1, y+1, x+h-1, y+h-1);
		//graphics->drawLine(x+1, y+h-1, x+h-2, y+h-1);
		
		if(buttonColor != 0)
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