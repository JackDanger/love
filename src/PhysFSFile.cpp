#include "PhysFSFile.h"

#include "using_output.h"

using std::string;

namespace love
{

	PhysFSFile::PhysFSFile(const string & source, const string & filename, int mode) 
		: File(source, filename, mode)
	{
		this->data = 0;
		this->size = 0;
	}

	PhysFSFile::~PhysFSFile()
	{
	}

	bool PhysFSFile::load()
	{
		if(mode != LOVE_READ)
			return true;
		
		// Sets the specified source as search path. Can be 
		// dir or archive file.
		int added = PHYSFS_addToSearchPath(source.c_str(), 1);

		if(!added)
		{
			fail();
			return false;
		}

		// Check if the file we want exists
		int exists = PHYSFS_exists(filename.c_str());

		// Check for failure
		if(!exists)
		{
			removeSource();
			fail();
			return false;
		}

		// Open file for read.
		file = PHYSFS_openRead(filename.c_str());

		// Get filesize
		PHYSFS_sint64 size = PHYSFS_fileLength(file);
		this->size = (unsigned long)size;

		// Create temp array, and allocate memory for permanent array.
		this->data = new char[(size_t)size];

		// Read file into memory
		int read = (int) PHYSFS_read (file, this->data, 1, ((PHYSFS_uint32)size));

		// Check for failure
		if(read == -1)
		{
			removeSource();
			fail();
			return false;
		}

		// Okay, done with file. Close it. 
		int closed = PHYSFS_close(file);

		// Check for errors.	
		if(!closed)
		{
			fail();
			return false;
		}

		// Remove source
		removeSource();

		// Notify plz
		//printf(" + LOADED \"%s\"\n",(source + "\" -> \"" + filename).c_str());


		return true;
	}

	bool PhysFSFile::open()
	{

		switch(mode)
		{
		case LOVE_READ:
			// File is already read ... let's do nothing.
			break;
		case LOVE_WRITE:
			file = PHYSFS_openWrite(filename.c_str());
			
			if(file == 0)
			{
				error("Could not open file for write." + std::string(PHYSFS_getLastError()));
				return false;
			}

			isOpen = true;

			break;
		case LOVE_APPEND:
			file = PHYSFS_openAppend(filename.c_str());
			
			if(file == 0)
			{
				error("Could not open file for append." + std::string(PHYSFS_getLastError()));
				return false;
			}

			isOpen = true;

			break;

		}

		return true;
	}

	bool PhysFSFile::close()
	{
		if(!PHYSFS_close(file))
		{
			error("Could not close file." + std::string(PHYSFS_getLastError()));
			return false;
		}

		isOpen = false;

		return true;
	}

	bool PhysFSFile::write( std::string data )
	{
		bool wasOpen = isOpen;

		if(!wasOpen && !open()) 
			return false;

		int written = (int)PHYSFS_write(file, data.c_str(), 1, data.length());

		if(!wasOpen && !close()) 
			return false;

		if(written < 0)
		{
			error("Could not write to file." + std::string(PHYSFS_getLastError()));
			return false;			
		}

		return true;
	}

	const char * PhysFSFile::read()
	{
		return (const char *)this->data;
	}

	void PhysFSFile::fail()
	{
		std::stringstream ss;
		ss << "Could not load ";
		ss << filename; ss << " from ";
		ss << source; ss << ". ";
		ss << PHYSFS_getLastError();
		error(ss.str());
	}

	void PhysFSFile::removeSource()
	{
		// Done, remove source.
		int removed = PHYSFS_removeFromSearchPath(source.c_str());

		// Check for failure
		if(!removed)
		{
			fail();
			return;
		}
	}

}// love
