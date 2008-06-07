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
		char * buf = _getcwd(0, 0);
#else
		char buf[MAXPATHLEN];
		getcwd(buf, MAXPATHLEN);
#endif
		return buf;
	}

	bool setSaveDirectory( const std::string & gameid )
	{

		// Get user directory.
		std::string user = std::string(getUserDirectory());

		// Create the .love directory.
		if(!setWriteDirectory(user))
			return false;

		// Create the love folder.
		if(!mkdir(".love"))
		{
			printf(PHYSFS_getLastError());
			disableWriteDirectory();
			return false;
		}

		// Set the love folder as the write directory.
		if(!setWriteDirectory(user + ".love"))
			return false;

		// Create the game folder.
		if(!mkdir(gameid.c_str()))
		{
			printf(PHYSFS_getLastError());
			disableWriteDirectory();
			return false;
		}

		// Set this as the new directory.
		if(!setWriteDirectory(user + ".love/" + gameid))
			return false;

		// Also add this dir to the search path.
		if(!addDirectory(user + ".love/" + gameid))
			return false;

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
/**
	// Set 
	int include( lua_State * L )
	{
		int n = lua_gettop(L);

		if( n != 1 )
			return luaL_error(L, "Function requires a single parameter.");

		if(lua_type(L, 1) != LUA_TSTRING)
			return luaL_error(L, "Function requires parameter of type string.");	


		std::string s(file);
		
		if(!exists(file))
		{
			love_mod::runtime_error("Could not include " + s + ". File does not exist.");
			return;
		}

		const char * filename = lua_tostring(L, 1);

		love::pFile f(new File(std::string(file)));
		
		if(!f->load())
			return luaL_error(L, "Could not load file.");

		luaL_loadbuffer(L,(const char *)f->getData(), 
						f->getSize(), filename);

		int result = lua_pcall(L, 0, 0, 0);



		return 0;
	}

**/


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
			return false;
		
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

	const char * read(pFile & file, int count)
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

		return (const char *)buffer;
	}

	bool write(pFile & file, const char * data)
	{

		std::string str(data);

		unsigned int written = static_cast<unsigned int>(PHYSFS_write(file->getHandle(), data, 1, (PHYSFS_uint32)str.length()));

		if(written != str.length())
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
