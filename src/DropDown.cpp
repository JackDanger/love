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

	void DropDown::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void DropDown::setActiveColor(const pAbstractColor * color)
	{
		if(color != 0)
			activeColor = *color;
	}

	void DropDown::setActiveBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			activeBackgroundColor = *color;
	}

	void DropDown::setSelectionColor(const pAbstractColor * color)
	{
		if(color != 0)
			selectionColor = *color;
	}

	void DropDown::setSelectionBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			selectionBackgroundColor = *color;
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

	void DropDown::setButton(const pAbstractImage * image)
	{
		this->button = (*image);
	}

	void DropDown::setButtonPressed(const pAbstractImage * image)
	{
		this->buttonPressed = (*image);
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
		if(getHeight() < button->getHeight())
			setHeight((int)button->getHeight());
	}

	pAbstractColor DropDown::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor DropDown::getActiveColor()
	{
		return activeColor;
	}

	pAbstractColor DropDown::getActiveBackgroundColor()
	{
		return activeBackgroundColor;
	}

	pAbstractColor DropDown::getSelectionColor()
	{
		return selectionColor;
	}

	pAbstractColor DropDown::getSelectionBackgroundColor()
	{
		return selectionBackgroundColor;
	}

	pAbstractColor DropDown::getButtonColor()
	{
		return buttonColor;
	}

	pAbstractColor DropDown::getButtonBackgroundColor()
	{
		return buttonBackgroundColor;
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

	const char * DropDown::getElementAt(int i)
	{
		return list->getElementAt(i).c_str();
	}
	
	int DropDown::getSelected()
	{
		return gcn::DropDown::getSelected();
	}

	const char * DropDown::getSelectedElement()
	{
		return list->getElementAt(getSelected()).c_str();
	}

	int DropDown::getNumberOfElements()
	{
		return list->getNumberOfElements();
	}

	void DropDown::draw(gcn::Graphics * graphics)
	{
		if(color != 0)
			gcn::DropDown::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		if(backgroundColor != 0)
			gcn::DropDown::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		if(activeBackgroundColor != 0)
			gcn::DropDown::setSelectionColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		if(selectionColor != 0 || selectionBackgroundColor != 0)
		{
			WidgetListIterator iter;
			for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
			{
				if(selectionColor != 0)
					(*iter)->setForegroundColor(gcn::Color(selectionColor->getRed(),selectionColor->getGreen(),selectionColor->getBlue(),selectionColor->getAlpha()));
				if(selectionBackgroundColor != 0)
					(*iter)->setSelectionColor(gcn::Color(selectionBackgroundColor->getRed(),selectionBackgroundColor->getGreen(),selectionBackgroundColor->getBlue(),selectionBackgroundColor->getAlpha()));
			}
		}
		gcn::DropDown::setBaseColor(gcn::DropDown::getBackgroundColor());

		gcn::DropDown::draw(graphics);
	}

	void DropDown::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor != 0)
			gcn::DropDown::setBaseColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else if(backgroundColor != 0)
			gcn::DropDown::setBaseColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		/*else if(color != 0)
			gcn::DropDown::setBaseColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));*/

		gcn::DropDown::drawBorder(graphics);
	}

	void DropDown::drawButton(gcn::Graphics *graphics)
	{
		if(button != 0)
		{
			int x = getWidth();
			if (mDroppedDown)
				x -= mOldH;
			else
				x -= getHeight();
			int y = 0;
			if(mPushed && buttonPressed != 0)
				buttonPressed->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			else
				button->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
		}
		else
		{
			if(buttonColor != 0)
				gcn::DropDown::setForegroundColor(gcn::Color(buttonColor->getRed(),buttonColor->getGreen(),buttonColor->getBlue(),buttonColor->getAlpha()));
			if(buttonBackgroundColor != 0)
				gcn::DropDown::setBaseColor(gcn::Color(buttonBackgroundColor->getRed(),buttonBackgroundColor->getGreen(),buttonBackgroundColor->getBlue(),buttonBackgroundColor->getAlpha()));
			else
				setBaseColor(gcn::DropDown::getBackgroundColor());

			gcn::DropDown::drawButton(graphics);
		}
	}
}
