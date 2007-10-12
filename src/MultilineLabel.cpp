#include "MultilineLabel.h"

namespace love
{
	MultilineLabel::MultilineLabel(const string caption) : Label(caption)
	{
		setCaption(caption);
	}

	MultilineLabel::~MultilineLabel()
	{
	}

	void MultilineLabel::setCaption(const string & caption)
	{
		string temp = "";
		const char * text = getCaption().c_str();
		lines.clear();

		for(int i = 0; i != strlen(text) && text[i] != '\0'; i++)
		{
			if(text[i] == '\n')
			{
				lines.push_back(temp);
				temp = "";
			}
			else
			{
				temp += text[i];
			}
		}
		//takes the last one and pushes it
		lines.push_back(temp);
	}

	void MultilineLabel::setCaption(const char * caption)
	{
		setCaption(string(caption));
	}

	void MultilineLabel::adjustSize()
	{
		int length, temp = 0;
		for(int i = 0; i != lines.size(); i++)
		{
			length = getFont()->getWidth(lines[i]);
			temp = (temp > length) ? temp : length;
		}
		setWidth(temp);

		setHeight((getFont()->getHeight() + 2) * lines.size());

		if(background != 0)
		{
			if(getWidth() < background->getWidth())
				setWidth((int)background->getWidth());
			if(getHeight() < background->getHeight())
				setHeight((int)background->getHeight());
		}
	}

	void MultilineLabel::draw(gcn::Graphics* graphics)
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
			y = (getHeight() / 2) - ((getFont()->getHeight() * lines.size()) / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y = getHeight() - (getFont()->getHeight() * lines.size());
			break;
		}

		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		for(unsigned int i = 0; i < lines.size(); i++)
			graphics->drawText(lines[i], x, y + (i * getFont()->getHeight()));
	}
}