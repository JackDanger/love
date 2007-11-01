#include "ListBox.h"

namespace love
{
	ListBox::ListBox(GUIList * list) : gcn::ListBox()
	{
		setListModel(list);
		this->list = list;
	}

	ListBox::~ListBox()
	{
		if(list != 0)
			delete list;
	}

	void ListBox::setSize(int width, int height)
	{
		gcn::ListBox::setSize(width, height);
	}

	void ListBox::setWidth(int width)
	{
		gcn::ListBox::setWidth(width);
	}

	void ListBox::setHeight(int height)
	{
		gcn::ListBox::setHeight(height);
	}

	void ListBox::setBorderSize(unsigned int size)
	{
		gcn::ListBox::setBorderSize(size);
	}

	void ListBox::setName(const char * name)
	{
		gcn::ListBox::setActionEventId(name);
	}

	void ListBox::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void ListBox::setSelectionColor(const pAbstractColor * color)
	{
		this->selectionColor = (*color);
	}

	void ListBox::setSelectionBackgroundColor(const pAbstractColor * color)
	{
		this->selectionBackgroundColor = (*color);
	}

	int ListBox::getWidth()
	{
		return gcn::ListBox::getWidth();
	}

	int ListBox::getHeight()
	{
		return gcn::ListBox::getHeight();
	}

	unsigned int ListBox::getBorderSize()
	{
		return gcn::ListBox::getBorderSize();
	}

	const char * ListBox::getName()
	{
		return gcn::ListBox::getActionEventId().c_str();
	}

	pAbstractColor ListBox::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor ListBox::getSeclectionColor()
	{
		return selectionColor;
	}

	pAbstractColor ListBox::getSeclectionBackgroundColor()
	{
		return selectionBackgroundColor;
	}

	void ListBox::adjustSize()
	{
		gcn::ListBox::adjustSize();
	}

	void ListBox::add(const char * text)
	{
		list->add(text);
	}

	void ListBox::remove(int i)
	{
		list->remove(i);
	}

	void ListBox::clear()
	{
		list->clear();
	}

	const char * ListBox::getElementAt(int i)
	{
		return list->getElementAt(i).c_str();
	}
	
	int ListBox::getSelected()
	{
		return gcn::ListBox::getSelected();
	}

	const char * ListBox::getSelectedElement()
	{
		return list->getElementAt(getSelected()).c_str();
	}

	int ListBox::getNumberOfElements()
	{
		return list->getNumberOfElements();
	}

	void ListBox::draw(gcn::Graphics * graphics)
	{
		if(color != 0)
			gcn::ListBox::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		if(backgroundColor != 0)
			gcn::ListBox::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		if(selectionBackgroundColor != 0)
			gcn::ListBox::setSelectionColor(gcn::Color(selectionBackgroundColor->getRed(),selectionBackgroundColor->getGreen(),selectionBackgroundColor->getBlue(),selectionBackgroundColor->getAlpha()));
		
		// (almost) straight rip from gcn::ListBox::draw()
		graphics->setColor(gcn::ListBox::getBackgroundColor());
		graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
		
		if (mListModel == NULL)
		{
			return;
		}
		
		graphics->setColor(getForegroundColor());
		graphics->setFont(getFont());
		
		int i, fontHeight;
		int y = 0;
		
		fontHeight = getFont()->getHeight();
		
		for (i = 0; i < mListModel->getNumberOfElements(); ++i)
		{
			if (i == mSelected)
			{
				graphics->setColor(getSelectionColor());
				graphics->fillRectangle(gcn::Rectangle(0, y, getWidth(), fontHeight));
				if(selectionColor != 0)
					graphics->setColor(gcn::Color(selectionColor->getRed(),selectionColor->getGreen(),selectionColor->getBlue(),selectionColor->getAlpha()));
				graphics->drawText(mListModel->getElementAt(i), 1, y);
				graphics->setColor(getForegroundColor());
			}
			else
				graphics->drawText(mListModel->getElementAt(i), 1, y);
			
			y += fontHeight;
		}
	}

	void ListBox::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor != 0)
			gcn::ListBox::setBaseColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		gcn::ListBox::drawBorder(graphics);
	}
}