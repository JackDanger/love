/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_MODULE_SDLSOUND_H
#define LOVE_MODULE_SDLSOUND_H

// LOVE
#include "../liblove/config.h"
#include "../liblove/filesystem/File.h"
#include "../liblove/luax.h"
#include "../liblove/types.h"

// love_sdlsound
#include "SoundData.h"

namespace love
{
namespace sdlsound
{
	// Standard function.
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	SoundData * newSoundData(File * file);

} // sdlsound
} // love

#endif // LOVE_MODULE_SDLSOUND_H
