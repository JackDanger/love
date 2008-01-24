/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

// This file contains what is needed to access error, 
// warning, and info output functions.

#ifndef LOVE_USING_OUTPUT_H
#define LOVE_USING_OUTPUT_H

#include <string>
#include <sstream>

namespace love
{
	extern void error(const std::string & str);
	extern void warning(const std::string & str);
	extern void info(const std::string & str);
}// love

#endif // LOVE_USING_OUTPUT_H
