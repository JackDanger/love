#include "Graphics.h"

// LOVE
#include "using_filesystem.h"

namespace love
{

	Graphics::Graphics()
	{
		background.reset<Color>(new Color(0, 0, 0, 255));
		color.reset<Color>(new Color(255, 255, 255, 255));
	}

	Graphics::~Graphics()
	{
	}

	int Graphics::getWidth() const
	{
		return width;
	}

	int Graphics::getHeight() const
	{
		return height;
	}

	void Graphics::setBackgroundColor(pColor color)
	{
		this->background = color;
	}

	void Graphics::setBackgroundColor(int r, int g, int b)
	{
		this->background.reset<Color>(new Color(r, g, b, 255));
	}

	void Graphics::setColor(pColor color)
	{
		this->color = color;
	}

	void Graphics::setColor(int r, int g, int b, int a)
	{
		this->color.reset<Color>(new Color(r, g, b, a));
	}

	void Graphics::setFont(pFont font)
	{
		this->font = font;
	}

	pImage Graphics::getImage(const std::string & filename) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getImage(file);
	}

	pFont Graphics::getFont(const std::string & filename, int size) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getFont(file, size);
	}

	void Graphics::draw(const char * str, float x, float y) const
	{
		apply(color); // Set current color.

		if(font != 0)
			font->print(std::string(str), x, y);
	}

} // love
