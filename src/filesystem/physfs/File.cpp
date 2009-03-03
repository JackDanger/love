/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "File.h"

// STD
#include <string.h>

// LOVE
#include "Filesystem.h"

namespace love
{
namespace filesystem
{
namespace physfs
{
	File::File(const std::string & filename, int mode) 
		: love::filesystem::File(filename, mode), data(0), file(0)
	{
	}

	File::~File()
	{
		unload();
	}

	bool File::load()
	{
		if(!open())
			return false;

		// If data already present, then delete.
		if(data != 0)
		{
			delete [] data;
			data = 0;
		}
		
		// Okay, get the filesize and allocate that much memory.
		int size = (int)PHYSFS_fileLength(file);
		data = new char[size];
		
		// Read the file.
		bool result = (PHYSFS_read(file, data, 1, size) != -1);

		close();
		return result;
	}

	void File::unload()
	{
		if(data == 0)
			return;
			
		// Delete the data.
		delete[] data;
		data = 0;
		
		// CLOSE the file, if it's open.
		if(file != 0)
			close();
	}

	int File::getSize()
	{
		// If the file is closed, open it to
		// check the size.
		if(file == 0)
		{
			if(!open())
				return 0;
			int size = (int)PHYSFS_fileLength(file);
			close();
			return size;
		}

		return (int)PHYSFS_fileLength(file);
	}

	char * File::getData()
	{
		return data;
	}

	bool File::open()
	{
		// Check whether the write directory is set.
		if((mode == love::FILE_APPEND || mode == love::FILE_WRITE) && (PHYSFS_getWriteDir() == 0))
			if(!Filesystem::__getinstance()->setupWriteDirectory())
				return false;

		switch(mode)
		{
		case love::FILE_READ:
			file = PHYSFS_openRead(filename.c_str());
			break;
		case love::FILE_APPEND:
			file = PHYSFS_openAppend(filename.c_str());
			break;
		case love::FILE_WRITE:
			file = PHYSFS_openWrite(filename.c_str());
			break;
		}

		return (file != 0);
	}

	bool File::close()
	{
		if(!PHYSFS_close(file))
			return false;
		file = 0;
		return true;
	}

	int File::read(char * dest, int count)
	{
		if(file == 0)
			return -2;

		if(count == -1)
			count = (int)PHYSFS_fileLength(file);

		return (int)PHYSFS_read(file, dest, 1, count);
	}

	bool File::write(const char * data, int count)
	{
		count = (count == -1) ? (PHYSFS_uint32)strlen(data) : count;

		// Try to write.
		int written = static_cast<int>(PHYSFS_write(file, data, 1, count));

		// Check that correct amount of data was written.
		if(written != count)
			return false;

		return true;
	}

	bool File::eof()
	{
		if(file == 0 || PHYSFS_eof(file))
			return true;
		return false;
	}

	int File::tell()
	{
		if(file == 0)
			return -1;

		return (int)PHYSFS_tell(file);
	}

	bool File::seek(int pos)
	{
		if(file == 0)
			return false;
		
		if(!PHYSFS_seek(file, (PHYSFS_uint64)pos))
			return false;
		return true;
	}

} // physfs
} // filesystem
} // love