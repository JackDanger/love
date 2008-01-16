#include "PhysFSFile.h"
#include <physfs.h>

using std::string;

namespace love
{

	PhysFSFile::PhysFSFile(const string & source, const string & filename) : File(source, filename)
	{
		this->data = 0;
		this->size = 0;
	}

	PhysFSFile::~PhysFSFile()
	{
	}

	bool PhysFSFile::load()
	{
		
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
		PHYSFS_file * file = PHYSFS_openRead(filename.c_str());

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

	void PhysFSFile::fail()
	{
		printf("Could not load file \"%s\" from \"%s\": %s\n", filename.c_str(), source.c_str(), PHYSFS_getLastError());
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
