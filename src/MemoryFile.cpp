#include "MemoryFile.h"

using std::string;

namespace love
{

	MemoryFile::MemoryFile(char *d, const unsigned long s, const string &f)
		: File("pre-compiled", f, d, s, true)
	{
	}

	MemoryFile::~MemoryFile()
	{
		this->unload();
	}

	bool MemoryFile::load()
	{
		return true;
	}

	void MemoryFile::unload()
	{
	}
}// love
