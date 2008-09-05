/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_FILE_H
#define LOVE_FILE_H

// LOVE
#include "constants.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* Abstract File class. An important property of
	* the File class is that it is able to load and unload 
	* itself. (But of course, the methods it uses to achieve this
	* must be specified in some non-abstract module).
	*
	* @author Anders Ruud
	* @date 2007-08-05
	**/
	class File
	{
	protected:

		// filename
		std::string filename;

		// The file-open mode. (Read, ReadWrite, etc)
		int mode;

	public:

		/**
		* Constructs an File with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		File(const std::string & filename, int mode = FILE_READ);

		virtual ~File();

		/**
		* Gets the filename of the file we are loading.
		**/
		const std::string & getFilename() const;
			
		/**
		* Gets the current file mode.
		**/
		int getMode() const;

		/**
		* Gets the size of the loaded file.
		**/
		virtual int getSize() = 0;

		/**
		* Gets a pointer to the loaded data.
		**/
		virtual char * getData() = 0;

		virtual bool load() = 0;
		virtual void unload() = 0; 
		virtual bool open() = 0;
		virtual bool close() = 0;
		virtual int read(char * dest, int count = -1) = 0;
		virtual bool write(const char * data, int count = -1) = 0;
		virtual bool eof() = 0;
		virtual int tell() = 0;
		virtual bool seek(int pos) = 0;

	}; // File

	typedef boost::shared_ptr<File> pFile;

} // love

#endif // LOVE_FILE_H
