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

	void ListBox::setActiveColor(const pAbstractColor * color)
	{
		this->activeColor = (*color);
	}

	void ListBox::setActiveColor(const pColor * color)
	{
		this->activeColor = (*color);
	}

	void ListBox::setActiveColor(const pAnimatedColor * color)
	{
		this->activeColor = (*color);
	}

	void ListBox::setSelectionColor(const pAbstractColor * color)
	{
		this->selectionColor = (*color);
	}

	void ListBox::setSelectionColor(const pColor * color)
	{
		this->selectionColor = (*color);
	}

	void ListBox::setSelectionColor(const pAnimatedColor * color)
	{
		this->selectionColor = (*color);
	}

	const pAbstractColor * ListBox::getActiveColor()
	{
		return &activeColor;
	}

	const pAbstractColor * ListBox::getSeclectionColor()
	{
		return &selectionColor;
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

	void ListBox::draw(gcn::Graphics * graphics)
	{
		if(color.get() != 0)
			gcn::ListBox::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		if(backgroundColor.get() != 0)
			gcn::ListBox::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		if(selectionColor.get() != 0)
			gcn::ListBox::setSelectionColor(gcn::Color(selectionColor->getRed(),selectionColor->getGreen(),selectionColor->getBlue(),selectionColor->getAlpha()));
		
		gcn::ListBox::draw(graphics);
	}

	void ListBox::drawBorder(gcn::Graphics * graphics)
	{
		gcn::ListBox::drawBorder(graphics);
	}
}