#include "File.h"

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

	std::string File::getExtention() const
	{
		std::string::size_type idx;

		idx = filename.rfind('.');

		if(idx != std::string::npos)
		{
			std::string extension = filename.substr(idx+1);
			return extension;
		}
		else
		{
			// Empty.
			return std::string();
		}		
	}

	int File::getMode() const
	{
		return mode;
	}

}// love
