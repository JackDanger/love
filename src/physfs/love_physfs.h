/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/
#ifndef LOVE_MOD_PHYSFS_H
#define LOVE_MOD_PHYSFS_H

// LOVE
#include "../modfs.h"
#include "../constants.h"

// Module
#include "File.h"

// STD
#include <vector>
#include <string>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_physfs
{
	
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC init(love_mod::modconf * conf);
		bool DECLSPEC quit();
		bool DECLSPEC luaopen(lua_State * s);

		/**
		* Helper function that loads a file for internal use.
		* The the original contents of the shared_ptr is removed, 
		* only the filename is used to load the file).
		**/
		bool DECLSPEC load(love::pFile & file);

		/**
		* Unloads a file.
		**/
		bool DECLSPEC unload(love::pFile & file);

		/**
		* Pushes the filesystem state if possible. All directories
		* are removed from the search path. No files can be open
		* when this is called.
		**/
		bool DECLSPEC push();

		/**
		* Removes the current filesystem state, and activates
		* the next filesystem state, if any. No files can be
		* open when this is called.
		**/
		bool DECLSPEC pop();

		/**
		* Adds a directory to the search path.
		**/
		bool DECLSPEC addDir(const std::string & dir);

		/**
		* Adds the base directory to the search path.
		**/
		bool DECLSPEC addBase();

		// Doomed?
		bool DECLSPEC exists(const std::string & f);

		/**
		* Gets the user home directory.
		**/ 
		void DECLSPEC getUserDir(std::string & user);

		/**
		* Gets the directory from which the application 
		* was run.
		**/
		void DECLSPEC getBaseDir(std::string & base);

		/**
		* Setup a save directory for a certain game. 
		**/
		bool DECLSPEC setSaveDirectory( const std::string & gameid );

		/**
		* Gets the leaf node in a full path.
		**/
		void DECLSPEC getLeaf( const std::string & full, std::string & leaf);
	}

	/**
	* A filesystem state. Contains a list of current search
	* paths, and the current write directory.
	**/
	struct state
	{
		std::vector<std::string> search; // Search paths.
		std::string write; // Write directory.
	};

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
	bool removeDir(const std::string & dir);

	/**
	* Gets the current write directory, if any. An empty
	* string will be returned if no directory is set.
	**/
	std::string getWriteDir();

	/**
	* Sets the current write directory.
	**/
	bool setWriteDir(const std::string & dir);

	/**
	* Disables the write directory.
	**/
	bool disableWriteDir();

	/**
	* Gets the size of a file.
	**/
	int size(pFile & file);

	/**
	* Creates a new file.
	**/
	pFile newFile(const char * file, int mode = love::FILE_READ);

	/**
	* Loads and runs a file no matter what. The same
	* file WILL be included twice!
	**/
	void include( const char * file );

	/**
	* Loads and runs a file. The same file will not 
	* be included twice.
	**/
	void require( const char * file );

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

	// @todo
	// enumerate() (Special function in pure SWIG).

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
	* @param file The file handle.
	* @param count The number of bytes to read. Defaults
	* to the size of the file.
	**/
	const char * read(pFile & file, int count = -1);

	/**
	* Write the bytes in data to the file. File
	* must be opened for write.
	* @param file The file handle to write to.
	**/ 
	bool write(pFile & file, const char * data);

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

} // love_physfs

#endif // LOVE_MOD_PHYSFS_H 
