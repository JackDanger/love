/**
* @file PhysFSFileSystem.h
* @author Anders Ruud
* @date 2007-08-16
* @brief Contains definition for class PhysFSFileSystem.
**/

#ifndef LOVE_PHYSFS_FILESYSTEM_H
#define LOVE_PHYSFS_FILESYSTEM_H

// LOVE
#include "AbstractFileSystem.h"

// STL
#include <string>
#include <vector>

using std::string;
using std::vector;

// Boost
#include <boost/shared_ptr.hpp>


namespace love
{
	// Forward declarations
	class AbstractFile;

	/**
	* @class PhysFSFileSystem
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-16
	* @brief A filesystem implementation using PhysFS.
	**/
	class PhysFSFileSystem : public AbstractFileSystem
	{

	private:

		// Command line arguments
		int argc;
		char ** argv;

	public:


		/**
		* @brief Constructs a new PhysFSFileSystem.
		* @param argc The number of command line arguments.
		* @param argv The command line arguments.
		**/
		PhysFSFileSystem(int argc, char ** argv);

		/**
		* @brief Destructor.
		**/
		virtual ~PhysFSFileSystem();	

		/**
		* @brief Inits the PhysFSFileSystem. 
		* @return Returns LOVE_OK if no errors.
		**/
		int init();

		/**
		* @brief Configure the system with pre-parsed parameters.
		* @param parameters Pointer to the parameters.
		* @return LOVE_OK if no errors.
		**/
		int configure(Parameters * parameters);

		/**
		* @brief Gets a new AbstractFile.
		* @param source The source from which to load the file.
		* @param file The the filepath relative to the source.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getFile(const string & source, const string & file) const;

		/**
		* @brief Gets a new AbstractFile, relative to base directory.
		* @param file The the filepath relative to the base directory.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getBaseFile(const string & file) const;

		/**
		* @brief Gets a new AbstractFile, relative to user directory.
		* @param file The the filepath relative to the user directory.
		* @return The new AbstractFile. (Unloaded)
		**/
		virtual pAbstractFile getUserFile(const string & file) const;

		/**
		* @brief Gets a list of entries in the specified file (or dir).
		* @param source The source where the file (or dir) resides.
		* @param file The file (or dir) to list entries for.
		* @return A list of entries (files, directories) in the given source.
		**/
		virtual vector<string> getList(const string & source, const string & file);

		/**
		* @brief Checks if a file exists in the given source.
		* @param source The source where the file resides.
		* @param file The file to check for.
		* @return True if file exists, false otherwise.
		* @note Does not differentiate between directories and files.
		**/
		virtual bool exists(const string & source, const string & file) const;


		/**
		* @brief Checks if a file really is a file (and not a dir).
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" indeed is a file. False if it's a directory, or non-existent.
		**/
		virtual bool isFile(const string & source, const string & file);

		/**
		* @brief Checks if a "file" really is a directory.
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" is a directory, false if it's a file or non-existent.
		**/
		virtual bool isDir(const string & source, const string & file);


	private:

		/**
		* @brief Adds the path to the current PhysFS search path.
		* @param path The path to add.
		* @return True on success, false otherwise.
		**/
		bool add(const string & path) const;

		/**
		* @brief Removes the path from the current PhysFS seatch path.
		* @param path The path to remove.
		* @return True on success, false otherwise.
		**/
		bool remove(const string & path) const;

	};

	typedef boost::shared_ptr<PhysFSFileSystem> pPhysFSFileSystem;

} // love

#endif

