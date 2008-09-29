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
#	define LOVE_PATH_SEPARATOR "/"
#	define LOVE_MAX_PATH _MAX_PATH
#else
#	define LOVE_APPDATA_FOLDER ".love"
#	define LOVE_PATH_SEPARATOR "/"
#	define LOVE_MAX_PATH MAXPATHLEN
#endif

namespace love_physfs
{

	// Counts open files.
	int open_count = 0;

	// Pointer used for file reads.
	char * buffer = 0;
	
	// Buffer used for getcwd in Linux.
	char cwdbuffer[LOVE_MAX_PATH];

	// This name will be used to create the folder
	// in the appdata/userdata folder.
	std::string save_identity;

	// Full and relative paths of the game save folder. 
	// (Relative to the %APPDATA% folder, meaning that the
	// relative string will look something like: ./LOVE/game)
	std::string save_path_relative, save_path_full;

	// The full path to the source of the game.
	std::string game_source;

	bool module_init(love::Core * core)
	{
		std::cout << "INIT love.filesystem [" << "PhysFS" << "]" << std::endl;

		if(!PHYSFS_init("love.exe"))
		{
			std::cerr << "Count not init PhysFS" << std::endl;
			return false;
		}

		return true;
	}

	bool module_quit(love::Core * core)
	{
		PHYSFS_deinit();
		save_path_full.clear();
		save_path_relative.clear();
		save_identity.clear();
		game_source.clear();
		std::cout << "QUIT love.filesystem [" << "PhysFS" << "]" << std::endl;
		return true;
	}

	bool module_open(love::Core * core)
	{
		lua_State * L = core->getL();
		luaopen_mod_physfs(L);

		// Add the loader function.
		core->addSearcher(loader);

		return true;
	}

	bool setIdentity( const char * ident )
	{
		// Check whether save directory is already set.
		if(!save_identity.empty() || PHYSFS_getWriteDir() != 0)
			return love::core->error("Identifier has already been set");

		// Store the save directory.
		save_identity = std::string(ident);

		// Generate the relative path to the game save folder.
		save_path_relative = std::string(LOVE_APPDATA_FOLDER LOVE_PATH_SEPARATOR) + save_identity;

		// Generate the full path to the game save folder.
		save_path_full = std::string(getAppdataDirectory()) + std::string(LOVE_PATH_SEPARATOR);
		save_path_full += save_path_relative;

		std::cout << save_path_full << std::endl;

		// We now have something like:
		// save_identity: game
		// save_path_relative: ./LOVE/game
		// save_path_full: C:\Documents and Settings\user\Application Data/LOVE/game

		// Try to add the save directory to the search path.
		// (No error on fail, it means that the path doesn't exist).
		PHYSFS_addToSearchPath(save_path_full.c_str(), 1);

		return true;
	}

	bool setSource(const char * source)
	{
		// Check whether directory is already set.
		if(!game_source.empty())
			return love::core->error("Game source has already been set");

		// Add the directory.
		if(!PHYSFS_addToSearchPath(source, 0))
			return love::core->error("Could not add directory: %s", PHYSFS_getLastError());

		// Save the game source.
		game_source = std::string(source);

		return true;
	}

	bool setupWriteDirectory()
	{
		// These must all be set.
		if(save_identity.empty() || save_path_full.empty() || save_path_relative.empty())
			return love::core->error("Can't write files, game save identifier not set.");

		// Set the appdata folder as writable directory.
		// (We must create the save folder before mounting it).
		if(!PHYSFS_setWriteDir(getAppdataDirectory()))
			return love::core->error("Could not set write directory: %s", PHYSFS_getLastError());

		// Create the save folder. (We're now "at" %APPDATA%).
		if(!mkdir(save_path_relative.c_str()))
		{	
			PHYSFS_setWriteDir(0); // Clear the write directory in case of error.
			return love::core->error("Could not mkdir: %s", PHYSFS_getLastError());
		}	

		// Set the final write directory.
		if(!PHYSFS_setWriteDir(save_path_full.c_str()))
			return love::core->error("Could not set write directory: %s", PHYSFS_getLastError());

		// Add the directory. (Well not be readded if already present).
		if(!PHYSFS_addToSearchPath(save_path_full.c_str(), 1))
		{
			PHYSFS_setWriteDir(0); // Clear the write directory in case of error.
			return love::core->error("Could not add directory: %s", PHYSFS_getLastError());
		}

		return true;
	}

	pFile newFile(const char * file, int mode)
	{
		if(mode == love::FILE_READ && !exists(file))
			love::core->error("Could not load file \"%s\": file does not exist.", file);

		pFile f(new File(std::string(file), mode));
		return f;
	}

	const char * getWorkingDirectory()
	{
		#ifdef WIN32
				_getcwd(cwdbuffer, _MAX_PATH);
		#else
				getcwd(cwdbuffer, MAXPATHLEN);
		#endif
				return cwdbuffer;
	}

	const char * getUserDirectory()
	{
		return PHYSFS_getUserDir();
	}

	const char * getAppdataDirectory()
	{
#ifdef WIN32
		return getenv("APPDATA");
#else
		return getUserDirectory();
#endif
	}

	const char * getSaveDirectory()
	{
		return save_path_full.c_str();
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
				return luaL_error(L, "Could not open file.");
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

		lua_pushcclosure(L, lines_i, 2);
		return 1;
	}

	int lines_i(lua_State * L)
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

	int load(lua_State * L)
	{
		// Need only one arg.
		love::luax_assert_argc(L, 1, 1);

		// Must be string.
		if(!lua_isstring(L, -1))
			return luaL_error(L, "The argument must be a string.");

		const char * filename = lua_tostring(L, -1);
		
		// The file must exist.
		if(!exists(filename))
			return luaL_error(L, "File %s does not exist.", filename);

		// Create the file.
		pFile file = newFile(filename);

		if(!file->load())
			return luaL_error(L, "File %s could not be loaded.", filename);

		// Get the data from the file.
		const char * data = file->getData();
		int size = file->getSize();

		// Load the chunk, but don't run it.
		switch (luaL_loadbuffer(L, data, size, filename))
		{
		case LUA_ERRMEM:
			return luaL_error(L, "Memory allocation error: %s\n", lua_tostring(L, -1));
		case LUA_ERRSYNTAX:
			return luaL_error(L, "Syntax error: %s\n", lua_tostring(L, -1));
		default: // success
			return 1;
		}
	}

	int loader(lua_State * L)
	{
		const char * filename = lua_tostring(L, -1);

		// Check whether file exists.
		if(!exists(filename))
		{
			lua_pushfstring(L, "\n\tno file \"%s\" in LOVE game directories.\n", filename);
			return 1;
		}
	
		// Ok, load it.
		return load(L);
	}

} // love_physfs
