#include <love/MemoryFile.h>
using std::string;

namespace love
{

	MemoryFile::MemoryFile(char *d, const unsigned long s, const string &f, bool compiled)
		: File(f, d, s, compiled)
	{
	}

	MemoryFile::~MemoryFile()
	{
		unload();
	}

	bool MemoryFile::load()
	{
		return true;
	}

	void MemoryFile::unload()
	{
		
	}

}// love
