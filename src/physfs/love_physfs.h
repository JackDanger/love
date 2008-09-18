/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
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
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	/**
	* Pushes the filesystem state if possible. All directories
	* are removed from the search path. No files can be open
	* when this is called.
	**/
	bool push();

	/**
	* Removes the current filesystem state, and activates
	* the next filesystem state, if any. No files can be
	* open when this is called.
	**/
	bool pop();

	/**
	* Adds a directory to the search path.
	**/
	bool addDirectory(const std::string & dir);

	/**
	* Adds the base directory to the search path.
	**/
	bool addBaseDirectory();

	/**
	* Checks if some file exists in the current search path.
	* @param f The file (or directory) to check for.
	**/
	bool exists(const std::string & f);

	/**
	* Gets the user home directory.
	**/ 
	const char * getUserDirectory();

	/**
	* Gets the directory from which the application 
	* was run.
	**/
	const char * getBaseDirectory();

	/**
	* Setup a save directory for a certain game. 
	* @param game The full or relative path to the game.
	**/
	bool setSaveDirectory( const std::string & game );

	/**
	* Gets a pointer to a file in the search path. The object
	* must be freed by the caller.
	* @param filename The filename (and path) of the file.
	**/
	love::pFile * getFile(const char * filename, int mode);

	/**
	* A filesystem state. Contains a list of current search
	* paths, and the current write directory.
	**/
	struct state
	{
		std::vector<std::string> search; // Search paths.
		std::string write; // Write directory.
	};

	/**
	* Gets the leaf node in a full path.
	**/
	std::string getLeaf(const std::string & full);

	/**
	* Gets the APPDATA directory. On Windows, this is the folder
	* in the %APPDATA% enviroment variable. On Linux, this is the
	* user home folder.
	**/
	std::string getAppdata();

	/**
	* This can be called when Physfs encounters an error. 
	* @return Always false.
	**/
	bool error(const std::string & s);

	/**
	* Adds a state to the stack and to the 
	* PhysFS state.
	**/
	bool addState( state & s );

	/**
	* Removes a state from the PhysFS state only.
	* (Stack must be popped).
	**/
	bool removeState( state & s );

	/**
	* Removes a directory from the PhysFS search path.
	**/
	bool removeDirectory(const std::string & dir);

	/**
	* Gets the current write directory, if any. An empty
	* string will be returned if no directory is set.
	**/
	std::string getWriteDirectory();

	/**
	* Sets the current write directory.
	**/
	bool setWriteDirectory(const std::string & dir);

	/**
	* Disables the write directory.
	**/
	bool disableWriteDirectory();

	/**
	* This sets up the save directory. If the 
	* it is already set up, nothing happens.
	* @return True on success, false otherwise.
	**/
	bool setupWriteDirectory();

	/**
	* Gets the size of a file.
	**/
	int size(pFile & file);

	/**
	* Creates a new file.
	**/
	pFile newFile(const char * file, int mode = love::FILE_READ);

	/**
	* Gets the full path of the save folder.
	**/
	int getSaveDirectory(lua_State * L);

	/**
	* Gets the current working directory.
	**/
	const char * getWorkingDirectory();

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

	// DO NOT EXPOSE.
	int lines_iterator(lua_State * L);

	int load(lua_State * L);

	// A physfs-compatible package.loader.
	// DO NOT EXPOSE.
	int loader(lua_State * L);

} // love_physfs

#endif // LOVE_MOD_PHYSFS_H 
