#include "MemoryFile.h"

using std::string;

namespace love
{

	MemoryFile::MemoryFile(char *d, const unsigned long s, const string &f)
		: File(f, d, s, true)
	{
	}

	MemoryFile::~MemoryFile()
	{
	}

}// love
