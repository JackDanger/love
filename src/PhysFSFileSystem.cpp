#include "PhysFSFileSystem.h"
#include "physfs.h"
#include "love.h"
#include "Parameters.h"
#include "PhysFSFile.h"

namespace love
{

	PhysFSFileSystem::PhysFSFileSystem(int argc, char ** argv) : argc(argc)
	{
		this->argv = argv;
	}

	PhysFSFileSystem::~PhysFSFileSystem()
	{
	}

	pAbstractFile PhysFSFileSystem::getFile(const string & source, const string & file) const
	{
		pAbstractFile tmp(new PhysFSFile(source, file));
		return tmp;
	}

	pAbstractFile PhysFSFileSystem::getBaseFile(const string & file) const
	{
		pAbstractFile tmp(new PhysFSFile(this->base, file));
		return tmp;
	}

	pAbstractFile PhysFSFileSystem::getUserFile(const string & file) const
	{
		pAbstractFile tmp(new PhysFSFile(this->user, file));
		return tmp;
	}

	int PhysFSFileSystem::init()
	{

		// Initialize PhysFS
		if(!PHYSFS_init(argv[0]))
		{
			printf("Could not init PhysFS!\n");
			return LOVE_ERROR;
		}

		// Set base and user dir
		this->base = string(PHYSFS_getBaseDir());
		this->user = string(PHYSFS_getUserDir());
			
		return LOVE_OK;
	}

	int PhysFSFileSystem::configure(Parameters * parameters)
	{
		
		if(parameters->exists("--base"))
			this->base = parameters->get("--base");

		if(parameters->exists("--user"))
			this->user = parameters->get("--user");


		return LOVE_OK;
	}

	vector<string> PhysFSFileSystem::getList(const string & source, const string & file)
	{

		vector<string> file_list;

		add(source);

		char **rc = PHYSFS_enumerateFiles(file.c_str());
		char **i;

		remove(source);

		// Loop through each game.
		for (i = rc; *i != 0; i++)
		{
			file_list.push_back(*i);
		}

		// Free PhysFS resources.
		PHYSFS_freeList(rc);

		return file_list;
	}

	bool PhysFSFileSystem::exists(const string & source, const string & file) const
	{
		// Add source.
		add(source);

		// Check for existence.
		int existence = PHYSFS_exists (file.c_str());

		// Remove source.
		remove(source);

		return (existence != 0);
	}

	bool PhysFSFileSystem::isFile(const string & source, const string & file)
	{
		bool is_file = true;

		// Check if it exists
		if(!exists(source, file))
			return false; // No, it's not a file.

		// Add source.
		add(source);		

		// Check if it's a dir.
		if(PHYSFS_isDirectory(file.c_str()))
			is_file = false;

		// Remove source.
		remove(source);

		return is_file;

	}

	bool PhysFSFileSystem::isDir(const string & source, const string & file)
	{
		bool dir = false;

		// Check if it exists
		if(!exists(source, file))
			return false; // No, it's not a dir.

		// Add source.
		add(source);		

		// Check if it's a dir.
		if(PHYSFS_isDirectory(file.c_str()))
			dir = true;

		// Remove source.
		remove(source);

		return dir;
	}

	bool PhysFSFileSystem::add(const string & path) const
	{
		// Try to add the source.
		if(!PHYSFS_addToSearchPath(path.c_str(), 1))
		{
			printf("PhysFS error when adding source \"%s\": %s\n", path.c_str(), PHYSFS_getLastError());	
			return false;
		}

		return true;
	}

	bool PhysFSFileSystem::remove(const string & path) const
	{
	
		// Try to remove source.
		if(!PHYSFS_removeFromSearchPath(path.c_str()))
		{
			printf("PhysFS error when removing source \"%s\": %s\n", path.c_str(), PHYSFS_getLastError());	
			return false;
		}

		return true;
	}

}// love
