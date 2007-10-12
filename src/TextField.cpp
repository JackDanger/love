#include "TextField.h"

namespace love
{
	TextField::TextField(const char * text)
	{
		gcn::TextField();
		gcn::TextField::setText(text);

		color = 0;
		backgroundColor = 0;
		borderColor = 0;
		activeColor = 0;
		activeBackgroundColor = 0;
	}

	TextField::~TextField()
	{ }

	void TextField::setText(const char * text)
	{
		gcn::TextField::setText(text);
	}

	void TextField::setColor(AbstractColor * color)
	{
		this->color = color;
	}

	void TextField::setBackgroundColor(AbstractColor * color)
	{
		backgroundColor = color;
	}

	void TextField::setBorderColor(AbstractColor * color)
	{
		borderColor = color;
	}

	void TextField::setActiveColor(AbstractColor * color)
	{
		activeColor = color;
	}

	void TextField::setActiveBackgroundColor(AbstractColor * color)
	{
		activeBackgroundColor = color;
	}

	AbstractColor * TextField::getColor()
	{
		return color;
	}

	AbstractColor * TextField::getBackgroundColor()
	{
		return backgroundColor;
	}

	AbstractColor * TextField::getActiveColor()
	{
		return activeColor;
	}

	AbstractColor * TextField::getActiveBackgroundColor()
	{
		return activeBackgroundColor;
	}

	AbstractColor * TextField::getBorderColor()
	{
		return borderColor;
	}

	void TextField::draw(gcn::Graphics* graphics)
	{
		if(isFocused() && activeColor != 0)
			gcn::TextField::setForegroundColor(gcn::Color(activeColor->getRed(),activeColor->getGreen(),activeColor->getBlue(),activeColor->getAlpha()));
		else if(color != 0)
			gcn::TextField::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		
		if(isFocused() && activeBackgroundColor != 0)
			gcn::TextField::setBackgroundColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		else if(backgroundColor != 0)
			gcn::TextField::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		gcn::TextField::draw(graphics);
	}

	void TextField::drawBorder(gcn::Graphics* graphics)
	{
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		if(borderColor != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0x000000));
		
		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}
}