/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
*
* This file contains version information, configuration
* options, platform macros, etc.
* 
* @author Anders Ruud
* @date 2008-10-28
*/

#ifndef LOVE_CONFIG_H
#define LOVE_CONFIG_H

// STD
#include <string>

// Build.
#define LOVE_BUILD_EXE 1
#define LOVE_BUILD_DLL 0

// Version stuff.
const int LOVE_VERSION = 060;
const int LOVE_VERSION_COMPATIBILITY[] =  { 021,030,031,032,040,050,0 };
const std::string LOVE_VERSION_STR = "0.6.0";
const std::string LOVE_VERSION_CODENAME = "Jiggly Juice";
const std::string LOVE_VERSION_FULL_STR = std::string("LOVE ") + LOVE_VERSION_STR + std::string(" (") + LOVE_VERSION_CODENAME + std::string(")");

// Platform stuff.
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

// DLL-stuff.
#ifdef LOVE_WINDOWS
#	ifndef DECLSPEC
#		define DECLSPEC __declspec(dllexport)
#	endif
#else
#	ifndef DECLSPEC
#		define DECLSPEC
#	endif
#endif

#endif // LOVE_CONFIG_H
