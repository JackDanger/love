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
		
		color = 0;
		hoverColor = 0;
		pressedColor = 0;
		activeColor = 0;
		backgroundColor = 0;
		hoverBackgroundColor = 0;
		pressedBackgroundColor = 0;
		activeBackgroundColor = 0;
		borderColor = 0;

		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
	}

	Button::~Button()
	{ }

	void Button::setCaption(const char * caption)
	{
		gcn::Button::setCaption(string(caption));
	}

	void Button::adjustSize()
	{
		setWidth(getFont()->getWidth(mCaption) + 8);
		setHeight(getFont()->getHeight() + 4);
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

	void Button::setColor(AbstractColor * color)
	{
		if(color != 0)
			this->color = color;
	}

	void Button::setHoverColor(AbstractColor * color)
	{
		if(color != 0)
			hoverColor = color;
	}

	void Button::setPressedColor(AbstractColor * color)
	{
		if(color != 0)
			pressedColor = color;
	}

	void Button::setActiveColor(AbstractColor * color)
	{
		if(color != 0)
			activeColor = color;
	}

	void Button::setAllColors(AbstractColor * color)
	{
		if(color == 0) return;

		this->color = color;
		hoverColor = color;
		pressedColor = color;
		activeColor = color;
	}

	void Button::setBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			backgroundColor = color;
	}

	void Button::setHoverBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			hoverBackgroundColor = color;
	}

	void Button::setPressedBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			pressedBackgroundColor = color;
	}

	void Button::setActiveBackgroundColor(AbstractColor * color)
	{
		if(color != 0)
			activeBackgroundColor = color;
	}

	void Button::setAllBackgroundColors(AbstractColor * color)
	{
		backgroundColor = color;
		hoverBackgroundColor = color;
		pressedBackgroundColor = color;
		activeBackgroundColor = color;
	}

	void Button::setBorderColor(AbstractColor * color)
	{
		if(color != 0)
			borderColor = color;
	}

	AbstractColor * Button::getColor()
	{
		return color;
	}

	AbstractColor * Button::getHoverColor()
	{
		return hoverColor;
	}

	AbstractColor * Button::getPressedColor()
	{
		return pressedColor;
	}

	AbstractColor * Button::getActiveColor()
	{
		return activeColor;
	}

	AbstractColor * Button::getBackgroundColor()
	{
		return backgroundColor;
	}

	AbstractColor * Button::getHoverBackgroundColor()
	{
		return hoverBackgroundColor;
	}

	AbstractColor * Button::getPressedBackgroundColor()
	{
		return pressedBackgroundColor;
	}

	AbstractColor * Button::getActiveBackgroundColor()
	{
		return activeBackgroundColor;
	}

	AbstractColor * Button::getBorderColor()
	{
		return borderColor;
	}

	void Button::draw(gcn::Graphics* graphics)
	{
		int y = 0;
		int x = 0;

		gcn::Color backColor;

		if(backgroundColor != 0)
			backColor = gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha());
		else
			backColor = gcn::Color(0,0,0,0);

		if(isPressed())
		{
			y = 1; //awesome 3d effects, yo
			x = 1;
			if(pressedBackgroundColor != 0)
				backColor = gcn::Color(pressedBackgroundColor->getRed(),pressedBackgroundColor->getGreen(),pressedBackgroundColor->getBlue(),pressedBackgroundColor->getAlpha());
			else if(hoverBackgroundColor != 0)
				backColor = gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha()) + 0x303030;
			else if(backgroundColor != 0)
				backColor = backColor - 0x606060;
			else
				backColor.a += 25;
		}
		else if(mHasMouse)
		{
			if(hoverBackgroundColor != 0)
				backColor = gcn::Color(hoverBackgroundColor->getRed(),hoverBackgroundColor->getGreen(),hoverBackgroundColor->getBlue(),hoverBackgroundColor->getAlpha());
			else if(backgroundColor != 0)
				backColor = backColor - 0x303030;
			else
				backColor.a += 12;
		}
		else if(isFocused())
		{
			if(activeBackgroundColor != 0)
				backColor = gcn::Color(activeBackgroundColor->getRed(), activeBackgroundColor->getGreen(), activeBackgroundColor->getBlue(), activeBackgroundColor->getAlpha());
		}

		graphics->setColor(backColor);

		graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));

		switch(getAlignment())
		{
		default:
		case gcn::Graphics::CENTER:
			x += (getWidth() / 2) - (getFont()->getWidth(getCaption()) / 2);
			break;
		case gcn::Graphics::LEFT:
			break;
		case gcn::Graphics::RIGHT:
			x += getWidth() - getFont()->getWidth(getCaption());
			break;
		}

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y += (getHeight() / 2) - (getFont()->getHeight() / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y += getHeight() - getFont()->getHeight();
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
		else if(isFocused() && activeColor != 0)
			graphics->setColor(gcn::Color(activeColor->getRed(), activeColor->getGreen(), activeColor->getBlue(), activeColor->getAlpha()));

		graphics->drawText(getCaption(),x,y);
	}

	void Button::drawBorder(gcn::Graphics* graphics)
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