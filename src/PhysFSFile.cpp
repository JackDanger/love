#include "PhysFSFile.h"
#include "physfs.h"
#include "love.h"
#include "Core.h"
#include "Console.h"

namespace love
{

	PhysFSFile::PhysFSFile(const string & source, const string & filename) : AbstractFile(source, filename)
	{
		this->data = 0;
		this->size = 0;
	}

	PhysFSFile::~PhysFSFile()
	{
	}

	int PhysFSFile::load()
	{
		
		// Sets the specified source as search path. Can be 
		// dir or archive file.
		int added = PHYSFS_addToSearchPath(source.c_str(), 1);

		if(!added)
		{
			fail();
			return LOVE_ERROR;
		}

		// Check if the file we want exists
		int exists = PHYSFS_exists(filename.c_str());

		// Check for failure
		if(!exists)
		{
			removeSource();
			fail();
			return LOVE_ERROR;
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
			return LOVE_ERROR;
		}

		// Okay, done with file. Close it. 
		int closed = PHYSFS_close(file);

		// Check for errors.	
		if(!closed)
		{
			fail();
			return LOVE_ERROR;
		}

		// Remove source
		removeSource();

		// Notify plz
		if(core->isVerbose())
			core->printf(" + LOADED \"%s\"\n",(source + "\" -> \"" + filename).c_str());


		return LOVE_OK;
	}

	void PhysFSFile::fail()
	{
		printf("PhysFS fail while loading \"%s\\%s\": \n", filename.c_str(), PHYSFS_getLastError());
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

	void PhysFSFile::unload()
	{
		if(data != 0)
		{
			if(core->isVerbose())
				core->printf(" - UNLOAD \"%s\"\n", (source + "\" -> \"" + filename).c_str());
			delete data;
		}

		data = 0;
	}


}// love
