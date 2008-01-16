/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

// Contains version information.

#ifndef LOVE_VERSION_H
#define LOVE_VERSION_H

// STD
#include <string>

namespace love  
{  
	enum { 
		LOVE_MAJOR_VERSION = 0, 
		LOVE_MINOR_VERSION = 1, 
		LOVE_REVISION = 1
	};

	/**
	* Gets the current version in string form.
	**/
	std::string version_string();

} // love

#endif // LOVE_VERSION_H

