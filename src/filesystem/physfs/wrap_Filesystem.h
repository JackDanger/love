/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-30
**/

#ifndef LOVE_FILESYSTEM_PHYSFS_WRAP_FILESYSTEM_H
#define LOVE_FILESYSTEM_PHYSFS_WRAP_FILESYSTEM_H

// LOVE
#include "../../luax.h"
#include "Filesystem.h"
#include "wrap_File.h"

namespace love
{
namespace filesystem
{
namespace physfs
{
	int _wrap_setIdentity(lua_State * L);
	int _wrap_setSource(lua_State * L);
	int _wrap_newFile(lua_State * L);
	int _wrap_getWorkingDirectory(lua_State * L);
	int _wrap_getUserDirectory(lua_State * L);
	int _wrap_getAppdataDirectory(lua_State * L);
	int _wrap_getSaveDirectory(lua_State * L);
	int _wrap_exists(lua_State * L);
	int _wrap_isDirectory(lua_State * L);
	int _wrap_isFile(lua_State * L);
	int _wrap_mkdir(lua_State * L);
	int _wrap_remove(lua_State * L);
	int _wrap_open(lua_State * L);
	int _wrap_close(lua_State * L);
	int _wrap_read(lua_State * L);
	int _wrap_write(lua_State * L);
	int _wrap_eof(lua_State * L);
	int _wrap_tell(lua_State * L);
	int _wrap_seek(lua_State * L);
	int _wrap_enumerate(lua_State * L);
	int _wrap_lines(lua_State * L);
	int _wrap_load(lua_State * L);
	int wrap_Filesystem_open(lua_State * L);

} // physfs
} // filesystem
} // love

#endif // LOVE_FILESYSTEM_PHYSFS_WRAP_FILESYSTEM_H
