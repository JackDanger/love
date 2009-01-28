/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "wrap_Music.h"

namespace love
{
namespace audio
{
namespace openal
{
	Music * luax_checkmusic(lua_State * L, int idx)
	{
		return luax_checktype<Music>(L, idx, "Music", LOVE_AUDIO_MUSIC_BITS);
	}

	static const luaL_Reg wrap_Music_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

	int wrap_Music_open(lua_State * L)
	{
		luax_register_type(L, "Music", wrap_Music_functions);
		return 0;
	}

} // openal
} // audio
} // love
