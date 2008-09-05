#include <love/MemoryFile.h>
using std::string;

namespace love
{

	MemoryFile::MemoryFile(char *d, int s, const string &f)
		: File(f), data(d), size(s)
	{
	}

	MemoryFile::~MemoryFile()
	{
		unload();
	}

	int MemoryFile::getSize()
	{
		return size;
	}

	char * MemoryFile::getData()
	{
		return data;
	}

	bool MemoryFile::load()
	{
		return true;
	}

	void MemoryFile::unload()
	{
	}

	bool MemoryFile::open()
	{
		return false;
	}

	bool MemoryFile::close()
	{
		return false;
	}

	int MemoryFile::read(char * dest, int count)
	{
		return -1;
	}

	bool MemoryFile::write(const char * data, int count)
	{
		return false;
	}

	bool MemoryFile::eof()
	{
		return true;
	}

	int MemoryFile::tell()
	{
		return 0;
	}

	bool MemoryFile::seek(int pos)
	{
		return false;
	}

}// love
