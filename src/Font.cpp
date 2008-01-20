#include "Font.h"

namespace love
{
	Font::Font(pFile file, int size)  : Resource(file), size(size)
	{
		for(unsigned int i = 0; i < MAX_CHARS; i++) widths[i] = 0;
	}

	Font::~Font()
	{
	}

	float Font::getHeight() const
	{
		return size;
	}
	
	float Font::getWidth(const std::string & line) const
	{
		float temp = 0;

		for(unsigned int i = 0; i < line.size(); i++)
		{
			temp += widths[(int)line[i]];
		}

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
}
