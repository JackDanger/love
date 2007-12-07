#include "TextField.h"

namespace love
{
	TextField::TextField(const string & text) : gcn::TextField(text)
	{
		//gcn::TextField();
		//gcn::TextField::setText(text);
	}

	TextField::~TextField()
	{ }

	void TextField::setSize(int width, int height)
	{
		gcn::TextField::setSize(width, height);
	}

	void TextField::setWidth(int width)
	{
		gcn::TextField::setWidth(width);
	}

	void TextField::setHeight(int height)
	{
		gcn::TextField::setHeight(height);
	}

	void TextField::setBorderSize(unsigned int size)
	{
		gcn::TextField::setBorderSize(size);
	}

	void TextField::setText(const string & text)
	{
		gcn::TextField::setText(text);
	}

	void TextField::setName(const string & name)
	{
		gcn::TextField::setActionEventId(name);
	}

	void TextField::setCaretPosition(unsigned int position)
	{
		gcn::TextField::setCaretPosition(position);
	}

	void TextField::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void TextField::setActiveColor(const pAbstractColor & color)
	{
		activeColor = color;
	}

	void TextField::setActiveBackgroundColor(const pAbstractColor & color)
	{
		activeBackgroundColor = color;
	}

	void TextField::setBackgroundImage(const pAbstractImage & image)
	{
		backgroundImage = image;
	}

	void TextField::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::TextField::setFont(this->font.get());
	}

	int TextField::getWidth()
	{
		return gcn::TextField::getWidth();
	}

	int TextField::getHeight()
	{
		return gcn::TextField::getHeight();
	}

	unsigned int TextField::getBorderSize()
	{
		return gcn::TextField::getBorderSize();
	}

	const string & TextField::getText()
	{
		return gcn::TextField::getText();
	}

	const string & TextField::getName()
	{
		return gcn::TextField::getActionEventId();
	}

	unsigned int TextField::getCaretPosition()
	{
		return gcn::TextField::getCaretPosition();
	}

	pAbstractColor TextField::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor TextField::getActiveColor()
	{
		return activeColor;
	}

	pAbstractColor TextField::getActiveBackgroundColor()
	{
		return activeBackgroundColor;
	}

	pAbstractImage TextField::getBackgroundImage()
	{
		return backgroundImage;
	}

	pAbstractFont TextField::getFont()
	{
		return GUIElement::getFont();
	}

	void TextField::adjustSize()
	{
		gcn::TextField::adjustSize();

		if(backgroundImage != 0)
		{
			if(backgroundImage->getWidth() > getWidth())
				setWidth((int)backgroundImage->getWidth());
		}
	}

	void TextField::adjustHeight()
	{
		gcn::TextField::adjustHeight();

		if(backgroundImage != 0)
		{
			if(backgroundImage->getHeight() > getHeight())
				setHeight((int)backgroundImage->getHeight());
		}
	}

	void TextField::keyPressed(gcn::KeyEvent& keyEvent)
	{
		gcn::TextField::keyPressed(keyEvent);
		fixScroll();
	}

	void TextField::mousePressed(gcn::MouseEvent& mouseEvent)
	{
		if (mouseEvent.getButton() == gcn::MouseEvent::LEFT)
		{
			mCaretPosition = gcn::TextField::getFont()->getStringIndexAt(mText, mouseEvent.getX() + mXScroll - getPaddingLeft() - 4);
			fixScroll();
		}
	}

	void TextField::fixScroll()
	{
		int m = 5;
		if (isFocused())
		{
			int caretX = gcn::TextField::getFont()->getWidth(mText.substr(0, mCaretPosition));
			
			if (caretX - mXScroll > getWidth() - getPaddingLeft() - getPaddingRight() - 4)
			{
				mXScroll = caretX - getWidth() + getPaddingLeft() + getPaddingRight() + 4;
			}
			else if (caretX - mXScroll < getFont()->getWidth(" "))
			{
				mXScroll = caretX - gcn::TextField::getFont()->getWidth(" ");
				
				if (mXScroll < 0)
				{
					mXScroll = 0;
				}
			}
		}
	}

	void TextField::draw(gcn::Graphics* graphics)
	{
		if(getFont() != 0)
			graphics->setFont(font.get());
		else
			graphics->setFont(gcn::TextField::getFont());

		if(isFocused() && activeBackgroundColor != 0)
			graphics->setColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		else if(backgroundColor != 0)
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		else
			graphics->setColor(gcn::TextField::getBackgroundColor());

		graphics->fillRectangle(gcn::Rectangle(1, 0, getWidth(), getHeight()));

		if(backgroundImage)
		{
			float x = (getWidth() / 2) - (backgroundImage->getWidth() / 2) + 2;
			float y = (getHeight() / 2) - (backgroundImage->getHeight() / 2);

			backgroundImage->render(graphics->getCurrentClipArea().x + x, graphics->getCurrentClipArea().y + y);
		}

		if(isFocused() && activeColor != 0)
			graphics->setColor(gcn::Color(activeColor->getRed(),activeColor->getGreen(),activeColor->getBlue(),activeColor->getAlpha()));
		else if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::TextField::getForegroundColor());

		graphics->pushClipArea(gcn::Rectangle(getPaddingLeft(), getPaddingTop(), getWidth() - getPaddingLeft() - getPaddingRight(), getHeight() - getPaddingTop() - getPaddingBottom()));

		if(isFocused())
		{
			int x = gcn::TextField::getFont()->getWidth(mText.substr(0, mCaretPosition)) - mXScroll + 2;
			graphics->drawLine(x, getHeight() - 2, x, 1);
		}

		int y = (int)((getHeight() / 2) - (gcn::TextField::getFont()->getHeight() / 2));

		graphics->drawText(mText, 2 - mXScroll, y);

		graphics->popClipArea();
	}

	void TextField::drawBorder(gcn::Graphics* graphics)
	{
		if(borderColor != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else if(backgroundColor != 0)
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		else
			graphics->setColor(getBaseColor());

		//gcn::TextField::drawBorder(graphics);
		unsigned int i;
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		for (i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i+1,i + 1, i+1, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i, height - i);
		}
	}
}
