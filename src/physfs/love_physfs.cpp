#include "love_physfs.h"
#include "mod_physfs.h"

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

namespace love_physfs
{

	// List of filesystem states.
	std::vector<state> states;

	// Counts open files.
	int open_count = 0;

	// Pointer used for file reads.
	char * buffer = 0;
	
	// Buffer used for getcwd in Linux.
#ifdef WIN32
	char cwdbuffer[_MAX_PATH];
#else
	char cwdbuffer[MAXPATHLEN];
#endif

	// This directory will be set at the 
	// first file write.
	std::string save_dir;

	love::Core * core = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.filesystem [" << "PhysFS" << "]" << std::endl;

		love_physfs::core = core;

		if(!PHYSFS_init(argv[0]))
		{
			std::cerr << "Count not init PhysFS" << std::endl;
			return false;
		}

		if(!push())
		{
			std::cerr << "Could not push filesystem state." << std::endl;
			return false;
		}

		// Set function pointers and load module.
		{
			love::Filesystem * f = core->getFilesystem();
			f->getFile = love_physfs::getFile;
			f->exists = love_physfs::exists;
			f->setSaveDirectory = love_physfs::setSaveDirectory;
			f->addDirectory = love_physfs::addDirectory;
			f->getBaseDirectory = love_physfs::getBaseDirectory;
			f->loaded = true;
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
		_getcwd(cwdbuffer, _MAX_PATH);
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

		// If / is the last char, remove it.
		while(pos == l.length() - 1 && l.length() > 0)
		{
			l = l.substr(0, l.length()-1);
			pos = l.find_last_of("/"); // Update position.
		}

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

	love::pFile * getFile(const char * filename, int mode)
	{
		love::pFile * file = new love::pFile(new File(std::string(filename), mode));
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

	bool setupWriteDirectory()
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

		bool success = file->open();

		if(!success)
		{
			std::cerr << "Error, could not open file: " << PHYSFS_getLastError() << std::endl;
			return false;
		}
		
		open_count++;
		return true;
	}

	bool close(pFile & file)
	{
		if(!file->close())
			return false;
		open_count--;
		return true;
	}

	int read(lua_State * L)
	{
		// The file to read from.
		pFile file;
		bool close;
		
		if(mod_is_file(L, 1))
		{
			file = mod_to_file(L, 1);
			close = false;
		}
		else if(lua_isstring(L, 1))
		{
			file.reset<File>(new File(lua_tostring(L, 1)));
			close = true;
			if(!open(file))
				return luaL_error(L, "Could not open file %s.", lua_tostring(L, 1));
		}
		else
			return luaL_error(L, "Expected filename or file handle.");

		int count = luaL_optint(L, 2, file->getSize());

		if(buffer != 0)
		{
			delete [] buffer;
			buffer = 0;
		}

		buffer = new char[count];

		int read = file->read(buffer, count);

		// Close the file, if applicable.
		if(close)
			love_physfs::close(file);

		if(read < 0)
			return luaL_error(L, "File could not be read (is it open?).");

		lua_pushlstring(L, buffer, read);
		return 1;
	}

	int write(lua_State * L)
	{
		// The file to write to.
		pFile file;
		bool close;
		
		if(mod_is_file(L, 1))
		{
			file = mod_to_file(L, 1);
			close = false;
		}
		else if(lua_isstring(L, 1))
		{

			close = true;

			// It should be possible to use append mode.
			int mode = luaL_optint(L, 3, love::FILE_WRITE);
			mode = (mode == love::FILE_APPEND) ? love::FILE_APPEND : love::FILE_WRITE;

			// Open the file.
			file.reset<File>(new File(lua_tostring(L, 1), mode));

			if(!open(file))
				return luaL_error(L, "Could not open file %s.", lua_tostring(L, 1));
		}
		else
			return luaL_error(L, "Expected filename or file handle.");

		if(!lua_isstring(L, 2))
			return luaL_error(L, "Second argument must be a string.");

		// Get the data.
		const char * data = lua_tostring(L, 2);

		// Write the data.
		bool success = file->write(data);

		if(close)
			love_physfs::close(file);

		if(!success)
			return luaL_error(L, "Data could not be written.");

		lua_pushboolean(L, success);
		return 1;
	}

	bool eof(pFile & file)
	{
		return file->eof();
	}

	int tell(pFile & file)
	{
		return file->tell();
	}

	bool seek(pFile & file, int pos)
	{
		return file->seek(pos);
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

	int lines(lua_State * L)
	{
		pFile file;

		if(mod_is_file(L, 1))
		{
			file = mod_to_file(L, 1);
			lua_pushboolean(L, 0); // 0 = do not close.
		}
		else if(lua_isstring(L, 1))
		{
			file.reset<File>(new File(lua_tostring(L, 1)));
			if(!open(file))
				return luaL_error(L, "Could not open file %s.\n", lua_tostring(L, 1)); 
			lua_pop(L, 1);
			mod_push_file(L, file);
			lua_pushboolean(L, 1); // 1 = autoclose.
		}
		else
			return luaL_error(L, "Expected filename or file handle.");

		// Reset the file position.
		if(!file->seek(0))
			return luaL_error(L, "File does not appear to be open.\n");

		lua_pushcclosure(L, lines_iterator, 2);
		return 1;
	}

	int lines_iterator(lua_State * L)
	{
		// We're using a 1k buffer.
		const static int bufsize = 8;
		static char buf[bufsize];

		pFile file = mod_to_file(L, lua_upvalueindex(1));
		int close = (int)lua_tointeger(L, lua_upvalueindex(2));

		// Find the next newline.
		// pos must be at the start of the line we're trying to find.
		int pos = file->tell();
		int newline = -1;
		int totalread = 0;

		while(!file->eof())
		{
			int current = file->tell();
			int read = file->read(buf, bufsize);
			totalread += read;

			if(read < 0)
				return luaL_error(L, "Readline failed!");

			for(int i = 0;i<read;i++)
			{
				if(buf[i] == '\n')
				{
					newline = current+i;
					break;
				}
			}
				
			if(newline > 0)
				break;
		}

		// Special case for the last "line".
		if(newline <= 0 && file->eof() && totalread > 0)
			newline = pos + totalread;

		// We've got a newline.
		if(newline > 0)
		{
			// Ok, we've got a line.
			int linesize = (newline-pos);

			// Allocate memory for the string.
			char * str = new char[linesize];

			// Read it.
			file->seek(pos); 
			if(file->read(str, linesize) == -1)
				return luaL_error(L, "Read error.");

			if(str[linesize-1]=='\r')
				linesize -= 1;
			
			lua_pushlstring(L, str, linesize);

			// Free the memory. Lua has a copy now.
			delete[] str;

			// Set the beginning of the next line.
			if(!file->eof())
				file->seek(newline+1);
			
			return 1;
		}

		if(close)
			love_physfs::close(file);

		// else: (newline <= 0)
		return 0;
	}

} // love_physfs
