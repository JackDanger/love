/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#include "love_physfs.h"

// STD
#include <iostream>

// Physfs
#include <physfs.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE physfs
#define LOVE_WRAP_BITS LOVE_PHYSFS_BITS
#include "../liblove/wfilesystem.h"

// For great CWD. (Current Working Directory)
// Using this instead of boost::filesystem which totally
// cramped our style.
#ifdef LOVE_WINDOWS
#	include <direct.h>
#else
#	include <sys/param.h>
#	include <unistd.h>
#endif

// In Windows, we would like to use "LOVE" as the 
// application folder, but in Linux, we like .love.
#ifdef LOVE_WINDOWS
#	define LOVE_APPDATA_FOLDER "LOVE"
#	define LOVE_PATH_SEPARATOR "/"
#	define LOVE_MAX_PATH _MAX_PATH
#else
#	define LOVE_APPDATA_FOLDER ".love"
#	define LOVE_PATH_SEPARATOR "/"
#	define LOVE_MAX_PATH MAXPATHLEN
#endif

namespace love
{
namespace physfs
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

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"physfs",
			"filesystem",
			"PhysicsFS Filesystem Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		
		// TODO: love.exe << fail
		if(!PHYSFS_init("love.exe"))
			return luaL_error(L, PHYSFS_getLastError());

		luareg(L);
		luax_register_gc(L, "physfs", luagc);

		// TODO: add searcher function.

		return 0;
	}

	int luagc(lua_State * L)
	{
		PHYSFS_deinit();
		save_path_full.clear();
		save_path_relative.clear();
		save_identity.clear();
		game_source.clear();
		return 0;
	}

	bool setIdentity( const char * ident )
	{
		// Check whether save directory is already set.
		if(!save_identity.empty() || PHYSFS_getWriteDir() != 0)
			return false;

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
			return false;

		// Add the directory.
		if(!PHYSFS_addToSearchPath(source, 0))
			return false;

		// Save the game source.
		game_source = std::string(source);

		return true;
	}

	bool setupWriteDirectory()
	{
		// These must all be set.
		if(save_identity.empty() || save_path_full.empty() || save_path_relative.empty())
			return false;

		// Set the appdata folder as writable directory.
		// (We must create the save folder before mounting it).
		if(!PHYSFS_setWriteDir(getAppdataDirectory()))
			return false;

		// Create the save folder. (We're now "at" %APPDATA%).
		if(!mkdir(save_path_relative.c_str()))
		{	
			PHYSFS_setWriteDir(0); // Clear the write directory in case of error.
			return false;
		}	

		// Set the final write directory.
		if(!PHYSFS_setWriteDir(save_path_full.c_str()))
			return false;

		// Add the directory. (Well not be readded if already present).
		if(!PHYSFS_addToSearchPath(save_path_full.c_str(), 1))
		{
			PHYSFS_setWriteDir(0); // Clear the write directory in case of error.
			return false;
		}

		return true;
	}

	File * newFile(const char * file, int mode)
	{
		if(mode == love::FILE_READ && !exists(file))
			return 0;

		File * f(new File(std::string(file), mode));
		return f;
	}

	const char * getWorkingDirectory()
	{
		#ifdef LOVE_WINDOWS
				_getcwd(cwdbuffer, _MAX_PATH);
		#else
				char * temp = getcwd(cwdbuffer, MAXPATHLEN);
				if(temp == 0)
					return 0;
		#endif
				return cwdbuffer;
	}

	const char * getUserDirectory()
	{
		return PHYSFS_getUserDir();
	}

	const char * getAppdataDirectory()
	{
#ifdef LOVE_WINDOWS
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

	bool open(File * file)
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

	bool close(File * file)
	{
		if(!file->close())
			return false;
		open_count--;
		return true;
	}

	int read(lua_State * L)
	{
		// The file to read from. The file must either be created
		// on-the-fly, or passed as a parameter.
		File * file;
		
		if(luax_istype(L, 1, LOVE_WRAP_FILE_BITS))
		{
			// The file is passed as a parameter.
			file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		}
		else if(lua_isstring(L, 1))
		{
			// Create the file.
			file = new File(lua_tostring(L, 1));

			// Try to open the file.
			if(!open(file))
				return luaL_error(L, "Could not open file %s.", lua_tostring(L, 1));
		}
		else
			return luaL_error(L, "Expected filename or file handle.");

		// Optionally, the caller can specify whether to read
		// the whole file, or just a part of it.
		int count = luaL_optint(L, 2, file->getSize());

		// Allocate new memory.
		char * buffer = new char[count];

		// Read the file. 
		int read = file->read(buffer, count);

		// Error check.
		if(read < 0)
		{
			delete [] buffer;
			return luaL_error(L, "File could not be read (is it open?).");
		}

		// Close and delete the file, if we created it. 
		// (I.e. if the first parameter is a string).
		if(lua_isstring(L, 1))
		{
			love::physfs::close(file);
			delete file;
		}

		// Push the string.
		lua_pushlstring(L, buffer, read);
		
		// Lua has a copy now, so we can free it.
		delete [] buffer;

		return 1;
	}

	int write(lua_State * L)
	{
		// The file to write to. The file must either be created
		// on-the-fly, or passed as a parameter.
		File * file;
		
		// We know for sure that the second parameter must be a 
		// a string, so let's check that first.
		if(!lua_isstring(L, 2))
			return luaL_error(L, "Second argument must be a string.");

		if(luax_istype(L, 1, LOVE_WRAP_FILE_BITS))
		{
			// The file is passed as a parameter.
			file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		}
		else if(lua_isstring(L, 1))
		{
			// It should be possible to use append mode, but
			// normal FILE_WRITE is the default.
			int mode = luaL_optint(L, 3, FILE_WRITE);

			// Create the file.
			file = new File(lua_tostring(L, 1), mode);

			// Open the file.
			if(!open(file))
				return luaL_error(L, "Could not open file.");
		}
		else
			return luaL_error(L, "Expected filename or file handle.");

		// Get the data.
		const char * data = lua_tostring(L, 2);

		// Write the data.
		bool success = file->write(data);

		// Close and delete the file, if we created 
		// it in this function.
		if(lua_isstring(L, 1))
		{
			love::physfs::close(file);
			delete file;
		}

		if(!success)
			return luaL_error(L, "Data could not be written.");

		lua_pushboolean(L, success);
		return 1;
	}

	bool eof(File * file)
	{
		return file->eof();
	}

	int tell(File * file)
	{
		return file->tell();
	}

	bool seek(File * file, int pos)
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
		File * file;

		if(luax_istype(L, 1, LOVE_WRAP_FILE_BITS))
		{
			file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
			lua_pushboolean(L, 0); // 0 = do not close.
		}
		else if(lua_isstring(L, 1))
		{
			file = new File(lua_tostring(L, 1));
			if(!open(file))
				return luaL_error(L, "Could not open file %s.\n", lua_tostring(L, 1)); 
			lua_pop(L, 1);
			// TODO: Really need to check this.
			luax_newtype(L, "File", LOVE_WRAP_FILE_BITS, false);
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

		File * file = luax_checktype<File>(L, lua_upvalueindex(1), "File", LOVE_WRAP_FILE_BITS);
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
		{
			love::physfs::close(file);
			delete file;
		}

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
		File * file = newFile(filename);

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

} // physfs
} // love