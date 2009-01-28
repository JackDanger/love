/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-22
**/

#ifndef LOVE_FILESYSTEM_PHYSFS_FILE_H
#define LOVE_FILESYSTEM_PHYSFS_FILE_H

// LOVE
#include "../File.h"

// PhysFS
#include <physfs.h>

namespace love
{
namespace filesystem
{
namespace physfs
{
	class File : public love::filesystem::File
	{
	private:

		// Data for the file.
		char * data;

		// PHYSFS File handle.
		PHYSFS_file * file;

	public:

		/**
		* Constructs an File with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		File(const std::string & filename, int mode = love::FILE_READ);

		virtual ~File();
		
		// Implements love::File.
		int getSize();
		char * getData();
		bool load();
		void unload(); 
		bool open();
		bool close();
		int read(char * dest, int count = -1);
		bool write(const char * data, int count = -1);
		bool eof();
		int tell();
		bool seek(int pos);

	}; // File

} // physfs
} // filesystem
} // love

#endif // LOVE_FILESYSTEM_PHYSFS_FILE_H
