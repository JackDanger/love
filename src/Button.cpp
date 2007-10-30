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

			gcn::Button::draw(graphics);
			return;

			gcn::Color backColor;

			if(backgroundColor.get() != 0)
				backColor = gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha());
			else
				backColor = gcn::Color(0,0,0,0);
	
			if(isPressed())
			{
				y = 1; //awesome 3d effects, yo
				x = 1;
				if(pressedBackgroundColor.get() != 0)
					backColor = gcn::Color(pressedBackgroundColor->getRed(),pressedBackgroundColor->getGreen(),pressedBackgroundColor->getBlue(),pressedBackgroundColor->getAlpha());
				else if(hoverBackgroundColor.get() != 0)
					backColor = gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha()) + 0x303030;
				else if(backgroundColor.get() != 0)
					backColor = backColor - 0x606060;
				else
					backColor.a += 25;
			}
			else if(mHasMouse)
			{
				if(hoverBackgroundColor.get() != 0)
					backColor = gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha());
				else if(backgroundColor.get() != 0)
					backColor = backColor - 0x303030;
				else
					backColor.a += 12;
			}

			graphics->setColor(backColor);

			graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));
		}

		switch(getAlignment())
		{
		default:
		case gcn::Graphics::CENTER:
			x += (getWidth() / 2) - (gcn::Button::getFont()->getWidth(getCaption()) / 2);
			break;
		case gcn::Graphics::LEFT:
			break;
		case gcn::Graphics::RIGHT:
			x += getWidth() - gcn::Button::getFont()->getWidth(getCaption());
			break;
		}

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y += (getHeight() / 2) - (gcn::Button::getFont()->getHeight() / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y += getHeight() - gcn::Button::getFont()->getHeight();
			break;
		}

		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		if(isPressed() && pressedColor != 0)
			graphics->setColor(gcn::Color(pressedColor->getRed(),pressedColor->getGreen(),pressedColor->getBlue(),pressedColor->getAlpha()));
		else if(mHasMouse && hoverColor != 0)
			graphics->setColor(gcn::Color(hoverColor->getRed(),hoverColor->getGreen(),hoverColor->getBlue(),hoverColor->getAlpha()));

		graphics->drawText(getCaption(),x,y);
	}

	void Button::drawBorder(gcn::Graphics* graphics)
	{
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		gcn::Button::drawBorder(graphics);
		return;

		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}
}