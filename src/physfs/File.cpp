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
