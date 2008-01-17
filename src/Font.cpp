#include "Font.h"

namespace love
{
	Font::Font(pFile file, int size)  : Resource(file), size(size)
	{
		for(unsigned int i = 0; i < MAX_CHARS; i++) widths[i] = -1;
	}

	Font::~Font()
	{
	}

	float Font::getHeight() const
	{
		return this->getLineHeight();
	}

	float Font::getWidth(const char * line) const
	{
		return this->getLineWidth(line);
	}
	
	float Font::getLineWidth(const std::string & line) const
	{
		return this->getLineWidth(line.c_str());
	}
	
	float Font::getWidth(const std::string & line) const
	{
		return this->getLineWidth(line.c_str());
	}
}
