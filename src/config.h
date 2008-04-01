/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* @todo This file isn't done.
* @author Anders Ruud
* @date 2008-03-26
*/
#ifndef LOVE_CONFIG_H
#define LOVE_CONFIG_H

// STD
#include <string>

namespace love
{

#ifdef WIN32

	// Filesystem.
	static const int modules_graphics_num = 1;
	static const std::string modules_filesystem[] = 
	{ 
		"love_physfs.dll" 
	};

	// Physics.
	static const int modules_physics_num = 1;
	static const std::string modules_physics[] = 
	{ 
		"love_chipmunk.dll" 
	};

#else

#endif

} // love

#endif // LOVE_CONFIG_H
