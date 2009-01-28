/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-22
**/

#include "File.h"

namespace love
{
namespace filesystem
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

} // filesystem
} // love
