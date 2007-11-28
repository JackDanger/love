/**
* @file AbstractFileSystem.h
* @author Anders Ruud
* @date 2007-08-16
* @brief Contains definition for class AbstractFileSystem.
**/

#ifndef LOVE_ABSTRACTFILESYSTEM_H
#define LOVE_ABSTRACTFILESYSTEM_H

// LOVE
#include "AbstractDevice.h"
#include "AbstractFile.h"

// STL
#include <string>
#include <vector>

using std::string;
using std::vector;

// Boost
#include <boost/shared_ptr.hpp>


namespace love
{

	/**
	* @class AbstractFileSystem
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-16
	* @brief Superclass for all FileSystem handlers.
	**/
	class AbstractFileSystem : public AbstractDevice
	{
	protected:

		// The base directory. This is usually where
		// the application can be run from, but can be configured to
		// be other places.
		string base;

		// The user home directory. Empty string means that 
		string user;

	public:

		/**
		* @brief Contructs an empty AbstractFileSystem.
		**/
		AbstractFileSystem();
		virtual ~AbstractFileSystem();		

		/**
		* @brief Gets a new AbstractFile.
		* @param source The source from which to load the file.
		* @param file The the filepath relative to the source.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getFile(const string & source, const string & file) const = 0;

		/**
		* @brief Gets a new AbstractFile, relative to base directory.
		* @param file The the filepath relative to the base directory.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getBaseFile(const string & file) const = 0;

		/**
		* @brief Gets a new AbstractFile, relative to user directory.
		* @param file The the filepath relative to the user directory.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getUserFile(const string & file) const = 0;

		/**
		* @brief Gets a list of entries in the specified file (or dir).
		* @param source The source where the file (or dir) resides.
		* @param file The file (or dir) to list entries for.
		* @return A list of entries (files, directories) in the given source.
		**/
		virtual vector<string> getList(const string & source, const string & file) = 0;

		/**
		* @brief Checks if a file exists in the given source.
		* @param source The source where the file resides.
		* @param file The file to check for.
		* @return True if file exists, false otherwise.
		* @note Does not differentiate between directories and files.
		**/
		virtual bool exists(const string & source, const string & file) const = 0;

		/**
		* @brief Checks if a file really is a file (and not a dir).
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" indeed is a file. False if it's a directory, or non-existent.
		**/
		virtual bool isFile(const string & source, const string & file) = 0;

		/**
		* @brief Checks if a "file" really is a directory.
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" is a directory, false if it's a file or non-existent.
		**/
		virtual bool isDir(const string & source, const string & file) = 0;

		/**
		* @brief Get the current base directory.
		* @return The current base directory.
		**/
		const string & getBase() const;

		/**
		* @brief Gets the current user directory.
		* @return The current user directory.
		**/
		const string & getUser() const;

	};

	typedef boost::shared_ptr<AbstractFileSystem> pAbstractFileSystem;

} // love

#endif
