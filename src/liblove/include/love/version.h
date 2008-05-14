/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* This file contains information about which 
* LOVE version this is, and a function for checking
* game compatability.
* 
* @author Anders Ruud
* @date 2008-03-29
*/

#ifndef LOVE_VERSION_H
#define LOVE_VERSION_H

// Version defines.
#define LOVE_VERSION_MAJOR 0
#define LOVE_VERSION_MINOR 2
#define LOVE_VERSION_REV 2
#define LOVE_VERSION_STR "0.2.2"
#define LOVE_VERSION_COMPATIBILITY LOVE_VERSION_STR " 0.2.1"
#define LOVE_VERSION_CODENAME "Mutant Vermin"
#define LOVE_VERSION_FULL_STR LOVE_VERSION_STR " (" LOVE_VERSION_CODENAME ")"

namespace love
{
	/**
	* Checks if this version is compatible with a game
	* written for another version of LOVE.
	**/
	bool is_compatible(const char * version_str);
}

#endif // LOVE_VERSION_H
