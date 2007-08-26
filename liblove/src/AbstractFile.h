/**
* @file AbstractFile.h
* @author Anders Ruud
* @date 2007-08-05
* @brief Contains definition for class AbstractFile.
**/

#ifndef LOVE_ABSTRACT_FILE
#define LOVE_ABSTRACT_FILE

// LOVE
#include "Object.h"
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class AbstractFile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-05
	* @brief 
	**/
	class AbstractFile : public Object, public Loadable
	{
	protected:

		// source
		string source;

		// filename
		string filename;

		// The actual file data
		char * data;

		// The size of the data
		unsigned long size;

	public:

		/**
		* @brief Constructs an AbstractFile with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		AbstractFile(const string & source, const string & filename);

		/**
		* @brief Destructor.
		**/
		virtual ~AbstractFile();

		/**
		* @brief Gets source.
		* @return The source from which we are loading files.
		**/
		const string & getSource() const;


		/**
		* @brief Gets filename.
		* @return The filename of the file we are loading.
		**/
		const string & getFilename() const;


		/**
		* @brief Gets the size of the loaded file
		* @returns The size of the loaded file, or 0 if the file is not loaded.
		**/
		unsigned long getSize() const;

		/**
		* @brief Gets a pointer to the data.
		* @return A pointer to data, or 0 if the data is not loaded.
		**/
		char * getData();

		/**
		* @brief Frees resources.
		**/
		virtual void unload();

	};

	typedef boost::shared_ptr<AbstractFile> pAbstractFile;

} // love

#endif

