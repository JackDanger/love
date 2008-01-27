#include "Label.h"
#include "using_graphics.h"

#include <math.h>

namespace love
{
	Label::Label(std::string text) : Widget(false, false)
	{
		this->text = text;
		adjustSize();
	}

	Label::~Label()
	{
	}
	
	void Label::setBackgroundImage(const pImage & image)
	{
		this->backgroundImage = image;
		
		adjustContent();
	}
	
	pImage Label::getBackgroundImage() const
	{
		return backgroundImage;
	}

	void Label::adjustWidth()
	{
		graphics->push();
		
		if(font != 0)
			graphics->setFont(font);
		
		width = graphics->getFont()->getWidth(text) + paddingLeft + paddingRight;
		
		if(backgroundImage != 0 && backgroundImage->getWidth() > width)
			width = backgroundImage->getWidth();
		
		graphics->pop();
	}
	
	void Label::adjustHeight()
	{
		graphics->push();
		
		if(font != 0)
			graphics->setFont(font);
		
		height = graphics->getFont()->getHeight() + paddingTop + paddingBottom;
		
		if(backgroundImage != 0 && backgroundImage->getHeight() > height)
			height = backgroundImage->getHeight();
		
		graphics->pop();
	}
	
	void Label::adjustContent()
	{
		graphics->push();
		
		if(font != 0)
			graphics->setFont(font);
		
		innerx = x;
		innery = y;
		
		switch(align)
		{
			case love::LOVE_ALIGN_LEFT:
				innerx += paddingLeft;
				break;
					
			case love::LOVE_ALIGN_RIGHT:
				innerx += width - graphics->getFont()->getWidth(text) - paddingRight;
				break;
					
			default:
			case love::LOVE_ALIGN_CENTER:
				innerx += (width / 2) - (graphics->getFont()->getWidth(text) / 2);
				break;
		}
			
		switch(valign)
		{
			case love::LOVE_ALIGN_TOP:
				innery += paddingTop;
				break;
					
			case love::LOVE_ALIGN_BOTTOM:
				innery += height - graphics->getFont()->getHeight() - paddingBottom;
				break;
					
			default:
			case love::LOVE_ALIGN_CENTER:
				innery += (height / 2) - (graphics->getFont()->getHeight() / 2);
				break;
		}
		
		graphics->pop();
	}

	void Label::update(float dt)
	{
	}

	void Label::render() const
	{
		graphics->push();
		
		if(backgroundColor != 0)
		{
			graphics->push();
			
			graphics->setColor(backgroundColor);
			graphics->fillQuad(x, y, 0, 0, 0, height, width, height, width, 0);
			
			graphics->pop();
		}
		
		drawBorder();
		
		if(color != 0)
			graphics->setColor(color);
		
		if(font != 0)
			graphics->setFont(font);
		
		if(backgroundImage != 0)
			backgroundImage->render(x, y);
		
		graphics->draw(text.c_str(), floor(innerx), floor(innery));
		
		// reinstate the status quo
		graphics->pop();
	}

	void Label::mousePressed(float x, float y, int button)
	{
	}

	void Label::mouseReleased(float x, float y, int button)
	{
	}

	void Label::mouseMoved(float x, float y)
	{
	}

	void Label::keyPressed(int key)
	{
	}

	void Label::keyReleased(int key)
	{
	}

}
