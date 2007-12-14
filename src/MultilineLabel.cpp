#include "MultilineLabel.h"

using std::string;
using std::vector;

namespace love
{
	MultilineLabel::MultilineLabel(const string & caption) : Label(caption)
	{
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

	int MultilineLabel::adjustContent()
	{
		const char * text = getCaption().c_str();
		vector<string> words;
		vector<float> sizes;
		float size = 0;
		string temp;
		lines.clear();
		words.clear();
		sizes.clear();

		if(strlen(text) == 0)
			return getHeight();

		for(int i = 0; i != (int)strlen(text) && text[i] != '\0'; i++)
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
				size += gcn::Label::getFont()->getWidth(" ");
				words.push_back(temp);
				sizes.push_back(size);
				size = 0;
				temp = "";
			}
			else
			{
				temp += text[i];
				size += gcn::Label::getFont()->getWidth(string(1, text[i]).c_str());
			}
		}
		//takes the last one and pushes it
		words.push_back(temp);
		sizes.push_back(size);

		temp = "";
		size = 0;
		for(int i = 0; i != (int)words.size(); i++)
		{
			if(words.at(i) == "\n")
			{
				lines.push_back(temp);
				size = 0;
				temp = "";
			}
			else if(getWidth() != 0)
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

		return (int)(gcn::Label::getFont()->getHeight() * lines.size());
	}

	void MultilineLabel::adjustSize()
	{
		int length, temp = 0;

		if(backgroundImage != 0)
		{
			if(getWidth() < backgroundImage->getWidth())
				setWidth((int)backgroundImage->getWidth());
			if(getHeight() < backgroundImage->getHeight())
				setHeight((int)backgroundImage->getHeight());
		}

		adjustContent();

		if(getWidth() == 0)
		{
			for(int i = 0; i != (int)lines.size(); i++)
			{
				length = gcn::Label::getFont()->getWidth(lines[i].c_str());
				temp = (temp > length) ? temp : length;
			}
			setWidth(temp);
		}

		temp = (gcn::Label::getFont()->getHeight()) * (int)lines.size();
		if(backgroundImage == 0 || getHeight() < temp)
			setHeight(temp);
	}

	void MultilineLabel::draw(gcn::Graphics* graphics)
	{
		int x = 0;
		int y = 0;

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

		switch(verticalAlignment)
		{
		default:
		case Text::LOVE_ALIGN_CENTER:
			y = (getHeight() / 2) - (((int)getFont()->getHeight() * (int)lines.size()) / 2);
			break;
		case Text::LOVE_ALIGN_TOP:
			break;
		case Text::LOVE_ALIGN_BOTTOM:
			y = getHeight() - ((int)getFont()->getHeight() * (int)lines.size());
			break;
		}

		if(font != 0)
			graphics->setFont(font.get());
		if(color != 0)
			graphics->setColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));

		for(unsigned int i = 0; i < lines.size(); i++)
		{
			switch(getAlignment())
			{
			default:
			case gcn::Graphics::CENTER:
				x = (getWidth() / 2) - ((int)getFont()->getWidth(lines[i].c_str()) / 2);
				break;
			case gcn::Graphics::LEFT:
				break;
			case gcn::Graphics::RIGHT:
				x = getWidth() - gcn::Label::getFont()->getWidth(lines[i]);
				break;
			}
			graphics->drawText(lines[i], x, y + (i * (int)getFont()->getHeight()));
		}
	}
}
