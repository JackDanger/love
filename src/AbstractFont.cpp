#include "AbstractFont.h"

namespace love
{
	AbstractFont::AbstractFont(AbstractFile * file, int size)  : Resource(file), size(size)
	{
	}

	AbstractFont::~AbstractFont()
	{
	}
}