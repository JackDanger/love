/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* -- LOVE Development Team, http://love2d.org
**/

#ifndef LOVE_FILESYSTEM_FILE_H
#define LOVE_FILESYSTEM_FILE_H

// LOVE
#include "../Object.h"
#include "../constants.h"

// STL
#include <string>

namespace love
{
namespace filesystem
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
	class File : public Object
	{
	protected:

		// filename
		std::string filename;

		// The file-open mode. (Read, ReadWrite, etc)
		int mode;

	public:

		/**
		* Constructs an empty file.
		**/
		File();

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
		* Gets the extention of the file.
		**/
		std::string getExtention() const;
			
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

} // filesystem
} // love

#endif // LOVE_FILESYSTEM_FILE_H
