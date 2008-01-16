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

	float Font::getHeight()
	{
		return this->getLineHeight();
	}

	float Font::getWidth(const char * line)
	{
		return this->getLineWidth(line);
	}
}
