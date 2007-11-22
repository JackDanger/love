#include "AbstractGraphics.h"

namespace love
{
	
	AbstractGraphics::AbstractGraphics()
	{
	}
	
	AbstractGraphics::~AbstractGraphics()
	{
	}
	
	void AbstractGraphics::setColor(const pAbstractColor & color)
	{
		this->color = color;
	}

	void AbstractGraphics::setColor(int r, int g, int b, int a)
	{
		this->color.reset<AbstractColor>(new Color(r, g, b, a));
	}

	void AbstractGraphics::setColor(int code, int a)
	{
		this->color.reset<AbstractColor>(new Color(code));
		this->color->setAlpha(a);
	}

	void AbstractGraphics::setBackgroundColor(const pAbstractColor & color)
	{
		this->background = color;
		glClearColor((float)background->getRed()/255.0f, (float)background->getGreen()/255.0f, (float)background->getBlue()/255.0f, 1.0f);
	}

	void AbstractGraphics::setBackgroundColor(int r, int g, int b)
	{
		this->background.reset<Color>(new Color(r, g, b));
		glClearColor((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
	}

	void AbstractGraphics::setBackgroundColor(int code)
	{
		this->background.reset<Color>(new Color(code));
		glClearColor((float)background->getRed()/255.0f, (float)background->getGreen()/255.0f, (float)background->getBlue()/255.0f, 1.0f);
	}

	void AbstractGraphics::setFont(const pAbstractFont & font)
	{
		this->font = font;
	}

	pAbstractColor AbstractGraphics::getColor()
	{
		return color;
	}

	pAbstractColor AbstractGraphics::getBackgroundColor()
	{
		return background;
	}

	pAbstractFont AbstractGraphics::getFont()
	{
		return font;
	}

	void AbstractGraphics::draw(const pSprite & sprite, float x, float y) const
	{
		sprite->render(x, y);
	}
	void AbstractGraphics::draw(const pSprite & sprite, float x, float y, float width, float height) const
	{
		sprite->render(x, y, width, height);
	}

	void AbstractGraphics::draw(const pParticleSystem & particleSystem, float x, float y) const
	{
		particleSystem->render(x, y);
	}
		
	void AbstractGraphics::draw(const string & str, float x, float y, float limit, int align) const
	{
		if(font!=0)
		{
			// Create new text object.
			Text text(font.get(), color.get());

			// Set some attributes.
			text.align(align);
			text.setLimit(limit);

			// And print.
			text.print(x, y, str.c_str(), font.get(), color.get());
		}
	}

} // love
