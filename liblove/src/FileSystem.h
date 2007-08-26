/**
* @file FileSystem.h
* @author Anders Ruud
* @date 2007-07-31
* @brief Contains definition for class FileSystem.
**/

#ifndef LOVE_FILESYSTEM_H
#define LOVE_FILESYSTEM_H

// LOVE

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{

	/**
	* @class FileSystem
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-07-31
	* @brief 
	**/
	class FileSystem
	{
	private:

	public:

		/**
		* @brief Contructs an empty FileSystem.
		**/
		FileSystem();
		
		/**
		* @brief Destructor.
		**/
		virtual ~FileSystem();


		/**
		* @brief Sets the source for reading files.
		* @param element The archive filename or directory.
		* @note Can be a directory (usually the game directory) or the 
		* filename to a .zip or .7z file.
		**/
		void setSource(const string & element);


		/**
		* @brief Removes the current source.
		* @return True if successful, false otherwise. Fails if there are open file pointers.
		**/
		bool clearSource();


		/**
		* @brief Checks if a file with the specified filename exists. 
		* @return True if file exists, false otherwise. Will also true if a directory exists
		* with the specified filename.
		**/
		bool exists(const string & file);

	};

	typedef boost::shared_ptr<FileSystem> pFileSystem;

} // love

#endif
