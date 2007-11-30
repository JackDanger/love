#include "DropDown.h"

namespace love
{
	int DropDown::getItemHeight()
	{
		return gcn::DropDown::getFont()->getHeight() + 2;
	}

	int DropDown::getItemAt(int x, int y)
	{
		if(x < 0 || x > getWidth() || y < 0 || y > getHeight() - mOldH) return -1;
		
		return y / getItemHeight();
	}

	DropDown::DropDown(GUIList * list) : gcn::DropDown()
	{
		setListModel(list);
		this->list = list;
		mCloseOnSelect = false;
		mHasMouse = false;
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

	void DropDown::setName(const string & name)
	{
		gcn::DropDown::setActionEventId(name);
	}

	void DropDown::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void DropDown::setListColor(const pAbstractColor & color)
	{
		listColor = color;
	}

	void DropDown::setListBackgroundColor(const pAbstractColor & color)
	{
		listBackgroundColor = color;
	}

	void DropDown::setHoverColor(const pAbstractColor & color)
	{
		hoverColor = color;
	}

	void DropDown::setHoverBackgroundColor(const pAbstractColor & color)
	{
		hoverBackgroundColor = color;
	}

	void DropDown::setSelectedColor(const pAbstractColor & color)
	{
		selectedColor = color;
	}

	void DropDown::setSelectedBackgroundColor(const pAbstractColor & color)
	{
		selectedBackgroundColor = color;
	}

	void DropDown::setButtonColor(const pAbstractColor & color)
	{
		buttonColor = color;
	}

	void DropDown::setButtonBackgroundColor(const pAbstractColor & color)
	{
		buttonBackgroundColor = color;
	}

	void DropDown::setButtonHoverColor(const pAbstractColor & color)
	{
		buttonHoverColor = color;
	}

	void DropDown::setButtonHoverBackgroundColor(const pAbstractColor & color)
	{
		buttonHoverBackgroundColor = color;
	}

	void DropDown::setButtonPressedColor(const pAbstractColor & color)
	{
		buttonPressedColor = color;
	}

	void DropDown::setButtonPressedBackgroundColor(const pAbstractColor & color)
	{
		buttonPressedBackgroundColor = color;
	}

	void DropDown::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::DropDown::setFont(this->font.get());
	}

	void DropDown::setBackgroundImage(const pAbstractImage & image)
	{
		backgroundImage = image;
	}

	void DropDown::setListImage(const pAbstractImage & image)
	{
		listImage = image;
	}

	void DropDown::setButton(const pAbstractImage & image)
	{
		button = image;
	}

	void DropDown::setButtonHover(const pAbstractImage & image)
	{
		buttonHover = image;
	}

	void DropDown::setButtonPressed(const pAbstractImage & image)
	{
		buttonPressed = image;
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

	const string & DropDown::getName()
	{
		return gcn::DropDown::getActionEventId();
	}

	void DropDown::adjustHeight()
	{
		int h = gcn::DropDown::getFont()->getHeight();

		if(backgroundImage != 0)
			h = backgroundImage->getHeight() > h ? (int)backgroundImage->getHeight() : h;
		if(button != 0)
			h = button->getHeight() > h ? (int)button->getHeight() : h;
		
		if(mDroppedDown)
		{
			int sh = getItemHeight() * (list->getNumberOfElements()); // +2 for a little spacing
			if(listImage != 0)
				sh = listImage->getHeight() > sh ? (int)listImage->getHeight() : sh;
			h += sh;
		}

		setHeight(h);
	}

	void DropDown::adjustSize()
	{
		adjustHeight();

		int w = 0;

		for(int i = 0; i < list->getNumberOfElements(); i++)
		{
			int t = gcn::DropDown::getFont()->getWidth(list->getElementAt(i));
			if(t > w)
				w = t;
		}

		if(backgroundImage != 0)
		{
			if(button != 0)
				w = (int)(backgroundImage->getWidth() + button->getWidth());
			else // if no button is present, the font height is used as a size determinant
				w = (int)backgroundImage->getWidth() + gcn::DropDown::getFont()->getHeight();
		}

		if(listImage != 0)
			w = listImage->getWidth() > w ? (int)listImage->getWidth() : w;

		if(w > getWidth())
			setWidth(w);
	}

	pAbstractColor DropDown::getListColor()
	{
		return listColor;
	}

	pAbstractColor DropDown::getListBackgroundColor()
	{
		return listBackgroundColor;
	}

	pAbstractColor DropDown::getHoverColor()
	{
		return hoverColor;
	}

	pAbstractColor DropDown::getHoverBackgroundColor()
	{
		return hoverBackgroundColor;
	}

	pAbstractColor DropDown::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor DropDown::getSelectedColor()
	{
		return selectedColor;
	}

	pAbstractColor DropDown::getSelectedBackgroundColor()
	{
		return selectedBackgroundColor;
	}

	pAbstractColor DropDown::getButtonColor()
	{
		return buttonColor;
	}

	pAbstractColor DropDown::getButtonBackgroundColor()
	{
		return buttonBackgroundColor;
	}

	pAbstractColor DropDown::getButtonHoverColor()
	{
		return buttonHoverColor;
	}

	pAbstractColor DropDown::getButtonHoverBackgroundColor()
	{
		return buttonHoverBackgroundColor;
	}

	pAbstractColor DropDown::getButtonPressedColor()
	{
		return buttonPressedColor;
	}

	pAbstractColor DropDown::getButtonPressedBackgroundColor()
	{
		return buttonPressedBackgroundColor;
	}

	pAbstractFont DropDown::getFont()
	{
		return GUIElement::getFont();
	}

	pAbstractImage DropDown::getBackgroundImage()
	{
		return backgroundImage;
	}

	pAbstractImage DropDown::getListImage()
	{
		return listImage;
	}

	pAbstractImage DropDown::getButton()
	{
		return button;
	}

	pAbstractImage DropDown::getButtonHover()
	{
		return buttonHover;
	}

	pAbstractImage DropDown::getButtonPressed()
	{
		return buttonPressed;
	}

	void DropDown::add(const string & text)
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

	string DropDown::getElementAt(int i)
	{
		if(i < 0 || i > list->getNumberOfElements())
			return "";
		return list->getElementAt(i);
	}
	
	int DropDown::getSelected()
	{
		return gcn::DropDown::getSelected();
	}

	void DropDown::setSelected(int selected)
	{
		gcn::DropDown::setSelected(selected);
	}

	string DropDown::getSelectedElement()
	{
		return getElementAt(getSelected());
	}

	int DropDown::getNumberOfElements()
	{
		return list->getNumberOfElements();
	}

	void DropDown::closeOnSelect(bool value)
	{
		mCloseOnSelect = value;
	}

	bool DropDown::closesOnSelect()
	{
		return mCloseOnSelect;
	}

	void DropDown::draw(gcn::Graphics * graphics)
	{
		if(backgroundColor != 0)
		{
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));
		}

		if(backgroundImage != 0)
		{
			graphics->setColor(gcn::Color(0xFFFFFF)); // to "clear" the background color
			backgroundImage->render((float)graphics->getCurrentClipArea().x, (float)graphics->getCurrentClipArea().y);
		}

		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(getForegroundColor());
		if(font != 0)
			graphics->setFont(font.get());

		if (mListBox->getSelected() >= 0)
			graphics->drawText(list->getElementAt(mListBox->getSelected()), 0, 0);

		drawButton(graphics);

		if(mDroppedDown)
			drawList(graphics);
	}

	void DropDown::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor != 0)
			gcn::DropDown::setBaseColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else if(backgroundColor != 0)
			gcn::DropDown::setBaseColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));

		gcn::DropDown::drawBorder(graphics);
	}

	void DropDown::drawList(gcn::Graphics * graphics)
	{
		int x = 0;
		int y = mOldH;

		if(listBackgroundColor != 0)
		{
			graphics->setColor(gcn::Color(listBackgroundColor->getRed(),listBackgroundColor->getGreen(),listBackgroundColor->getBlue(),listBackgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(0,mOldH,getWidth(),getHeight()));
		}

		if(listImage != 0)
		{
			graphics->setColor(gcn::Color(0xFFFFFF)); // to "clear" the background color
			listImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
		}

		if(listColor != 0)
			graphics->setColor(gcn::Color(listColor->getRed(),listColor->getGreen(),listColor->getBlue(),listColor->getAlpha()));
		else if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(getForegroundColor());

		for(int i = 0; i < list->getNumberOfElements(); i++)
		{
			if(mHoverSelect == i)
			{
				gcn::Color temp = graphics->getColor();
				if(hoverBackgroundColor != 0)
				{
					graphics->setColor(gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha()));
					graphics->fillRectangle(gcn::Rectangle(0,y,getWidth(),getItemHeight()));
					graphics->setColor(temp);
				}
				if(hoverColor != 0)
					graphics->setColor(gcn::Color(hoverColor->getRed(),hoverColor->getGreen(),hoverColor->getBlue(),hoverColor->getAlpha()));

				graphics->drawText(list->getElementAt(i), x, y);
				graphics->setColor(temp);
			}
			else if(getSelected() == i)
			{
				gcn::Color temp = graphics->getColor();
				if(selectedBackgroundColor != 0)
				{
					graphics->setColor(gcn::Color(selectedBackgroundColor->getRed(),selectedBackgroundColor->getGreen(),selectedBackgroundColor->getBlue(),selectedBackgroundColor->getAlpha()));
					graphics->fillRectangle(gcn::Rectangle(0,y,getWidth(),getItemHeight()));
					graphics->setColor(temp);
				}
				if(selectedColor != 0)
					graphics->setColor(gcn::Color(selectedColor->getRed(),selectedColor->getGreen(),selectedColor->getBlue(),selectedColor->getAlpha()));

				graphics->drawText(list->getElementAt(i), x, y);
				graphics->setColor(temp);
			}
			else
				graphics->drawText(list->getElementAt(i), x, y);
			y += gcn::DropDown::getFont()->getHeight() + 2;
		}
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
			if((mPushed || mDroppedDown) && buttonPressed != 0)
				buttonPressed->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			else if(mHasMouse && !mDroppedDown && buttonHover != 0)
				buttonHover->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
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

	void DropDown::mouseEntered(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = true;
	}

	void DropDown::mouseExited(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = false;
		mHoverSelect = -1;
	}

	void DropDown::mouseMoved(gcn::MouseEvent & mouseEvent)
	{
		int x = mouseEvent.getX();
		int y = mouseEvent.getY();

		if(x < 0 || x > getWidth() || y < 0 || y > getHeight()) return;

		mHoverSelect = getItemAt(x, y - mOldH);

		gcn::DropDown::mouseMoved(mouseEvent);
	}

	void DropDown::mousePressed(gcn::MouseEvent & mouseEvent)
	{        
		// If we have a mouse press on the widget.
		if (0 <= mouseEvent.getY()
			&& mouseEvent.getY() < getHeight()
			&& mouseEvent.getX() >= 0
			&& mouseEvent.getX() < getWidth()
			&& mouseEvent.getButton() == gcn::MouseEvent::LEFT
			&& !mDroppedDown
			&& mouseEvent.getSource() == this)
		{
			mPushed = true;
			dropDown();
			requestModalMouseInputFocus();
		}
		// Fold up the listbox if the upper part is clicked after fold down
		else if (0 <= mouseEvent.getY()
			&& mouseEvent.getY() < getHeight()
			&& mouseEvent.getX() >= 0
			&& mouseEvent.getX() < getWidth()
			&& mouseEvent.getButton() == gcn::MouseEvent::LEFT
			&& mDroppedDown
			&& mouseEvent.getSource() == this)
		{
			if(mouseEvent.getY() < mOldH)
			{
				mPushed = false;
				foldUp();
				releaseModalMouseInputFocus();
			}

			int select = getItemAt(mouseEvent.getX(), mouseEvent.getY() - mOldH);
			if(select != -1 && select < list->getNumberOfElements())
			{
				gcn::DropDown::setSelected(select);
				if(mCloseOnSelect)
				{
					mHasMouse = false;
					mPushed = false;
					foldUp();
					releaseModalMouseInputFocus();
				}
			}
		}
		// If we have a mouse press outside the widget
		else if (0 > mouseEvent.getY()
			|| mouseEvent.getY() >= getHeight()
			|| mouseEvent.getX() < 0
			|| mouseEvent.getX() >= getWidth())
		{
			mHasMouse = false;
			mPushed = false;
			foldUp();
		}
	}
}
