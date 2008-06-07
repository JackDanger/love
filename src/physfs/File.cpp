#include "File.h"

using std::string;

namespace love_physfs
{

	File::File(const string & filename, int mode) 
		: love::File(filename, mode), file(0)
	{
		this->data = 0;
		this->size = 0;
	}

	File::~File()
	{
		unload();
	}

	bool File::load()
	{
		// Try to open it.
		file = PHYSFS_openRead(filename.c_str());

		if(file==0)
			return false;
		
		// Okay, get the filesize and allocate that much memory.
		size = (int)PHYSFS_fileLength(file);
		allocate(size);
		
		// Read the file.
		if(PHYSFS_read(file, data, 1, size) == -1)
		{
			// @todo Set error.
			PHYSFS_close(file);
			return false;
		}

		// Close the file.
		PHYSFS_close(file);

		return true;
	}

	void File::unload()
	{
		if(data == 0)
			return;
		delete[] data;
		data = 0;
	}

	PHYSFS_file * File::getHandle()
	{
		return file;
	}

	void File::setHandle(PHYSFS_file * handle)
	{
		this->file = handle;
	}

}// love_physfs
