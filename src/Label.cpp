#include "Label.h"

namespace love
{
	Label::Label(const string caption)
	{
		gcn::Label();

		gcn::Label::setCaption(caption);

		align(Text::LOVE_ALIGN_CENTER);
		valign(Text::LOVE_ALIGN_CENTER);
	}

	Label::~Label()
	{
	}

	void Label::setCaption(const char * caption)
	{
		gcn::Label::setCaption(string(caption));
	}

	void Label::adjustSize()
	{
		setWidth(getFont()->getWidth(getCaption()));
		setHeight(getFont()->getHeight() + 2);

		if(background != 0)
		{
			if(getWidth() < background->getWidth())
				setWidth((int)background->getWidth());
			if(getHeight() < background->getHeight())
				setHeight((int)background->getHeight());
		}
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

	void Label::setColor(const pAbstractColor * color)
	{
		if(color != 0)
			this->color = *color;
	}

	void Label::setBackgroundColor(const pAbstractColor * color)
	{
		if(color != 0)
			backgroundColor = *color;
	}

	void Label::setBorderColor(const pAbstractColor * color)
	{
		if(color != 0)
			borderColor = *color;
	}

	void Label::setBackground(const pAbstractImage * image)
	{
		background = *image;
	}

	pAbstractColor Label::getColor()
	{
		return color;
	}

	pAbstractColor Label::getBackgroundColor()
	{
		return backgroundColor;
	}

	pAbstractColor Label::getBorderColor()
	{
		return borderColor;
	}

	pAbstractImage Label::getBackground()
	{
		return background;
	}

	void Label::draw(gcn::Graphics* graphics)
	{
		int x = 0;
		int y = 0;

		if(backgroundColor != 0)
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,0));

		graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));

		if(background != 0)
		{
			switch(getAlignment())
			{
			default:
			case gcn::Graphics::CENTER:
				x = (int)((getWidth() / 2) - (background->getWidth() / 2));
				break;
			case gcn::Graphics::LEFT:
				break;
			case gcn::Graphics::RIGHT:
				x = (int)(getWidth() - background->getWidth());
				break;
			}
			switch(verticalAlignment)
			{
			default:
			case Text::LOVE_ALIGN_CENTER:
				y = (int)((getHeight() / 2) - (background->getHeight() / 2));
				break;
			case Text::LOVE_ALIGN_TOP:
				break;
			case Text::LOVE_ALIGN_BOTTOM:
				y = (int)(getHeight() - background->getHeight());
				break;
			}

			glPushAttrib(GL_CURRENT_BIT);
			graphics->setColor(gcn::Color(0xFFFFFF)); // to remove the effects of the background color
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

			background->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
				
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glDisable(GL_TEXTURE_2D);
			glPopAttrib();
		}

		x = 0;
		y = 0;

		switch(getAlignment())
		{
		default:
		case gcn::Graphics::CENTER:
			x = (getWidth() / 2) - (getFont()->getWidth(getCaption()) / 2);
			break;
		case gcn::Graphics::LEFT:
			break;
		case gcn::Graphics::RIGHT:
			x = getWidth() - getFont()->getWidth(getCaption());
			break;
		}

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y = (getHeight() / 2) - (getFont()->getHeight() / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y = getHeight() - getFont()->getHeight();
			break;
		}

		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		string temp = getCaption();
		graphics->drawText(temp,x,y);
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