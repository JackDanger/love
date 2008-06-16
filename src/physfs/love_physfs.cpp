#include "love_physfs.h"

// LOVE
#include <love/Core.h>

// STD
#include <set>
#include <string>

// PhysFS
#include <physfs.h>

// For great CWD. (Current Working Directory)
// Using this instead of boost::filesystem which totally
// cramped our style.
#ifdef WIN32
#	include <direct.h>
#else
#	include <sys/param.h>
#	include <unistd.h>
#endif

// In Windows, we would like to use "LOVE" as the 
// application folder, but in Linux, we like .love.
#ifdef WIN32
#	define LOVE_APPDATA_FOLDER "LOVE"
#else
#	define LOVE_APPDATA_FOLDER ".love"
#endif

// From SWIG.
extern "C" {
	int luaopen_mod_physfs(lua_State * L);
}

namespace love_physfs
{

	// List of filesystem states.
	std::vector<state> states;

	// Counts open files.
	int open_count = 0;

	// Pointer used for file reads.
	char * buffer = 0;
	
	// Buffer used for getcwd in Linux.
#ifndef WIN32
	char cwdbuffer[MAXPATHLEN];
#endif

	// This directory will be set at the 
	// first file write.
	std::string save_dir;

	love::Core * core = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		love_physfs::core = core;

		if(!PHYSFS_init(argv[0]))
		{
			std::cerr << "Count not init PhysFS" << std::endl;
			return false;
		}
		std::cout << "INIT love.filesystem [" << "PhysFS" << "]" << std::endl;

		if(!push())
		{
			std::cerr << "Could not push filesystem state." << std::endl;
			return false;
		}

		return true;
	}

	bool module_quit()
	{
		if(!PHYSFS_deinit())
			return false;
		std::cout << "QUIT love.filesystem [" << "PhysFS" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_physfs(s);
		return true;
	}

	bool push()
	{
		// We can only push if no files are open.
		if(open_count != 0)
			return false;

		// Remove the current state from PhysFS, if any.
		if(!states.empty())
			removeState(states.back());

		// Okay, push a fresh state.
		state s;
		states.push_back(s);
		return true;
	}

	bool pop()
	{
		// We can only pop if no files are open.
		if(open_count != 0)
			return false;

		// Do not pop an empty state stack.
		if(states.empty())
			return false;

		// Remove the old state from PhysFS.
		removeState(states.back());

		// Remove the old state from stack.
		states.pop_back();

		// Restore previous state.
		if(!states.empty())
			addState(states.back());
			
		return true;
	}
	
	bool addState( state & s )
	{
		// Add search directories.
		std::vector<std::string>::iterator i = s.search.begin();
		while( i != s.search.end() )
		{
			if(!addDirectory((*i)))
				return false;
			i++;
		}

		// Set write directory.
		if(!setWriteDirectory(s.write))
			return false;
		return true;
	}

	bool removeState( state & s )
	{
		// Remove search directories.
		std::vector<std::string>::iterator i = s.search.begin();
		while( i != s.search.end() )
		{
			if(!removeDirectory((*i)))
				return false;
			i++;
		}

		// Remove write directory.
		if(!disableWriteDirectory())
			return false;
		return true;
	}

	const char * getUserDirectory()
	{
		return PHYSFS_getUserDir();
	}

	const char * getBaseDirectory()
	{
#ifdef WIN32
		_getcwd(cwdbuffer, MAXPATHLEN);
#else
		getcwd(cwdbuffer, MAXPATHLEN);
#endif
		return cwdbuffer;
	}

	bool setSaveDirectory( const std::string & game )
	{
		


		// Get the "id" of the game.
		std::string gameid = getLeaf(game);

		if(gameid.empty())
			return false;

		std::string appdata = getAppdata();

		// Save this for later.
		save_dir = std::string(LOVE_APPDATA_FOLDER "/") + gameid;

		// Add the directory if it exists.
		// (No error check. If it fails, it's because it 
		// does not exist).
		std::stringstream full;
		full << appdata << "/" << save_dir;
		addDirectory(full.str());

		return true;
	}

	std::string getLeaf(const std::string & full)
	{

		std::string leaf;
		std::string l = full;

#ifdef WIN32
		
		// Replace all \ with /
		{
			size_t pos = l.find("\\");
			while(pos != std::string::npos)
			{
				l.replace(pos, 1, "/");
				pos = l.find("\\", pos+1);
			}
		}
#endif

		// Get the name after the last slash.
		size_t pos = l.find_last_of("/");

		if(pos == std::string::npos)
		{
			// The path is already the leaf.
			leaf = l;
			return leaf;
		}

		// Extract leaf.
		leaf = l.substr(pos+1);

		return leaf;
	}

	std::string getAppdata()
	{
		std::stringstream appdata; 
#ifdef WIN32
		appdata << getenv("APPDATA");
#else
		appdata << getUserDirectory();
#endif
		return appdata.str();
	}

	love::pFile * getFile(const char * filename)
	{
		love::pFile * file = new love::pFile(new File(std::string(filename)));
		return file;
	}
	

	std::string getWriteDirectory()
	{
		const char * dir = PHYSFS_getUserDir();
		if(dir == 0)
			return std::string();
		return std::string(dir);
	}

	bool setWriteDirectory(const std::string & dir)
	{
		if(!PHYSFS_setWriteDir(dir.c_str()))
			return false;
		return true;
	}

	bool disableWriteDirectory()
	{
		if(!PHYSFS_setWriteDir(0))
			return false;
		return true;
	}

	bool addDirectory(const std::string & dir)
	{
		if(!PHYSFS_addToSearchPath(dir.c_str(), 1))
			return false;
		states.back().search.push_back(dir);
		return true;
	}

	bool exists(const std::string & f)
	{
		return exists(f.c_str());
	}

	bool addBaseDirectory()
	{
		std::string base = std::string(getBaseDirectory());
		return addDirectory(base);
	}

	bool removeDirectory(const std::string & dir)
	{
		if(!PHYSFS_removeFromSearchPath(dir.c_str()))
			return false;
		return true;
	}

	pFile newFile(const char * file, int mode)
	{
		if(mode == love::FILE_READ && !exists(file))
		{
			std::stringstream err;
			err << "Could not load file \"" << file << "\". (File does not exist).";
			core->error(err.str().c_str());			
		}

		pFile f(new File(std::string(file), mode));
		return f;
	}

	bool exists(const char * file)
	{
		if(PHYSFS_exists(file))
			return true;
		return false;
	}

	bool isDirectory(const char * file)
	{
		if(PHYSFS_isDirectory(file))
			return true;
		return false;
	}

	bool isFile(const char * file)
	{
		return !isDirectory(file);
	}

	bool mkdir(const char * file)
	{
		if(!PHYSFS_mkdir(file))
			return false;
		return true;
	}

	bool remove(const char * file)
	{
		if(!PHYSFS_delete(file))
			return false;
		return true;
	}

	bool open(pFile & file)
	{

		// Check whether the write directory is set.
		if((file->getMode() == love::FILE_APPEND || file->getMode() == love::FILE_WRITE) && (PHYSFS_getWriteDir() == 0))
		{
			if(save_dir.empty())
			{
				std::cerr << "Write directory is not set!" << std::endl;
				return false;
			}

			std::string appdata = getAppdata();

			// Create directory.
			if(!setWriteDirectory(appdata))
			{
				std::cerr << "Could not set write directory: " << PHYSFS_getLastError() << std::endl;
				return false;
			}

			if(!mkdir(save_dir.c_str()))
			{
				std::cerr << "Could not create directory " << save_dir << ": " << PHYSFS_getLastError() << std::endl;
				return false;
			}

			disableWriteDirectory();

			std::stringstream full;
			full << appdata << "/" << save_dir;

			if(!setWriteDirectory(full.str()))
			{
				std::cerr << "Could not set write directory: " << PHYSFS_getLastError() << std::endl;
				return false;
			}

			if(!addDirectory(full.str()))
			{
				std::cerr << "Could not add directory to search path: " << PHYSFS_getLastError() << std::endl;
				return false;
			}

		}


		// The to-be opened PhysFS file handle.
		PHYSFS_file * f = 0;

		switch(file->getMode())
		{
		case love::FILE_READ:
			f = PHYSFS_openRead(file->getFilename().c_str());
			break;
		case love::FILE_APPEND:
			f = PHYSFS_openAppend(file->getFilename().c_str());
			break;
		case love::FILE_WRITE:
			f = PHYSFS_openWrite(file->getFilename().c_str());
			break;
		}

		if(f == 0)
		{
			std::cerr << "Error, could not open file: " << PHYSFS_getLastError() << std::endl;
			return false;
		}
		
		file->setHandle(f);
		open_count++;
		return true;
	}

	bool close(pFile & file)
	{
		if(file->getHandle() == 0)
			return false;

		if(!PHYSFS_close(file->getHandle()))
			return false;

		file->setHandle(0);
		open_count--;
		return true;
	}

	char * read(pFile & file, int count)
	{
		if(file->getHandle() == 0)
		{
			std::stringstream err;
			err << "Could not read from file \"" << file->getFilename() << 
					"\". File does not appear to be open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(count == -1)
			count = (int)PHYSFS_fileLength(file->getHandle());

		if(buffer != 0)
		{
			delete [] buffer;
			buffer = 0;
		}

		buffer = new char[count];

		if(PHYSFS_read(file->getHandle(), buffer, 1, count) == -1)
			return 0;

		return buffer;
	}

	bool write(pFile & file, const char * data)
	{
		// Try to write.
		int written = static_cast<int>(PHYSFS_write(file->getHandle(), data, 1, (PHYSFS_uint32)strlen(data)));

		// Check that correct amount of data was written.
		if(written != (int)strlen(data))
			return false;

		return true;
	}

	bool eof(pFile & file)
	{
		if(file->getHandle() == 0)
			return false;

		if(PHYSFS_eof(file->getHandle()))
			return true;
		return false;
	}

	int tell(pFile & file)
	{
		if(file->getHandle() == 0)
			return -1;

		return (int)PHYSFS_tell(file->getHandle());
	}

	bool seek(pFile & file, int pos)
	{
		if(file->getHandle() == 0)
			return false;
		
		if(!PHYSFS_seek(file->getHandle(), (PHYSFS_uint64)pos))
			return false;
		return true;
	}

	int enumerate(lua_State * L)
	{
		int n = lua_gettop(L);

		if( n != 1 )
			return luaL_error(L, "Function requires a single parameter.");

		int type = lua_type(L, 1);

		if(type != LUA_TSTRING)
			return luaL_error(L, "Function requires parameter of type string.");	

		const char * dir = lua_tostring(L, 1);
		char **rc = PHYSFS_enumerateFiles(dir);
		char **i;
		int index = 1;

		lua_newtable(L);

		for (i = rc; *i != 0; i++)
		{
			lua_pushinteger(L, index);
			lua_pushstring(L, *i);
			lua_settable(L, -3);
			index++;
		}
			
		PHYSFS_freeList(rc);

		return 1;
	}

} // love_physfs
