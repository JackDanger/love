/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/
#ifndef LOVE_MOD_PHYSFS_H
#define LOVE_MOD_PHYSFS_H

// LOVE
#include <love/mod.h>
#include <love/File.h>
#include <love/MemoryFile.h>

// Module
#include "File.h"

// STD
#include <vector>
#include <string>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_physfs
{
	// Standard module functions.
	bool module_init(love::Core * core);
	bool module_quit(love::Core * core);
	bool module_open(love::Core * core);

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
	pFile newFile(const char * file, int mode = love::FILE_READ);

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
	bool open(pFile & file);

	/**
	* Closes a file.
	* @param file The file to close.
	**/
	bool close(pFile & file);

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
	bool eof(pFile & file);

	/**
	* Gets the current position in a file.
	* @param file An open File.
	**/
	int tell(pFile & file);

	/**
	* Seek to a position within a file.
	* @param pos The position to seek to.
	**/
	bool seek(pFile & file, int pos);

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

} // love_physfs

#endif // LOVE_MOD_PHYSFS_H 
