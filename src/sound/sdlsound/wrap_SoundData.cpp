/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "wrap_SoundData.h"

namespace love
{
namespace sound
{
namespace sdlsound
{
	SoundData * luax_checksounddata(lua_State * L, int idx)
	{
		return luax_checktype<SoundData>(L, idx, "SoundData", LOVE_SOUND_SOUND_DATA_BITS);
	}

	static const luaL_Reg wrap_SoundData_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};
	
	int wrap_SoundData_open(lua_State * L)
	{
		luax_register_type(L, "SoundData", wrap_SoundData_functions);
		return 0;
	}

} // sdlsound
} // sound
} // love
