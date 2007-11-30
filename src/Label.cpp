#include "Label.h"

namespace love
{
	Label::Label(const string & caption) : gcn::Label(caption)
	{
		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
	}

	Label::~Label()
	{
	}

	void Label::setSize(int width, int height)
	{
		gcn::Label::setSize(width, height);
	}

	void Label::setWidth(int width)
	{
		gcn::Label::setWidth(width);
	}

	void Label::setHeight(int height)
	{
		gcn::Label::setHeight(height);
	}

	void Label::setBorderSize(unsigned int size)
	{
		gcn::Label::setBorderSize(size);
	}

	void Label::setCaption(const string & caption)
	{
		gcn::Label::setCaption(caption);
	}

	void Label::setBackgroundColor(const pAbstractColor & color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void Label::setFont(const pAbstractFont & font)
	{
		GUIElement::setFont(font);
		gcn::Label::setFont(this->font.get());
	}

	void Label::align(int alignment)
	{
		switch(alignment)
		{
		default:
		case Text::LOVE_ALIGN_LEFT:
			setAlignment(gcn::Graphics::LEFT);
			break;
		case Text::LOVE_ALIGN_CENTER:
			setAlignment(gcn::Graphics::CENTER);
			break;
		case Text::LOVE_ALIGN_RIGHT:
			setAlignment(gcn::Graphics::RIGHT);
			break;
		}
	}

	void Label::valign(int alignment)
	{
		verticalAlignment = alignment;
	}

	void Label::setBackgroundImage(const pAbstractImage & image)
	{
		backgroundImage = image;
	}

	int Label::getWidth()
	{
		return gcn::Label::getWidth();
	}

	int Label::getHeight()
	{
		return gcn::Label::getHeight();
	}

	unsigned int Label::getBorderSize()
	{
		return gcn::Label::getBorderSize();
	}

	const string & Label::getCaption()
	{
		return gcn::Label::getCaption();
	}

	pAbstractColor Label::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractImage Label::getBackgroundImage()
	{
		return backgroundImage;
	}

	pAbstractFont Label::getFont()
	{
		return GUIElement::getFont();
	}

	void Label::adjustSize()
	{
		setWidth(gcn::Label::getFont()->getWidth(getCaption()));
		setHeight(gcn::Label::getFont()->getHeight() + 2);

		if(backgroundImage != 0)
		{
			if(getWidth() < backgroundImage->getWidth())
				setWidth((int)backgroundImage->getWidth());
			if(getHeight() < backgroundImage->getHeight())
				setHeight((int)backgroundImage->getHeight());
		}
	}

	void Label::draw(gcn::Graphics* graphics)
	{
		int x = 0;
		int y = 0;

		if(font != 0)
			gcn::Label::setFont(font.get());
		if(backgroundColor != 0)
		{
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
			graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));
		}

		if(backgroundImage != 0)
		{
			switch(getAlignment())
			{
			default:
			case gcn::Graphics::CENTER:
				x = (int)((getWidth() / 2) - (backgroundImage->getWidth() / 2));
				break;
			case gcn::Graphics::LEFT:
				break;
			case gcn::Graphics::RIGHT:
				x = (int)(getWidth() - backgroundImage->getWidth());
				break;
			}
			switch(verticalAlignment)
			{
			default:
			case Text::LOVE_ALIGN_CENTER:
				y = (int)((getHeight() / 2) - (backgroundImage->getHeight() / 2));
				break;
			case Text::LOVE_ALIGN_TOP:
				break;
			case Text::LOVE_ALIGN_BOTTOM:
				y = (int)(getHeight() - backgroundImage->getHeight());
				break;
			}

			graphics->setColor(gcn::Color(0xFFFFFF)); // to remove the effects of the background color
			backgroundImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
		}

		x = 0;
		y = 0;

		switch(getAlignment())
		{
		default:
		case gcn::Graphics::CENTER:
			x = (getWidth() / 2) - (gcn::Label::getFont()->getWidth(getCaption()) / 2);
			break;
		case gcn::Graphics::LEFT:
			break;
		case gcn::Graphics::RIGHT:
			x = getWidth() - (gcn::Label::getFont()->getWidth(getCaption()));
			break;
		}

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y = (getHeight() / 2) - (gcn::Label::getFont()->getHeight() / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y = getHeight() - (gcn::Label::getFont()->getHeight());
			break;
		}

		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		graphics->setFont(gcn::Label::getFont());
		graphics->drawText(getCaption(),x,y);
	}

	void Label::drawBorder(gcn::Graphics* graphics)
	{
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		if(borderColor != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));
		
		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}
}
