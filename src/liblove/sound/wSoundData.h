/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_SOUND_DATA_TYPE_W
#define LOVE_SOUND_DATA_TYPE_W

#include "../luax.h"
#include "../wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_SOUND_DATA_BITS = (LOVE_SOUND_DATA_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checksounddata(L, idx) luax_checktype<SoundData>(L, idx, "SoundData", LOVE_SOUND_DATA_BITS)

	static const luaL_Reg SoundData_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_SOUND_DATA_TYPE_W
