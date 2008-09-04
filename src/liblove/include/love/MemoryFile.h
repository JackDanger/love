/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MEMORYFILE_H
#define LOVE_MEMORYFILE_H

// LOVE
#include "File.h"

// STL

// Boost

namespace love
{

	/**
	* MemoryFile class is for files that already are pre-loaded into memory
	* during compilation. Used to store default resources.
	*
	* @author Tommy Nguyen
	* @date 2008-02-01
	**/
	class MemoryFile : public File
	{
	private:

		// Pointer to the data.
		char * data;

		// The size of the data.
		int size;

	public:

		/**
		* Constructs a MemoryFile with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		MemoryFile(char *data, int size, const std::string &filename);
		virtual ~MemoryFile();

		// Implements love::File.
		int getSize();
		char * getData();
		bool load();
		void unload(); 
		bool open();
		bool close();
		int read(char * dest, int count = -1);
		bool write(const char * data);
		bool eof();
		int tell();
		bool seek(int pos);

	}; // MemoryFile

} // love

#endif // LOVE_MEMORYFILE_H
