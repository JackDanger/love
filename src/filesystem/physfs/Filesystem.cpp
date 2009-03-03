/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "Filesystem.h"

// Physfs
#include <physfs.h>

namespace love
{
namespace filesystem
{
namespace physfs
{
	// Wrapper loaders.
	extern int wrap_Filesystem_open(lua_State * L);

	Filesystem * Filesystem::_instance = 0;

	Filesystem::Filesystem()
		: open_count(0), buffer(0)
	{
	}

	Filesystem * Filesystem::__getinstance()
	{
		if(_instance == 0)
			_instance = new Filesystem();
		return _instance;
	}

	int Filesystem::__advertise(lua_State * L)
	{
		luax_register_info(L,
			"physfs",
			"filesystem",
			"PhysicsFS Filesystem Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Filesystem::__open(lua_State * L)
	{
		// TODO: love.exe << fail
		if(!PHYSFS_init("love.exe"))
			return luaL_error(L, PHYSFS_getLastError());

		wrap_Filesystem_open(L);
		luax_register_gc(L, "physfs", &__garbagecollect);

		// Add the package loader to the package.loaders table.
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaders");
		int len = lua_objlen(L, -1);
		lua_pushinteger(L, len+1);
		lua_pushcfunction(L, Filesystem::loader);
		lua_settable(L, -3);
		lua_pop(L, 2);

		return 0;
	}

	int Filesystem::__garbagecollect(lua_State * L)
	{
		PHYSFS_deinit();
		Filesystem * m = Filesystem::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	bool Filesystem::setIdentity( const char * ident )
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

	bool Filesystem::setSource(const char * source)
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

	bool Filesystem::setupWriteDirectory()
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

	File * Filesystem::newFile(const char * file, int mode)
	{
		if(mode == FILE_READ && !exists(file))
			return 0;

		return new File(std::string(file), mode);
	}

	const char * Filesystem::getWorkingDirectory()
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

	const char * Filesystem::getUserDirectory()
	{
		return PHYSFS_getUserDir();
	}

	const char * Filesystem::getAppdataDirectory()
	{
#ifdef LOVE_WINDOWS
		return getenv("APPDATA");
#else
		return getUserDirectory();
#endif
	}

	const char * Filesystem::getSaveDirectory()
	{
		return save_path_full.c_str();
	}

	bool Filesystem::exists(const char * file)
	{
		if(PHYSFS_exists(file))
			return true;
		return false;
	}

	bool Filesystem::isDirectory(const char * file)
	{
		if(PHYSFS_isDirectory(file))
			return true;
		return false;
	}

	bool Filesystem::isFile(const char * file)
	{
		return !isDirectory(file);
	}

	bool Filesystem::mkdir(const char * file)
	{
		if(!PHYSFS_mkdir(file))
			return false;
		return true;
	}

	bool Filesystem::remove(const char * file)
	{
		if(!PHYSFS_delete(file))
			return false;
		return true;
	}

	bool Filesystem::open(File * file)
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

	bool Filesystem::close(File * file)
	{
		if(!file->close())
			return false;
		open_count--;
		return true;
	}

	int Filesystem::read(lua_State * L)
	{
		// The file to read from. The file must either be created
		// on-the-fly, or passed as a parameter.
		File * file;
		
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
		{
			// The file is passed as a parameter.
			file = luax_checktype<File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
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
			this->close(file);
			delete file;
		}

		// Push the string.
		lua_pushlstring(L, buffer, read);
		
		// Lua has a copy now, so we can free it.
		delete [] buffer;

		return 1;
	}

	int Filesystem::write(lua_State * L)
	{
		// The file to write to. The file must either be created
		// on-the-fly, or passed as a parameter.
		File * file;
		
		// We know for sure that the second parameter must be a 
		// a string, so let's check that first.
		if(!lua_isstring(L, 2))
			return luaL_error(L, "Second argument must be a string.");

		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
		{
			// The file is passed as a parameter.
			file = luax_checktype<File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
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
			this->close(file);
			delete file;
		}

		if(!success)
			return luaL_error(L, "Data could not be written.");

		lua_pushboolean(L, success);
		return 1;
	}

	bool Filesystem::eof(File * file)
	{
		return file->eof();
	}

	int Filesystem::tell(File * file)
	{
		return file->tell();
	}

	bool Filesystem::seek(File * file, int pos)
	{
		return file->seek(pos);
	}

	int Filesystem::enumerate(lua_State * L)
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

	int Filesystem::lines(lua_State * L)
	{
		File * file;

		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
		{
			file = luax_checktype<File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
			lua_pushboolean(L, 0); // 0 = do not close.
		}
		else if(lua_isstring(L, 1))
		{
			file = new File(lua_tostring(L, 1));
			if(!open(file))
				return luaL_error(L, "Could not open file %s.\n", lua_tostring(L, 1)); 
			lua_pop(L, 1);
			// TODO: Really need to check this.
			luax_newtype(L, "File", LOVE_FILESYSTEM_FILE_BITS, false);
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

	int Filesystem::lines_i(lua_State * L)
	{
		// We're using a 1k buffer.
		const static int bufsize = 8;
		static char buf[bufsize];

		File * file = luax_checktype<File>(L, lua_upvalueindex(1), "File", LOVE_FILESYSTEM_FILE_BITS);
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
			Filesystem::__getinstance()->close(file);
			delete file;
		}

		// else: (newline <= 0)
		return 0;
	}

	int Filesystem::load(lua_State * L)
	{
		// Need only one arg.
		luax_assert_argc(L, 1, 1);

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

	int Filesystem::loader(lua_State * L)
	{
		const char * filename = lua_tostring(L, -1);

		// Check whether file exists.
		if(!Filesystem::__getinstance()->exists(filename))
		{
			lua_pushfstring(L, "\n\tno file \"%s\" in LOVE game directories.\n", filename);
			return 1;
		}
	
		// Ok, load it.
		return Filesystem::__getinstance()->load(L);
	}

} // physfs
} // filesystem
} // love