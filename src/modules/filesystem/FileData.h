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
**/

#ifndef LOVE_FILESYSTEM_FILE_DATA_H
#define LOVE_FILESYSTEM_FILE_DATA_H

// LOVE
#include <common/Data.h>

// STD
#include <string>

namespace love
{	
namespace filesystem
{
	class FileData : public Data
	{
	private:
	public:

		/**
		* Destructor.
		**/
		virtual ~FileData(){};

		/**
		* Gets a filename for this FileData. 
		* @return The filename for this FileData, with extension.
		**/
		virtual const std::string & getFilename() const = 0;

		/**
		* Gets the file extension for this FileData, or empty string if none.
		* @return The file extension for this FileData (without the dot).
		**/
		virtual const std::string & getExtension() const = 0;

	}; // FileData

} // filesystem
} // love

#endif // LOVE_FILESYSTEM_FILE_DATA_H