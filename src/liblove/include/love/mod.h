/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
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

// STD
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

// LOVE
#include "platform.h"
#include "luax.h"
#include "Core.h"
#include "Reference.h"

// For correct linkage across compilers.
#ifdef LOVE_WINDOWS
#	define DECLSPEC __declspec(dllexport)
#else
#	define DECLSPEC
#endif

#endif // LOVE_MOD_H
