#include <love/File.h>

namespace love
{
	File::File()
	{
	}

	File::File(const std::string & filename, int mode) 
		: filename(filename), mode(mode)
	{
	}

	File::~File()
	{
	}

	const std::string & File::getFilename() const
	{
		return filename;
	}

	int File::getMode() const
	{
		return mode;
	}

}// love
