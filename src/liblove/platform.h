/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Creates pretty platform defines.
* 
* @author Anders Ruud
* @date 2008-07-01
*/

#ifndef LOVE_PLATFORM_H
#define LOVE_PLATFORM_H

#if defined(WIN32) || defined(_WIN32)
#	define LOVE_WINDOWS 1
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
#	define LOVE_LINUX 1
#endif
#if defined(__APPLE__)
#	define LOVE_MACOSX 1
#endif
#if defined(macintosh)
#	define LOVE_MACOS 1
#endif

// For correct linkage across compilers.
#ifdef LOVE_WINDOWS
#	ifndef DECLSPEC
#		define DECLSPEC __declspec(dllexport)
#	endif
#else
#	ifndef DECLSPEC
#		define DECLSPEC
#	endif
#endif

#endif //LOVE_PLATFORM_H

