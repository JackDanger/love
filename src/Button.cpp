#include "Button.h"

namespace love
{
	Button::Button(const string caption)
	{
		gcn::Button();

		gcn::Button::setCaption(string(caption));
		//setSize(getFont()->getWidth(caption),getFont()->getHeight());

		setBaseColor(gcn::Color(0,0,0,255));
		setBorderSize(0);

		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
	}

	Button::~Button()
	{ }

	void Button::setSize(int width, int height)
	{
		gcn::Button::setSize(width, height);
	}

	void Button::setWidth(int width)
	{
		gcn::Button::setWidth(width);
	}

	void Button::setHeight(int height)
	{
		gcn::Button::setHeight(height);
	}

	void Button::setBorderSize(unsigned int size)
	{
		gcn::Button::setBorderSize(size);
	}

	void Button::setCaption(const char * caption)
	{
		gcn::Button::setCaption(string(caption));
	}

	void Button::setName(const char * name)
	{
		gcn::Button::setActionEventId(name);
	}

	void Button::align(int alignment)
	{
		switch(alignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			setAlignment(gcn::Graphics::CENTER);
			break;
		case Text::LOVE_ALIGN_LEFT:
			setAlignment(gcn::Graphics::LEFT);
			break;
		case Text::LOVE_ALIGN_RIGHT:
			setAlignment(gcn::Graphics::RIGHT);
			break;
		}
	}

	void Button::valign(int alignment)
	{
		verticalAlignment = alignment;
	}

	void Button::setBackgroundColor(const pAbstractColor * color)
	{
		GUIElement::setBackgroundColor(color);
	}

	void Button::setHoverColor(const pAbstractColor * color)
	{
		if(color != 0)
			hoverColor = *color;
	}

	void Button::setPressedColor(const pAbstractColor * color)
	{
		if(color != 0)
			pressedColor = *color;
	}

	void Button::setAllColors(const pAbstractColor * color)
	{
		if(color == 0) return;

		this->color = *color;
		hoverColor = *color;
		pressedColor = *color;
	}

	void Button::setHoverBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			hoverBackgroundColor = *color;
	}

	void Button::setPressedBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			pressedBackgroundColor = *color;
	}

	void Button::setAllBackgroundColors(const pAbstractColor * color)
	{
		backgroundColor = *color;
		hoverBackgroundColor = *color;
		pressedBackgroundColor = *color;
	}

	void Button::setDefaultImage(const pAbstractImage * image)
	{
		defaultImage = (*image);
	}

	void Button::setHoverImage(const pAbstractImage * image)
	{
		hoverImage = (*image);
	}

	void Button::setPressedImage(const pAbstractImage * image)
	{
		pressedImage = (*image);
	}

	int Button::getWidth()
	{
		return gcn::Button::getWidth();
	}

	int Button::getHeight()
	{
		return gcn::Button::getHeight();
	}

	unsigned int Button::getBorderSize()
	{
		return gcn::Button::getBorderSize();
	}

	const char * Button::getCaption()
	{
		return gcn::Button::getCaption().c_str();
	}

	const char * Button::getName()
	{
		return gcn::Button::getActionEventId().c_str();
	}

	pAbstractColor Button::getBackgroundColor()
	{
		return GUIElement::getBackgroundColor();
	}

	pAbstractColor Button::getHoverColor()
	{
		return hoverColor;
	}

	pAbstractColor Button::getPressedColor()
	{
		return pressedColor;
	}

	pAbstractColor Button::getHoverBackgroundColor()
	{
		return hoverBackgroundColor;
	}

	pAbstractColor Button::getPressedBackgroundColor()
	{
		return pressedBackgroundColor;
	}

	void Button::adjustSize()
	{
		setWidth(gcn::Button::getFont()->getWidth(mCaption) + 8);
		setHeight(gcn::Button::getFont()->getHeight() + 4);

		int size = 0;

		size = gcn::Button::getFont()->getWidth(mCaption) + 8;
		if(defaultImage.get() != 0 && size < defaultImage->getWidth())
			size = (int)defaultImage->getWidth();
		if(hoverImage.get() != 0 && size < hoverImage->getWidth())
			size = (int)hoverImage->getWidth();
		if(pressedImage.get() != 0 && size < pressedImage->getWidth())
			size = (int)pressedImage->getWidth();
		setWidth(size);

		size = gcn::Button::getFont()->getHeight() + 4;
		if(defaultImage.get() != 0 && size < defaultImage->getHeight())
			size = (int)defaultImage->getHeight();
		if(hoverImage.get() != 0 && size < hoverImage->getHeight())
			size = (int)hoverImage->getHeight();
		if(pressedImage.get() != 0 && size < pressedImage->getHeight())
			size = (int)pressedImage->getHeight();
		setHeight(size);
	}

	bool Button::isFocused() const
	{
		return false;
	}

	void Button::draw(gcn::Graphics* graphics)
	{
		int y = 0;
		int x = 0;

		if(defaultImage.get() != 0)
		{
			switch(getAlignment())
			{
			default:
			case gcn::Graphics::CENTER:
				x = (int)((getWidth() / 2) - (defaultImage->getWidth() / 2));
				break;
			case gcn::Graphics::LEFT:
				break;
			case gcn::Graphics::RIGHT:
				x = (int)(getWidth() - defaultImage->getWidth());
				break;
			}
			switch(verticalAlignment)
			{
			default:
			case Text::LOVE_ALIGN_CENTER:
				y = (int)((getHeight() / 2) - (defaultImage->getHeight() / 2));
				break;
			case Text::LOVE_ALIGN_TOP:
				break;
			case Text::LOVE_ALIGN_BOTTOM:
				y = (int)(getHeight() - defaultImage->getHeight());
				break;
			}

			if(isPressed() && pressedImage.get() != 0)
				pressedImage->render((float)graphics->getCurrentClipArea().x, (float)graphics->getCurrentClipArea().y);
			else if(mHasMouse && hoverImage.get() != 0)
				hoverImage->render((float)graphics->getCurrentClipArea().x, (float)graphics->getCurrentClipArea().y);
			else
				defaultImage->render((float)graphics->getCurrentClipArea().x, (float)graphics->getCurrentClipArea().y);
		}
		else
		{
			if(isPressed() && pressedColor != 0)
				gcn::Button::setForegroundColor(gcn::Color(pressedColor->getRed(), pressedColor->getGreen(), pressedColor->getBlue(), pressedColor->getAlpha()));
			else if(mHasMouse && hoverColor != 0)
				gcn::Button::setForegroundColor(gcn::Color(hoverColor->getRed(), hoverColor->getGreen(), hoverColor->getBlue(), hoverColor->getAlpha()));
			else if(color != 0)
				gcn::Button::setForegroundColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
			else
				gcn::Button::setForegroundColor(gcn::Color(0,0,0,255));

			if(isPressed() && pressedBackgroundColor != 0)
				gcn::Button::setBaseColor(gcn::Color(pressedBackgroundColor->getRed(), pressedBackgroundColor->getGreen(), pressedBackgroundColor->getBlue(), pressedBackgroundColor->getAlpha()));
			else if(mHasMouse && hoverBackgroundColor != 0)
				gcn::Button::setBaseColor(gcn::Color(hoverBackgroundColor->getRed(), hoverBackgroundColor->getGreen(), hoverBackgroundColor->getBlue(), hoverBackgroundColor->getAlpha()));
			else if(backgroundColor != 0)
				gcn::Button::setBaseColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));
			else
				gcn::Button::setBaseColor(gcn::Color(255,255,255,150));

			// the following code is ripped straight from gui::Button::draw but with a few small changes
			
			gcn::Color faceColor = getBaseColor();
			gcn::Color highlightColor, shadowColor;
			int alpha = getBaseColor().a;
			
			if (isPressed())
			{
				if(pressedBackgroundColor == 0)
				{
					faceColor = faceColor - 0x303030;
					faceColor.a = alpha;
				}
				highlightColor = faceColor - 0x303030;
				highlightColor.a = alpha;
				shadowColor = faceColor + 0x303030;
				shadowColor.a = alpha;
			}
			else
			{
				highlightColor = faceColor + 0x303030;
				highlightColor.a = alpha;
				shadowColor = faceColor - 0x303030;
				shadowColor.a = alpha;
			}
			
			graphics->setColor(faceColor);
			graphics->fillRectangle(gcn::Rectangle(1, 1, getDimension().width-1, getHeight() - 1));
			
			graphics->setColor(highlightColor);
			graphics->drawLine(0, 0, getWidth() - 1, 0);
			graphics->drawLine(0, 1, 0, getHeight() - 1);
			
			graphics->setColor(shadowColor);
			graphics->drawLine(getWidth() - 1, 1, getWidth() - 1, getHeight() - 1);
			graphics->drawLine(1, getHeight() - 1, getWidth() - 1, getHeight() - 1);
			
			graphics->setColor(getForegroundColor());
		}
			
		int textX;
		int textY = 0;
		//int textY = getHeight() / 2 - getFont()->getHeight() / 2;
			
		switch (getAlignment())
		{
		case gcn::Graphics::LEFT:
			textX = 4;
			break;
		default:
		case gcn::Graphics::CENTER:
			textX = getWidth() / 2;
			break;
		case gcn::Graphics::RIGHT:
			textX = getWidth() - 4;
			break;
		}

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			textY += (getHeight() / 2) - (gcn::Button::getFont()->getHeight() / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			textY += getHeight() - gcn::Button::getFont()->getHeight();
			break;
		}
			
		graphics->setFont(getFont());
			
		if (isPressed())
			graphics->drawText(getCaption(), textX + 1, textY + 1, getAlignment());
		else
		{
			graphics->drawText(getCaption(), textX, textY, getAlignment());
			if (isFocused())
				graphics->drawRectangle(gcn::Rectangle(2, 2, getWidth() - 4, getHeight() - 4));
		}
	}

	void Button::drawBorder(gcn::Graphics* graphics)
	{

		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		gcn::Button::drawBorder(graphics);
	}
}
