/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_PHYSFS_FILESYSTEM_H
#define LOVE_PHYSFS_FILESYSTEM_H

// LOVE
#include "Filesystem.h"

namespace love
{

	/**
	* A filesystem implementation using PhysFS.
	*
	* @author Anders Ruud
	* @date 2007-08-16
	**/
	class PhysFSFilesystem : public Filesystem
	{
	private:
	public:


		/**
		* Constructs a new PhysFSFilesystem.
		**/
		PhysFSFilesystem();

		/**
		* @brief Destructor.
		**/
		virtual ~PhysFSFilesystem();	

		// From Device
		bool init(int argc, char* argv[]);
		void quit();

		/**
		* @brief Gets a new File.
		* @param source The source from which to load the file.
		* @param file The the filepath relative to the source.
		* @return The new File. (Unloaded)
		**/
		virtual pFile newFile(const std::string & source, const std::string & file) const;

		/**
		* @brief Gets a new File, relative to base directory.
		* @param file The the filepath relative to the base directory.
		* @return The new File. (Unloaded)
		**/
		virtual pFile newBaseFile(const std::string & file) const;

		/**
		* @brief Gets a new File, relative to user directory.
		* @param file The the filepath relative to the user directory.
		* @return The new File. (Unloaded)
		**/
		virtual pFile newUserFile(const std::string & file) const;

		/**
		* @brief Gets a list of entries in the specified file (or dir).
		* @param source The source where the file (or dir) resides.
		* @param file The file (or dir) to list entries for.
		* @return A list of entries (files, directories) in the given source.
		**/
		virtual std::vector<std::string> getList(const std::string & source, const std::string & file);

		/**
		* @brief Checks if a file exists in the given source.
		* @param source The source where the file resides.
		* @param file The file to check for.
		* @return True if file exists, false otherwise.
		* @note Does not differentiate between directories and files.
		**/
		virtual bool exists(const std::string & source, const std::string & file) const;

		bool exists(const std::string & file) const;

		/**
		* @brief Checks if a file really is a file (and not a dir).
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" indeed is a file. False if it's a directory, or non-existent.
		**/
		virtual bool isFile(const std::string & source, const std::string & file);

		/**
		* @brief Checks if a "file" really is a directory.
		* @param source The source where the "file" resides.
		* @param file The "file" to check.
		* @return True if the "file" is a directory, false if it's a file or non-existent.
		**/
		virtual bool isDir(const std::string & source, const std::string & file);


	private:

		/**
		* @brief Adds the path to the current PhysFS search path.
		* @param path The path to add.
		* @return True on success, false otherwise.
		**/
		bool add(const std::string & path) const;

		/**
		* @brief Removes the path from the current PhysFS seatch path.
		* @param path The path to remove.
		* @return True on success, false otherwise.
		**/
		bool remove(const std::string & path) const;

	}; // PhysFSFilesystem

} // love

#endif // LOVE_PHYSFS_FILESYSTEM_H
