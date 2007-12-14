#include "ListBox.h"

using std::string;

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

	void ListBox::setName(const string & name)
	{
		gcn::ListBox::setActionEventId(name);
	}

	void ListBox::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void ListBox::setSelectionColor(const pAbstractColor & color)
	{
		this->selectionColor = color;
	}

	void ListBox::setSelectionBackgroundColor(const pAbstractColor & color)
	{
		this->selectionBackgroundColor = color;
	}

	void ListBox::setBackgroundImage(const pAbstractImage & image)
	{
		backgroundImage = image;
	}

	void ListBox::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::ListBox::setFont(this->font.get());
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

	const string & ListBox::getName()
	{
		return gcn::ListBox::getActionEventId();
	}

	pAbstractColor ListBox::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor ListBox::getSelectionColor()
	{
		return selectionColor;
	}

	pAbstractColor ListBox::getSelectionBackgroundColor()
	{
		return selectionBackgroundColor;
	}

	pAbstractImage ListBox::getBackgroundImage()
	{
		return backgroundImage;
	}

	pAbstractFont ListBox::getFont()
	{
		return GUIElement::getFont();
	}

	void ListBox::adjustSize()
	{
		gcn::ListBox::adjustSize();

		if(backgroundImage != 0)
		{
			if(getWidth() < backgroundImage->getWidth())
				setWidth((int)backgroundImage->getWidth());
			if(getHeight() < backgroundImage->getHeight())
				setHeight((int)backgroundImage->getHeight());
		}
	}

	void ListBox::add(const string & text)
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

	string ListBox::getElementAt(int i)
	{
		return list->getElementAt(i);
	}
	
	int ListBox::getSelected()
	{
		return gcn::ListBox::getSelected();
	}

	string ListBox::getSelectedElement()
	{
		return list->getElementAt(getSelected());
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

		if(backgroundImage != 0)
		{
			graphics->setColor(gcn::Color(0xFFFFFF)); // to remove the effects of the background color
			backgroundImage->render((float)graphics->getCurrentClipArea().x, (float)graphics->getCurrentClipArea().y);
		}
		
		if (mListModel == NULL)
		{
			return;
		}
		
		graphics->setColor(getForegroundColor());
		graphics->setFont(font.get());
		
		int i, fontHeight;
		int y = 0;
		
		fontHeight = ((int)getFont()->getHeight());
		
		for (i = 0; i < mListModel->getNumberOfElements(); ++i)
		{
			if (i == mSelected)
			{
				graphics->setColor(gcn::ListBox::getSelectionColor());
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
