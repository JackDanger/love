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
	public:

		/**
		* Constructs a MemoryFile with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		MemoryFile(char *data, const unsigned long size, const std::string &filename, bool compiled = true);
		~MemoryFile();

		bool load();
		void unload();

	}; // MemoryFile

} // love

#endif // LOVE_MEMORYFILE_H
