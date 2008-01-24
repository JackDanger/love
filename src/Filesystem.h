/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_FILESYSTEM_H
#define LOVE_FILESYSTEM_H

// LOVE
#include "Device.h"
#include "File.h"

// STD
#include <string>
#include <vector>

namespace love
{

	/**
	* Filesystem abstraction.
	* 
	* @author Anders Ruud
	* @date 2007-08-16
	**/
	class Filesystem : public Device
	{
		friend bool init(int argc, char* argv[]);

	protected:

		// The base directory. This is usually where
		// the application can be run from, but can be configured to
		// be other places.
		std::string base;

		// The user home directory. Empty string means that 
		std::string user;

	public:

		/**
		* @brief Contructs an empty Filesystem.
		**/
		Filesystem();

		virtual ~Filesystem();		

		/**
		* Gets a new File.
		* @param source The source from which to load the file.
		* @param file The the filepath relative to the source.
		**/
		virtual pFile newFile(const std::string & source, const std::string & file) const = 0;

		/**
		* Gets a new File, relative to base directory.
		* @param file The the filepath relative to the base directory.
		**/
		virtual pFile newBaseFile(const std::string & file) const = 0;

		/**
		* Gets a new File, relative to user directory.
		* @param file The the filepath relative to the user directory.
		**/
		virtual pFile newUserFile(const std::string & file) const = 0;

		/**
		* Gets a list of entries in the specified file (or dir).
		* @param source The source where the file (or dir) resides.
		* @param file The file (or dir) to list entries for.
		**/
		virtual std::vector<std::string> getList(const std::string & source, const std::string & file) = 0;

		/**
		* Checks if a file exists in the given source.
		* @param source The source where the file resides.
		* @param file The file to check for.
		* @note Does not differentiate between directories and files.
		**/
		virtual bool exists(const std::string & source, const std::string & file) const = 0;

		/**
		* Checks if a file exists.
		* @param file The filename.
		**/
		virtual bool exists(const std::string & file) const = 0;

		/**
		* Checks if a file really is a file (and not a dir).
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" indeed is a file. False if it's a directory, or non-existent.
		**/
		virtual bool isFile(const std::string & source, const std::string & file) = 0;

		/**
		* Checks if a "file" really is a directory.
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" is a directory, false if it's a file or non-existent.
		**/
		virtual bool isDir(const std::string & source, const std::string & file) = 0;

		/**
		* Get the current base directory.
		**/
		const std::string & getBase() const;

		/**
		* Gets the current user directory.
		**/
		const std::string & getUser() const;

	}; // Filesystem

} // love

#endif // LOVE_FILESYSTEM_H
