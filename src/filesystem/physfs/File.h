/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
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
