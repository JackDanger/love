#include <love/File.h>

using std::string;

namespace love
{

	File::File(const string & filename, int mode) 
		: filename(filename), mode(mode)
	{
	}

	File::~File()
	{
	}

	const string & File::getFilename() const
	{
		return filename;
	}

	int File::getMode() const
	{
		return mode;
	}

}// love
