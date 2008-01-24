#include "PhysFSFilesystem.h"
#include "PhysFSFile.h"
#include <physfs.h>

#include "using_output.h"

// boost
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using std::string;
using std::vector;

namespace love
{

	PhysFSFilesystem::PhysFSFilesystem()
	{
	}

	PhysFSFilesystem::~PhysFSFilesystem()
	{
		quit();
	}

	pFile PhysFSFilesystem::newFile(const string & source, const string & file) const
	{
		pFile tmp(new PhysFSFile(source, file));
		return tmp;
	}

	pFile PhysFSFilesystem::newBaseFile(const string & file) const
	{
		pFile tmp(new PhysFSFile(this->base, file));
		return tmp;
	}

	pFile PhysFSFilesystem::newUserFile(const string & file) const
	{
		pFile tmp(new PhysFSFile(this->user, file));
		return tmp;
	}

	bool PhysFSFilesystem::init(int argc, char* argv[])
	{

		// Initialize PhysFS
		if(!PHYSFS_init(argv[0]))
		{
			error("Could not init PhysFS!");
			return false;
		}

		// Set base and user dir
		//base = string(PHYSFS_getBaseDir()); // Using boost::filesystem instead.
		boost::filesystem::path full_path( boost::filesystem::current_path() );
		base = full_path.native_directory_string() + "/";
		user = string(PHYSFS_getUserDir());

		return true;
	}

	void PhysFSFilesystem::quit()
	{
		if(!PHYSFS_deinit())
		{
			//@todo: error
			return;
		}
	}

	vector<string> PhysFSFilesystem::getList(const string & source, const string & file)
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

	bool PhysFSFilesystem::exists(const string & source, const string & file) const
	{
		// Add source.
		add(source);

		// Check for existence.
		int existence = PHYSFS_exists (file.c_str());

		// Remove source.
		remove(source);

		return (existence != 0);
	}

	bool PhysFSFilesystem::exists(const std::string & file) const
	{
		bool exists = add(file);

		if(exists)
			remove(file);

		return exists;
	}

	bool PhysFSFilesystem::isFile(const string & source, const string & file)
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

	bool PhysFSFilesystem::isDir(const string & source, const string & file)
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

	bool PhysFSFilesystem::add(const string & path) const
	{
		// Try to add the source.
		if(!PHYSFS_addToSearchPath(path.c_str(), 1))
		{
			std::stringstream ss;
			ss << "PhysFS error when adding source "; 
			ss << path; ss << ". ";
			ss << PHYSFS_getLastError();
			error(ss.str());
			return false;
		}

		return true;
	}

	bool PhysFSFilesystem::remove(const string & path) const
	{
	
		// Try to remove source.
		if(!PHYSFS_removeFromSearchPath(path.c_str()))
		{
			std::stringstream ss;
			ss << "PhysFS error when removing source "; 
			ss << path; ss << ". ";
			ss << PHYSFS_getLastError();
			error(ss.str());
			return false;
		}

		return true;
	}

}// love
