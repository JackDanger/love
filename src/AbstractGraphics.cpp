#include "AbstractGraphics.h"

namespace love
{
	
	AbstractGraphics::AbstractGraphics()
	{
	}
	
	AbstractGraphics::~AbstractGraphics()
	{
	}
	
	void AbstractGraphics::setColor(const pColor * color)
	{
		this->color = *color;
	}

	void AbstractGraphics::setColor(int r, int g, int b, int a)
	{
		this->color.reset<Color>(new Color(r, g, b, a));
	}

	void AbstractGraphics::setBackground(const pColor * color)
	{
		this->background = *color;
		glClearColor((float)background->getRed()/255.0f, (float)background->getGreen()/255.0f, (float)background->getBlue()/255.0f, 1.0f);
	}

	void AbstractGraphics::setBackground(int r, int g, int b)
	{
		this->background.reset<Color>(new Color(r, g, b));
		glClearColor((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
	}

	void AbstractGraphics::setFont(const pAbstractFont * font)
	{
		this->font = *font;
	}

	void AbstractGraphics::setFont(pAbstractFont font)
	{
		this->font = font;
	}

	void AbstractGraphics::drawSprite(const pAbstractImage * sprite) const
	{
		this->drawSprite((pSprite)(*sprite));
	}

	void AbstractGraphics::drawSprite(const pAbstractImage * sprite, float x, float y) const
	{
		this->drawSprite((pSprite)(*sprite), x, y);
	}

	void AbstractGraphics::drawSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const
	{
		this->drawSprite((pSprite)(*sprite), x, y, width, height);
	}

	void AbstractGraphics::drawSprite(const pAbstractImage * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		this->drawSprite((pSprite)(*sprite), x, y, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	void AbstractGraphics::drawSubSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const
	{
		this->drawSubSprite((pSprite)(*sprite), x, y, width, height);
	}

	void AbstractGraphics::drawSprite(const pFrameAnimation * sprite) const
	{
		this->drawSprite((pSprite)(*sprite));
	}

	void AbstractGraphics::drawSprite(const pFrameAnimation * sprite, float x, float y) const
	{
		this->drawSprite((pSprite)(*sprite), x, y);
	}

	void AbstractGraphics::drawSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const
	{
		this->drawSprite((pSprite)(*sprite), x, y, width, height);
	}

	void AbstractGraphics::drawSprite(const pFrameAnimation * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		this->drawSprite((pSprite)(*sprite), x, y, x1, y1, x2, y2, x3, y3, x4, y4);
	}

	void AbstractGraphics::drawSubSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const
	{
		this->drawSubSprite((pSprite)(*sprite), x, y, width, height);
	}


} // love
