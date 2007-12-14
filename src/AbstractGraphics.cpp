#include "AbstractGraphics.h"
#include "Core.h"
#include "love.h"
#include "AbstractFile.h"

#include "AbstractFileSystem.h"

using std::string;

namespace love
{
	
	AbstractGraphics::AbstractGraphics()
	{
	}
	
	AbstractGraphics::~AbstractGraphics()
	{
	}
	
	pAbstractImage AbstractGraphics::getImage(const string & filename) const
	{
		pAbstractFile file = core->filesystem->getBaseFile(filename);
		return getImage(file);
	}

	pAbstractFont AbstractGraphics::getFont(const string & filename, int size) const
	{
		pAbstractFile file = core->filesystem->getBaseFile(filename);
		return getFont(file, size);
	}

	pAbstractFont AbstractGraphics::getImageFont(const string & filename, const string & glyphs) const
	{
		pAbstractFile file = core->filesystem->getBaseFile(filename);
		return getImageFont(file, glyphs);
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
		push();
		translate(-sprite->getWidth() / 2.0f, -sprite->getHeight() / 2.0f);
		setAlpha((int)sprite->getAlpha());
		sprite->render(x, y);
		pop();

	}
	void AbstractGraphics::draw(const pSprite & sprite, float x, float y, float xs, float ys, float width, float height) const
	{
		this->translate(x,y);
		setAlpha((int)sprite->getAlpha());
		sprite->render(xs, ys, width, height);
		this->translate(-x,-y);
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
