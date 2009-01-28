/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "wrap_Sound.h"

namespace love
{
namespace audio
{
namespace openal
{
	Sound * luax_checksound(lua_State * L, int idx)
	{
		return luax_checktype<Sound>(L, idx, "Sound", LOVE_AUDIO_SOUND_BITS);
	}

	static const luaL_Reg wrap_Sound_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

	int wrap_Sound_open(lua_State * L)
	{
		luax_register_type(L, "Sound", wrap_Sound_functions);
		return 0;
	}

} // openal
} // audio
} // love
