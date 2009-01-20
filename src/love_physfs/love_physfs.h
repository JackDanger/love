/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_MODULE_PHYSFS_H
#define LOVE_MODULE_PHYSFS_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/luax.h"

// Module
#include "File.h"

namespace love
{
namespace physfs
{

	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* This sets up the save directory. If the 
	* it is already set up, nothing happens.
	* @return True on success, false otherwise.
	**/
	bool setupWriteDirectory();

	/**
	* Sets the name of the save folder.
	* @param ident The name of the game. Will be used to
	* to create the folder in the LOVE data folder.
	**/
	bool setIdentity(const char * ident);

	/**
	* Sets the path to the game source.
	* This can only be set once.
	* @param source Path to a directory or a .love-file.
	**/
	bool setSource(const char * source);

	/**
	* Creates a new file.
	**/
	File * newFile(const char * file, int mode = love::FILE_READ);

	/**
	* Gets the current working directory.
	**/
	const char * getWorkingDirectory();

	/**
	* Gets the user home directory.
	**/ 
	const char * getUserDirectory();

	/**
	* Gets the APPDATA directory. On Windows, this is the folder
	* in the %APPDATA% enviroment variable. On Linux, this is the
	* user home folder.
	**/
	const char * getAppdataDirectory();

	/**
	* Gets the full path of the save folder.
	**/
	const char * getSaveDirectory();

	/**
	* Checks whether a file exists in the current search path
	* or not. 
	* @param file The filename to check.
	**/
	bool exists(const char * file);

	/**
	* Checks if an existing file really is a directory.
	* @param file The filename to check.
	**/
	bool isDirectory(const char * file);

	/**
	* Checks if an existing file really is a file, 
	* and not a directory.
	* @param file The filename to check.
	**/
	bool isFile(const char * file);

	/**
	* Creates a directory. Write dir must be set.
	* @param file The directory to create.
	**/
	bool mkdir(const char * file);

	/**
	* Removes a file (or directory).
	* @param file The file or directory to remove.
	**/
	bool remove(const char * file);

	/**
	* Opens a file for reading or writing. (Depends
	* on the mode chosen at the time of creation).
	* @param file The file to open.
	**/
	bool open(File * file);

	/**
	* Closes a file.
	* @param file The file to close.
	**/
	bool close(File * file);

	/**
	* Reads count bytes from an open file.
	* The first parameter is either a File or 
	* a string. An optional second parameter specified the
	* max number of bytes to read.
	**/
	int read(lua_State * L);

	/**
	* Write the bytes in data to the file. File
	* must be opened for write.
	* The first parameter is either a File or 
	* a string.
	**/ 
	int write(lua_State * L);

	/**
	* Check if end-of-file is reached.
	* @return True if EOF, false otherwise.
	**/
	bool eof(File * file);

	/**
	* Gets the current position in a file.
	* @param file An open File.
	**/
	int tell(File * file);

	/**
	* Seek to a position within a file.
	* @param pos The position to seek to.
	**/
	bool seek(File * file, int pos);

	/**
	* This "native" method returns a table of all 
	* files in a given directory.
	**/
	int enumerate(lua_State * L);

	/**
	* Returns an iterator which iterates over
	* lines in files.
	**/
	int lines(lua_State * L);

	/**
	* The line iterator function.
	**/
	int lines_i(lua_State * L);

	/**
	* Loads a file without running it. The loaded
	* chunk is returned as a function.
	* @param filename The filename of the file to load.
	* @return A function.
	**/
	int load(lua_State * L);

	// A physfs-compatible package.loader.
	// DO NOT EXPOSE.
	int loader(lua_State * L);

	// TODO: Add require, include

} // physfs
} // love

#endif // LOVE_MODULE_PHYSFS_H