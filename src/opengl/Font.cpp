#include "Font.h"

namespace love_opengl
{
	Font::Font(love::pFile file, int size)  : love::Resource(file), size(size), lineHeight(1), mSpacing(1)
	{
		for(unsigned int i = 0; i < MAX_CHARS; i++)
		{
			widths[i] = 0;
			spacing[i] = 0;
		}
	}

	Font::~Font()
	{
	}

	float Font::getHeight() const
	{
		return (float)size;
	}
	
	float Font::getWidth(const std::string & line) const
	{
		if(line.size() == 0) return 0;
		float temp = 0;

		for(unsigned int i = 0; i < line.size() - 1; i++)
		{
			temp += widths[(int)line[i]] + (spacing[(int)line[i]] * mSpacing);
		}
		temp += widths[(int)line[line.size() - 1]]; // the last character's spacing isn't counted

		return temp;
	}

	float Font::getWidth(const char * line) const
	{
		return this->getWidth(std::string(line));
	}
	
	float Font::getWidth(const char character) const
	{
		return (float)widths[(int)character];
	}

	void Font::setLineHeight(float height)
	{
		this->lineHeight = height;
	}

	float Font::getLineHeight() const
	{
		return lineHeight;
	}

	void Font::setSpacing(float amount)
	{
		mSpacing = amount;
	}

	float Font::getSpacing() const
	{
		return mSpacing;
	}
}
