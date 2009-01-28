/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_FILESYSTEM_PHYSFS_WRAP_FILE_H
#define LOVE_FILESYSTEM_PHYSFS_WRAP_FILE_H

// LOVE
#include "../../luax.h"
#include "../../wrap.h"
#include "File.h"

namespace love
{
namespace filesystem
{
namespace physfs
{
	File * luax_checkfile(lua_State * L, int idx);
	int _wrap_File_getSize(lua_State * L);
	int wrap_File_open(lua_State * L);

} // physfs
} // filesystem
} // love

#endif // LOVE_FILESYSTEM_PHYSFS_WRAP_FILE_H
