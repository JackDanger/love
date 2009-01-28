/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "wrap_Audible.h"

namespace love
{
namespace audio
{
namespace openal
{
	Audible * luax_checkaudible(lua_State * L, int idx)
	{
		return luax_checktype<Audible>(L, idx, "Audible", LOVE_AUDIO_AUDIBLE_BITS);
	}

	static const luaL_Reg wrap_Audible_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

	int wrap_Audible_open(lua_State * L)
	{
		luax_register_type(L, "Audible", wrap_Audible_functions);
		return 0;
	}

} // openal
} // audio
} // love
