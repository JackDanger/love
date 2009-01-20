/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_SOUND_MODULE_W
#define LOVE_SOUND_MODULE_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wSoundData.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{

	int _wrap_newSoundData(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		File * file = luax_checktype<File>(L, 1, "File", LOVE_FILE_BITS);
		SoundData * t = newSoundData(file);
		luax_newtype(L, "SoundData", LOVE_WRAP_SOUND_DATA_BITS, (void*)t);
		return 1;
	}

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "newSoundData",  _wrap_newSoundData },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "sound", module_fn);
		luax_register_type(L, "SoundData", SoundData_mt);
		return 0;
	}

} // LOVE_WRAP_NAMESPACE
} // love

#endif // LOVE_SOUND_MODULE_W
