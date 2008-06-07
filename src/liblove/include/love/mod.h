/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
* 
* This is a simple header file which is to be included
* all modules. It contains header that all modules use, 
* and some preprocessor definitions.
* 
* @author Anders Ruud
* @date 2008-03-17
*/

#ifndef LOVE_MOD_H
#define LOVE_MOD_H

// For correct linkage across compilers.
#ifdef WIN32
#	define DECLSPEC __declspec(dllexport)
#else
#	define DECLSPEC
#endif

// All modules need Lua.
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

// STD
#include <string>
#include <sstream>
#include <iostream>

// LOVE
namespace love 
{
	// Forward declare.
	class Core; 
}

#endif // LOVE_MOD_H
