#include "LoveFile.h"
#include "physfs.h"

namespace love
{

	LoveFile::LoveFile()
	{
		this->data = 0;
		this->size = 0;
	}

	LoveFile::LoveFile(const string & source, const string & filename) : source(source), filename(filename)
	{
		this->data = 0;
		this->size = 0;
	}

	LoveFile::~LoveFile()
	{
		this->unload();
	}

	const string & LoveFile::getSource() const
	{
		return source;
	}

	const string & LoveFile::getFilename() const
	{
		return filename;
	}

	unsigned long LoveFile::getSize() const
	{
		return size;
	}

	char * LoveFile::getData()
	{
		return this->data;
	}

	void LoveFile::load()
	{
		
		// Sets the specified source as search path. Can be 
		// dir or archive file.
		int added = PHYSFS_addToSearchPath(source.c_str(), 1);

		if(!added)
		{
			fail();
			return;
		}

		// Check if the file we want exists
		int exists = PHYSFS_exists(filename.c_str());

		// Check for failure
		if(!exists)
		{
			removeSource();
			fail();
			return;
		}

		// Open file for read.
		PHYSFS_file * file = PHYSFS_openRead(filename.c_str());

		// Get filesize
		PHYSFS_sint64 size = PHYSFS_fileLength(file);
		this->size = (unsigned long)size;

		// Create temp array, and allocate memory for permanent array.
		this->data = new char[(size_t)size];

		// Read file into memory
		int read = PHYSFS_read (file, this->data, 1, ((PHYSFS_uint32)size));

		// Check for failure
		if(read == -1)
		{
			removeSource();
			fail();
			return;
		}

		// Okay, done with file. Close it. 
		int closed = PHYSFS_close(file);

		// Check for errors.	
		if(!closed)
		{
			fail();
			return;
		}

		// Remove source
		removeSource();

		// Notify plz
		printf("File \"%s\" loaded successfully from source \"%s\".\n", filename.c_str(), source.c_str());


	}

	void LoveFile::fail()
	{
		printf("PhysFS fail while loading \"%s\%s\": \n", source.c_str(), filename.c_str(), PHYSFS_getLastError());
	}

	void LoveFile::removeSource()
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

	void LoveFile::unload()
	{
		if(this->data != 0)
			delete this->data;

		this->data = this->data;
	}


}// love
