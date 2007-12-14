#include "RadioButton.h"

using std::string;

namespace love
{
	RadioButton::RadioButton(const string & caption) : gcn::RadioButton()
	{
		gcn::RadioButton::setCaption(caption);
		mHasMouse = false;
	}

	RadioButton::~RadioButton()
	{}

	void RadioButton::setSize(int width, int height)
	{
		gcn::RadioButton::setSize(width, height);
	}

	void RadioButton::setWidth(int width)
	{
		gcn::RadioButton::setWidth(width);
	}

	void RadioButton::setHeight(int height)
	{
		gcn::RadioButton::setHeight(height);
	}

	void RadioButton::setBorderSize(unsigned int size)
	{
		gcn::RadioButton::setBorderSize(size);
	}

	void RadioButton::setCaption(const string & caption)
	{
		gcn::RadioButton::setCaption(caption);
	}

	void RadioButton::setName(const string & name)
	{
		gcn::RadioButton::setActionEventId(name);
	}

	void RadioButton::setMarked(bool marked)
	{
		gcn::RadioButton::setMarked(marked);
	}

	void RadioButton::align(int alignment)
	{
		this->alignment = alignment;
	}

	void RadioButton::valign(int alignment)
	{
		this->verticalAlignment = alignment;
	}

	void RadioButton::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void RadioButton::setHoverColor(const pAbstractColor & color)
	{
		hoverColor = color;
	}

	void RadioButton::setMarkedColor(const pAbstractColor & color)
	{
		markedColor = color;
	}

	void RadioButton::setDefaultImage(const pAbstractImage & image)
	{
		defaultImage = image;
	}

	void RadioButton::setHoverImage(const pAbstractImage & image)
	{
		hoverImage = image;
	}

	void RadioButton::setMarkedImage(const pAbstractImage & image)
	{
		markedImage = image;
	}

	void RadioButton::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::RadioButton::setFont(this->font.get());
	}

	int RadioButton::getWidth()
	{
		return gcn::RadioButton::getWidth();
	}

	int RadioButton::getHeight()
	{
		return gcn::RadioButton::getHeight();
	}

	unsigned int RadioButton::getBorderSize()
	{
		return gcn::RadioButton::getBorderSize();
	}

	const string & RadioButton::getCaption()
	{
		return gcn::RadioButton::getCaption();
	}

	const string & RadioButton::getName()
	{
		return gcn::RadioButton::getActionEventId();
	}

	bool RadioButton::isMarked()
	{
		return gcn::RadioButton::isMarked();
	}

	pAbstractColor RadioButton::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor RadioButton::getHoverColor()
	{
		return hoverColor;
	}

	pAbstractColor RadioButton::getMarkedColor()
	{
		return markedColor;
	}

	pAbstractImage RadioButton::getDefaultImage()
	{
		return defaultImage;
	}

	pAbstractImage RadioButton::getHoverImage()
	{
		return hoverImage;
	}

	pAbstractImage RadioButton::getMarkedImage()
	{
		return markedImage;
	}

	pAbstractFont RadioButton::getFont()
	{
		return GUIElement::getFont();
	}

	void RadioButton::adjustSize()
	{
		gcn::RadioButton::adjustSize();
	}

	void RadioButton::draw(gcn::Graphics * graphics)
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
			gcn::RadioButton::setBackgroundColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));

		// (almost) direct rip from gcn::RadioButton::draw()
		graphics->pushClipArea(gcn::Rectangle(1, 1, getWidth() - 1, getHeight() - 1));
		drawBox(graphics);
		graphics->popClipArea();
		
		graphics->setFont(font.get());
		graphics->setColor(getForegroundColor());
		
		int h = getHeight() + getHeight() / 2;
		graphics->drawText(getCaption(), h - 2, 0);
	}

	void RadioButton::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor.get() != 0)
			setBaseColor(gcn::Color(borderColor->getRed(), borderColor->getGreen(), borderColor->getBlue(), borderColor->getAlpha()));

		gcn::RadioButton::drawBorder(graphics);
	}

	void RadioButton::drawBox(gcn::Graphics * graphics)
	{
		if(defaultImage != 0)
		{
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
			gcn::RadioButton::drawBox(graphics);
	}

	void RadioButton::mouseEntered(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = true;
	}

	void RadioButton::mouseExited(gcn::MouseEvent & mouseEvent)
	{
		mHasMouse = false;
	}
}
