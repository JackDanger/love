#include "MultilineLabel.h"

namespace love
{
	MultilineLabel::MultilineLabel(const string caption) : Label(caption)
	{
		setCaption(caption);
	}

	MultilineLabel::~MultilineLabel()
	{
		lines.clear();
	}

	void MultilineLabel::setCaption(const string & caption)
	{
		gcn::Label::setCaption(caption);
		adjustContent();
	}

	void MultilineLabel::setCaption(const char * caption)
	{
		setCaption(string(caption));
	}

	int MultilineLabel::adjustContent()
	{
		if(getWidth() == 0) return 0;

		const char * text = getCaption();
		vector<string> words;
		vector<float> sizes;
		float size = 0;
		string temp;
		lines.clear();
		words.clear();
		sizes.clear();

		for(int i = 0; i != strlen(text) && text[i] != '\0'; i++)
		{
			if(text[i] == '\n')
			{
				words.push_back(temp);
				sizes.push_back(size);
				words.push_back("\n");
				sizes.push_back(0.0f);
				size = 0;
				temp = "";
			}
			else if(text[i] == ' ')
			{
				temp += text[i];
				size += getFont()->getWidth(" ");
				words.push_back(temp);
				sizes.push_back(size);
				size = 0;
				temp = "";
			}
			else
			{
				temp += text[i];
				size += getFont()->getWidth(string(1, text[i]));
			}
		}
		//takes the last one and pushes it
		words.push_back(temp);
		sizes.push_back(size);

		temp = "";
		size = 0;
		for(int i = 0; i != words.size(); i++)
		{
			if(words.at(i) == "\n")
			{
				lines.push_back(temp);
				size = 0;
				temp = "";
			}
			else
			{
				size += sizes.at(i);
				
				if(size > getWidth() && size != sizes.at(i))
				{
					lines.push_back(temp);
					size = sizes.at(i);
					temp = words.at(i);
				}
				else
					temp += words.at(i);
			}
		}
		//push the last one
		lines.push_back(temp);

		return getFont()->getHeight() * (int)lines.size();
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

		setHeight((getFont()->getHeight()) * (int)lines.size());

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

		if(backgroundColor.get() != 0)
			graphics->setColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,0));

		graphics->fillRectangle(gcn::Rectangle(0,0,getWidth(),getHeight()));

		if(background.get() != 0)
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

			graphics->setColor(gcn::Color(0xFFFFFF)); // to remove the effects of the background color

			background->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
		}

		x = 0;
		y = 0;

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y = (getHeight() / 2) - ((getFont()->getHeight() * (int)lines.size()) / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y = getHeight() - (getFont()->getHeight() * (int)lines.size());
			break;
		}

		if(color.get() != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		else
			graphics->setColor(gcn::Color(0,0,0,255));

		for(unsigned int i = 0; i < lines.size(); i++)
		{
			switch(getAlignment())
			{
			default:
			case gcn::Graphics::CENTER:
				x = (getWidth() / 2) - (getFont()->getWidth(lines[i]) / 2);
				break;
			case gcn::Graphics::LEFT:
				break;
			case gcn::Graphics::RIGHT:
				x = getWidth() - gcn::Label::getFont()->getWidth(lines[i]);
				break;
			}
			graphics->drawText(lines[i], x, y + (i * getFont()->getHeight()));
		}
	}
}