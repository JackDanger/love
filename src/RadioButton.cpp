#include "RadioButton.h"

namespace love
{
	RadioButton::RadioButton(const string caption)
	{
		gcn::RadioButton();
		gcn::RadioButton::setCaption(caption);
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

	void RadioButton::setCaption(const char * caption)
	{
		gcn::RadioButton::setCaption(caption);
	}

	void RadioButton::setName(const char * name)
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

	void RadioButton::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void RadioButton::setDefaultImage(const pAbstractImage * image)
	{
		this->defaultImage = *image;
	}

	void RadioButton::setMarkedImage(const pAbstractImage * image)
	{
		this->markedImage = *image;
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

	const char * RadioButton::getCaption()
	{
		return gcn::RadioButton::getCaption().c_str();
	}

	const char * RadioButton::getName()
	{
		return gcn::RadioButton::getActionEventId().c_str();
	}

	bool RadioButton::isMarked()
	{
		return gcn::RadioButton::isMarked();
	}

	pAbstractColor RadioButton::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractImage RadioButton::getDefaultImage()
	{
		return defaultImage;
	}

	pAbstractImage RadioButton::getMarkedImage()
	{
		return markedImage;
	}

	void RadioButton::adjustSize()
	{
		gcn::RadioButton::adjustSize();
	}

	void RadioButton::draw(gcn::Graphics * graphics)
	{
		if(color != 0)
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
		
		graphics->setFont(getFont());
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
			else
			{
				pad = (graphics->getCurrentClipArea().height / 2) - (int)(defaultImage->getHeight() / 2);
				defaultImage->render((float)graphics->getCurrentClipArea().x + pad, (float)graphics->getCurrentClipArea().y + pad);
			}
		}
		else
			gcn::RadioButton::drawBox(graphics);
	}
}