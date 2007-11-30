#include "CheckBox.h"

namespace love
{
	CheckBox::CheckBox(const string & caption) : gcn::CheckBox(caption)
	{
		mHasMouse = false;
	}

	CheckBox::~CheckBox()
	{}

	void CheckBox::setSize(int width, int height)
	{
		gcn::CheckBox::setSize(width, height);
	}

	void CheckBox::setWidth(int width)
	{
		gcn::CheckBox::setWidth(width);
	}

	void CheckBox::setHeight(int height)
	{
		gcn::CheckBox::setHeight(height);
	}

	void CheckBox::setBorderSize(unsigned int size)
	{
		gcn::CheckBox::setBorderSize(size);
	}

	void CheckBox::setCaption(const string & caption)
	{
		gcn::CheckBox::setCaption(caption);
	}

	void CheckBox::setName(const string & name)
	{
		gcn::CheckBox::setActionEventId(name);
	}

	void CheckBox::setMarked(bool marked)
	{
		gcn::CheckBox::setMarked(marked);
	}

	void CheckBox::align(int alignment)
	{
		this->alignment = alignment;
	}

	void CheckBox::valign(int alignment)
	{
		this->verticalAlignment = alignment;
	}

	void CheckBox::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void CheckBox::setHoverColor(const pAbstractColor & color)
	{
		hoverColor = color;
	}

	void CheckBox::setMarkedColor(const pAbstractColor & color)
	{
		markedColor = color;
	}

	void CheckBox::setDefaultImage(const pAbstractImage & image)
	{
		defaultImage = image;
	}

	void CheckBox::setHoverImage(const pAbstractImage & image)
	{
		hoverImage = image;
	}

	void CheckBox::setMarkedImage(const pAbstractImage & image)
	{
		markedImage = image;
	}

	void CheckBox::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::CheckBox::setFont(this->font.get());
	}

	int CheckBox::getWidth()
	{
		return gcn::CheckBox::getWidth();
	}

	int CheckBox::getHeight()
	{
		return gcn::CheckBox::getHeight();
	}

	unsigned int CheckBox::getBorderSize()
	{
		return gcn::CheckBox::getBorderSize();
	}

	const string & CheckBox::getCaption()
	{
		return gcn::CheckBox::getCaption();
	}

	const string & CheckBox::getName()
	{
		return gcn::CheckBox::getActionEventId();
	}

	bool CheckBox::isMarked()
	{
		return gcn::CheckBox::isMarked();
	}

	pAbstractColor CheckBox::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor CheckBox::getHoverColor()
	{
		return hoverColor;
	}

	pAbstractColor CheckBox::getMarkedColor()
	{
		return markedColor;
	}

	pAbstractImage CheckBox::getDefaultImage()
	{
		return defaultImage;
	}

	pAbstractImage CheckBox::getHoverImage()
	{
		return hoverImage;
	}

	pAbstractImage CheckBox::getMarkedImage()
	{
		return markedImage;
	}

	pAbstractFont CheckBox::getFont()
	{
		return GUIElement::getFont();
	}

	void CheckBox::adjustSize()
	{
		gcn::CheckBox::adjustSize();
	}

	void CheckBox::draw(gcn::Graphics * graphics)
	{
		if(isMarked() && markedColor != 0)
		{
			setBaseColor(gcn::Color(markedColor->getRed(), markedColor->getGreen(), markedColor->getBlue(), markedColor->getAlpha()));
			setForegroundColor(gcn::Color(markedColor->getRed(), markedColor->getGreen(), markedColor->getBlue(), markedColor->getAlpha()));
		}
		else if(mHasMouse && hoverColor != 0)
		{
			setBaseColor(gcn::Color(hoverColor->getRed(), hoverColor->getGreen(), hoverColor->getBlue(), hoverColor->getAlpha()));
			setForegroundColor(gcn::Color(hoverColor->getRed(), hoverColor->getGreen(), hoverColor->getBlue(), hoverColor->getAlpha()));
		}
		else if(color != 0)
		{
			setBaseColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
			setForegroundColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
		}
		if(backgroundColor != 0)
		{
			gcn::CheckBox::setBackgroundColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));
		}

		gcn::CheckBox::draw(graphics);
	}

	void CheckBox::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor != 0)
			setBaseColor(gcn::Color(borderColor->getRed(), borderColor->getGreen(), borderColor->getBlue(), borderColor->getAlpha()));

		gcn::CheckBox::drawBorder(graphics);
	}

	void CheckBox::drawBox(gcn::Graphics * graphics)
	{
		if(defaultImage != 0)
		{
			if(backgroundColor != 0)
			{
				graphics->setColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));
				graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));
			}
			int pad = 0; // the padding around the image depending on the size
			if(isMarked() && markedImage != 0)
			{
				pad = (graphics->getCurrentClipArea().height / 2) - (int)(markedImage->getHeight() / 2);
				markedImage->render((float)graphics->getCurrentClipArea().x + pad, (float)graphics->getCurrentClipArea().y + pad);
			}
			else if(mHasMouse && hoverImage != 0)
			{
				pad = (graphics->getCurrentClipArea().height / 2) - (int)(hoverImage->getHeight() / 2);
				hoverImage->render((float)graphics->getCurrentClipArea().x + pad, (float)graphics->getCurrentClipArea().y + pad);
			}
			else
			{
				pad = (graphics->getCurrentClipArea().height / 2) - (int)(defaultImage->getHeight() / 2);
				defaultImage->render((float)graphics->getCurrentClipArea().x + pad, (float)graphics->getCurrentClipArea().y + pad);
			}
		}
		else
			gcn::CheckBox::drawBox(graphics);
	}

	void CheckBox::mouseEntered(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = true;
	}

	void CheckBox::mouseExited(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = false;
	}
}
