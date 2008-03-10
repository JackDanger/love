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

		// From Filesystem.
		pFile newFile(const std::string & source, const std::string & file) const;
		pFile newBaseFile(const std::string & file) const;
		pFile newUserFile(const std::string & file) const;
		pFile newWriteFile(const std::string & file) const;
		pFile newAppendFile(const std::string & file) const;
		std::vector<std::string> getList(const std::string & source, const std::string & file);
		bool exists(const std::string & source, const std::string & file) const;
		bool exists(const std::string & file) const;
		bool isFile(const std::string & source, const std::string & file);
		bool isDir(const std::string & source, const std::string & file);
		bool setGameDirectory(const std::string id);
		bool setWriteDirectory(const std::string dir);
		std::string getWriteDirectory() const;
		bool disableWriteDirectory();
		std::string getLeaf( std::string full );

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
