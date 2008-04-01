/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* Modules that require filesystem support are treated
* as special modules, and need to include this header 
* file instead of mod.h. 
* 
* @author Anders Ruud
* @date 2008-03-17
*/

#ifndef LOVE_MODFS_H
#define LOVE_MODFS_H

// This is an extension to mod, so we'll be needing that.
#include "mod.h"

// Filesystem-stuff.
#include "Filesystem.h"
#include "File.h"
#include "Resource.h"

using love::Filesystem;

/**
* We use the same namespace as in mod.
**/
namespace love_mod
{
	/**
	* Sets the currently active filesystem. This must 
	* obviously be set for any modfs module.
	* @param f A pointer to the current filesystem object.
	**/
	void setFilesystem(Filesystem * f);

	/**
	* Loads a file.
	**/
	bool load(love::pFile & f);

	/**
	* Unloads a file.
	**/
	bool unload(love::pFile & f);

	/**
	* Creates a new file object. (Does not load
	* or anything else).
	**/
	love::pFile newFile( const char * filename );
}

#endif // LOVE_MODFS_H
