/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_PHYSFS_FILE_H
#define LOVE_PHYSFS_FILE_H

// LOVE
#include <love/File.h>

// PhysFS
#include <physfs.h>

namespace love_physfs
{
	/**
	* File implementation using PhysFS.
	* 
	* @author Anders Ruud
	* @date 2007-08-05
	**/
	class File : public love::File
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
		bool write(const char * data);
		bool eof();
		int tell();
		bool seek(int pos);

	}; // File

	typedef boost::shared_ptr<File> pFile;

} // love_physfs

#endif // LOVE_PHYSFS_FILE_H
