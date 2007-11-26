#include "AbstractFont.h"

namespace love
{
	AbstractFont::AbstractFont(AbstractFile * file, int size)  : Resource(file), size(size)
	{
		for(int i = 0; i < MAX_CHARS; i++) widths[i] = -1;
	}

	AbstractFont::~AbstractFont()
	{
	}

	float AbstractFont::getHeight()
	{
		return this->getLineHeight();
	}

	float AbstractFont::getWidth(const char * line)
	{
		return this->getLineWidth(line);
	}
}
