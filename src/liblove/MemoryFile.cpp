#include <love/MemoryFile.h>
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

	bool MemoryFile::load()
	{
		// Always loaded ...
		return true;
	}

	void MemoryFile::unload()
	{
		// (Supposed to be empty).
	}

}// love
