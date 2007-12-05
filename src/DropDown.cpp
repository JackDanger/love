#include "DropDown.h"

namespace love
{
	int DropDown::getItemHeight()
	{
		return gcn::DropDown::getFont()->getHeight() + (spacing * 2);
	}

	int DropDown::getItemAt(int x, int y)
	{
		if(x < 0 || x > getWidth() || y < 0 || y > getHeight() - mOldH) return -1;
		
		return (y - getPaddingTop()) / getItemHeight();
	}

	DropDown::DropDown(GUIList * list) : gcn::DropDown(), Padded()
	{
		setListModel(list);
		this->list = list;
		mCloseOnSelect = false;
		mHasMouse = false;
		spacing = 0;
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

	void DropDown::setSpacing(int spacing)
	{
		this->spacing = spacing;
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

	void DropDown::setButtonImage(const pAbstractImage & image)
	{
		buttonImage = image;
	}

	void DropDown::setButtonHoverImage(const pAbstractImage & image)
	{
		buttonHoverImage = image;
	}

	void DropDown::setButtonPressedImage(const pAbstractImage & image)
	{
		buttonPressedImage = image;
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

	int DropDown::getSpacing()
	{
		return spacing;
	}

	void DropDown::adjustHeight()
	{
		int h = gcn::DropDown::getFont()->getHeight();

		if(backgroundImage != 0)
			h = backgroundImage->getHeight() > h ? (int)backgroundImage->getHeight() : h;
		if(buttonImage != 0)
			h = buttonImage->getHeight() > h ? (int)buttonImage->getHeight() : h;
		
		if(mDroppedDown)
		{
			int sh = getItemHeight() * (list->getNumberOfElements());
			sh += getPaddingTop() + getPaddingBottom() + getBorderSize(); // +borderSize because of the separating line
			if(listImage != 0)
				sh = listImage->getHeight() > sh ? (int)listImage->getHeight() : sh;
			h += sh; //why isn't this making the widget hueg???
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

		w += getPaddingLeft() + getPaddingRight() + (spacing * 2);

		if(backgroundImage != 0)
		{
			int t = (int)backgroundImage->getWidth();
			/*if(button != 0)
				t = (int)(backgroundImage->getWidth() + button->getWidth());
			else // if no button is present, the font height is used as a size determinant
				t = (int)backgroundImage->getWidth() + gcn::DropDown::getFont()->getHeight();*/
			if(t > w)
				w = t;
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

	pAbstractImage DropDown::getButtonImage()
	{
		return buttonImage;
	}

	pAbstractImage DropDown::getButtonHoverImage()
	{
		return buttonHoverImage;
	}

	pAbstractImage DropDown::getButtonPressedImage()
	{
		return buttonPressedImage;
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
		{
			int y;
			if(mDroppedDown)
				y = (int)((mOldH / 2) - (gcn::DropDown::getFont()->getHeight() / 2));
			else
				y = (int)((getHeight() / 2) - (gcn::DropDown::getFont()->getHeight() / 2));

			graphics->drawText(list->getElementAt(mListBox->getSelected()), getPaddingLeft() + spacing, y);
		}

		drawButton(graphics);

		if(mDroppedDown)
		{
			int width = getWidth() + getBorderSize() * 2 - 1;
			int height = mOldH + getBorderSize() - 1;

			if(borderColor != 0)
				graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
			else if(backgroundColor != 0)
				graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
			else
				graphics->setColor(getBaseColor());

			for(unsigned int i = 0; i < getBorderSize(); i++)
				graphics->drawLine(0,height - i, width - 1, height - i);

			drawList(graphics);
		}
	}

	void DropDown::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else if(backgroundColor != 0)
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		else
			graphics->setColor(getBaseColor());

		//gcn::DropDown::drawBorder(graphics);
		unsigned int i;
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		for (i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}

	void DropDown::drawList(gcn::Graphics * graphics)
	{
		int x = 0;
		int y = mOldH + getBorderSize();

		if(listBackgroundColor != 0)
		{
			graphics->setColor(gcn::Color(listBackgroundColor->getRed(),listBackgroundColor->getGreen(),listBackgroundColor->getBlue(),listBackgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(x,y,getWidth(),getHeight()));
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

		x = getPaddingLeft();
		y += getPaddingTop();

		for(int i = 0; i < list->getNumberOfElements(); i++)
		{
			if(mHoverSelect == i)
			{
				gcn::Color temp = graphics->getColor();
				if(hoverBackgroundColor != 0)
				{
					graphics->setColor(gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha()));
					graphics->fillRectangle(gcn::Rectangle(x, y, getWidth() - getPaddingLeft() - getPaddingRight(), getItemHeight()));
					graphics->setColor(temp);
				}
				if(hoverColor != 0)
					graphics->setColor(gcn::Color(hoverColor->getRed(),hoverColor->getGreen(),hoverColor->getBlue(),hoverColor->getAlpha()));

				graphics->drawText(list->getElementAt(i), x + spacing, y + spacing);
				graphics->setColor(temp);
			}
			else if(getSelected() == i)
			{
				gcn::Color temp = graphics->getColor();
				if(selectedBackgroundColor != 0)
				{
					graphics->setColor(gcn::Color(selectedBackgroundColor->getRed(),selectedBackgroundColor->getGreen(),selectedBackgroundColor->getBlue(),selectedBackgroundColor->getAlpha()));
					graphics->fillRectangle(gcn::Rectangle(x, y, getWidth() - getPaddingLeft() - getPaddingRight(), getItemHeight()));
					graphics->setColor(temp);
				}
				if(selectedColor != 0)
					graphics->setColor(gcn::Color(selectedColor->getRed(),selectedColor->getGreen(),selectedColor->getBlue(),selectedColor->getAlpha()));

				graphics->drawText(list->getElementAt(i), x + spacing, y + spacing);
				graphics->setColor(temp);
			}
			else
				graphics->drawText(list->getElementAt(i), x + spacing, y + spacing);
			y += getItemHeight();
		}
	}

	void DropDown::drawButton(gcn::Graphics *graphics)
	{
		if(buttonImage != 0)
		{
			int x = getWidth();
			if (mDroppedDown)
				x -= mOldH;
			else
				x -= getHeight();
			int y = 0;
			if((mPushed || mDroppedDown) && buttonPressedImage != 0)
				buttonPressedImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			else if(mHasMouse && !mDroppedDown && buttonHoverImage != 0)
				buttonHoverImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			else
				buttonImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
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
