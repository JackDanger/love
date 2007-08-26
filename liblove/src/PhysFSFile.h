/**
* @file PhysFSFile.h
* @author Anders Ruud
* @date 2007-08-05
* @brief Contains definition for class PhysFSFile.
**/

#ifndef LOVE_PHYSFS_FILE_H
#define LOVE_PHYSFS_FILE_H

// LOVE
#include "AbstractFile.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class PhysFSFile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-05
	* @brief 
	**/
	class PhysFSFile : public AbstractFile
	{
	private:


	public:

		/**
		* @brief Constructs an PhysFSFile with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		PhysFSFile(const string & source, const string & filename);

		/**
		* @brief Destructor. Calls unload().
		**/ 
		virtual ~PhysFSFile();


		/**
		* @brief Loads the PhysFSFile.
		* @returns LOVE_OK on success.
		**/
		int load();

		/**
		* @brief Unloads the PhysFSFile. (Frees the memory used)
		**/
		void unload();

		

	private:

		void fail();
		void removeSource();


	};

	typedef boost::shared_ptr<PhysFSFile> pPhysFSFile;

} // love

#endif

