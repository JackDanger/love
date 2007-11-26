#include "CheckBox.h"

namespace love
{
	CheckBox::CheckBox(const string caption)
	{
		gcn::CheckBox();
		gcn::CheckBox::setCaption(caption);
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

	void CheckBox::setCaption(const char * caption)
	{
		gcn::CheckBox::setCaption(caption);
	}

	void CheckBox::setName(const char * name)
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

	void CheckBox::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void CheckBox::setDefaultImage(const pAbstractImage * image)
	{
		if(image == 0)
			defaultImage.reset();
		else
			defaultImage = *image;
	}

	void CheckBox::setMarkedImage(const pAbstractImage * image)
	{
		if(image == 0)
			markedImage.reset();
		else
			markedImage = *image;
	}

	void CheckBox::setFont(const pAbstractFont * font)
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

	const char * CheckBox::getCaption()
	{
		return gcn::CheckBox::getCaption().c_str();
	}

	const char * CheckBox::getName()
	{
		return gcn::CheckBox::getActionEventId().c_str();
	}

	bool CheckBox::isMarked()
	{
		return gcn::CheckBox::isMarked();
	}

	pAbstractColor CheckBox::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractImage CheckBox::getDefaultImage()
	{
		return defaultImage;
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
		if(color.get() != 0)
		{
			setBaseColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
			setForegroundColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
		}
		if(backgroundColor.get() != 0)
			gcn::CheckBox::setBackgroundColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));

		gcn::CheckBox::draw(graphics);
	}

	void CheckBox::drawBorder(gcn::Graphics * graphics)
	{
		if(borderColor.get() != 0)
			setBaseColor(gcn::Color(borderColor->getRed(), borderColor->getGreen(), borderColor->getBlue(), borderColor->getAlpha()));

		gcn::CheckBox::drawBorder(graphics);
	}

	void CheckBox::drawBox(gcn::Graphics * graphics)
	{
		if(defaultImage.get() != 0)
		{
			int pad = 0; // the padding around the image depending on the size
			if(isMarked() && markedImage.get() != 0)
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
			gcn::CheckBox::drawBox(graphics);
	}
}
