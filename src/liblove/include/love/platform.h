/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* Create pretty platform defines.
* 
* @author Anders Ruud
* @date 2008-07-01
*/

#ifndef LOVE_PLATFORM_H
#define LOVE_PLATFORM_H

#if defined(WIN32) || defined(_WIN32)
#	define LOVE_WINDOWS
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
#	define LOVE_LINUX
#endif
#if defined(__APPLE__)
#	define LOVE_MACOSX
#endif
#if defined(macintosh)
#	define LOVE_MACOS
#endif

#endif //LOVE_PLATFORM_H

