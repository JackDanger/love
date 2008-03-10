/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_FILE_H
#define LOVE_FILE_H

// LOVE
#include "love_file.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* Abstract File class. 
	*
	* @author Anders Ruud
	* @date 2007-08-05
	**/
	class File
	{
	protected:

		// source
		std::string source;

		// filename
		std::string filename;

		// The actual file data
		char * data;

		// The size of the data
		unsigned long size;

		// Whether this is a compiled resource or not.
		bool compiled;

		// The file-open mode. (Read, ReadWrite, etc)
		int mode;

		// True if the file is currently open.
		bool isOpen;

		/**
		 * Constructor used by MemoryFile alone.
		 * @param source	The source from which the file is loaded
		 * @param filename	The name of the file loaded
		 * @param data		The actual data loaded
		 * @param size		The size of the loaded data
		 * @param compiled	True if the file is compiled into the executable.
		 **/
		File(const std::string & source, const std::string & filename, char *data, const unsigned long size, bool compiled);

	public:

		/**
		* Constructs an File with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		File(const std::string & source, const std::string & filename, int mode = LOVE_READ);

		virtual ~File();

		/**
		* Gets source from which we are loading files.
		**/
		const std::string & getSource() const;

		/**
		* Gets the filename of the file we are loading.
		**/
		const std::string & getFilename() const;

		/**
		* Gets the size of the loaded file.
		**/
		unsigned long getSize() const;

		/**
		* Gets a pointer to the data.
		**/
		char * getData();

		/**
		* Loads the file.
		**/
		virtual bool load() = 0;

		/**
		* Should free anything allocated by load.
		**/
		virtual void unload();

		virtual bool open() = 0;
		virtual bool close() = 0;
		virtual bool write( std::string data ) = 0;
		virtual const char * read() = 0;

	}; // File

	typedef boost::shared_ptr<File> pFile;

} // love

#endif // LOVE_FILE_H
