/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_PHYSFS_FILE_H
#define LOVE_PHYSFS_FILE_H

// LOVE
#include "File.h"

namespace love
{

	/**
	* File implementation using PhysFS.
	* 
	* @author Anders Ruud
	* @date 2007-08-05
	**/
	class PhysFSFile : public File
	{
	private:
	public:

		/**
		* Constructs an PhysFSFile with the given source and filename.
		* @param source The source from which to load the file. (Archive or directory)
		* @param filename The relative filepath of the file to load from the source.
		**/
		PhysFSFile(const std::string & source, const std::string & filename);

		virtual ~PhysFSFile();

		// From file.
		bool load();

	private:

		void fail();
		void removeSource();

	}; // PhysFSFile

} // love

#endif // LOVE_PHYSFS_FILE_H
