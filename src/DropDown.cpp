#include "DropDown.h"

namespace love
{
	DropDown::DropDown(GUIList * list)
	{
		gcn::DropDown();
		setListModel(list);
		this->list = list;

		//gcn::DropDown::setBaseColor(gcn::Color(0,0,0,255));
		//gcn::DropDown::setForegroundColor(gcn::Color(0,0,0,255));
		//gcn::DropDown::setBackgroundColor(gcn::Color(255,255,255,255));
		//gcn::DropDown::setSelectionColor(gcn::Color(255,255,255,255));
	}

	DropDown::~DropDown()
	{
		if(list != 0)
			delete list;
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
		{
			gcn::DropDown::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		}
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
		gcn::DropDown::setBaseColor(getBackgroundColor());

		gcn::DropDown::draw(graphics);
	}

	void DropDown::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor.get() != 0)
			gcn::DropDown::setBaseColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else if(backgroundColor.get() != 0)
			gcn::DropDown::setBaseColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		/*else if(color.get() != 0)
			gcn::DropDown::setBaseColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));*/

		gcn::DropDown::drawBorder(graphics);
	}

	void DropDown::drawButton(gcn::Graphics *graphics)
	{
		if(buttonColor.get() != 0)
			gcn::DropDown::setBaseColor(gcn::Color(buttonColor->getRed(),buttonColor->getGreen(),buttonColor->getBlue(),buttonColor->getAlpha()));
		else
			setBaseColor(getBackgroundColor());

		gcn::DropDown::drawButton(graphics);
	}
}