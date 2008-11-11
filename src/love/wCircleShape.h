/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#ifndef LOVE_CIRCLE_SHAPE_W
#define LOVE_CIRCLE_SHAPE_W

#include "luax.h"

#include "wwrap.h"
#include "wShape.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_CIRCLE_SHAPE_BITS = (LOVE_CIRCLE_SHAPE_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkcircleshape(L, idx) luax_checktype<CircleShape>(L, idx, "CircleShape", LOVE_WRAP_CIRCLE_SHAPE_BITS)

	int _wrap_CircleShape_getRadius(lua_State * L)
	{
		CircleShape * c = luax_checkcircleshape(L, 1);
		lua_pushnumber(L, c->getRadius());
		return 1;
	}

	static const luaL_Reg CircleShape_mt[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },

		{ "getRadius", _wrap_CircleShape_getRadius },
		
		// From Shape.
		{ "getType", _wrap_Shape_getType },
		{ "setFriction", _wrap_Shape_setFriction },
		{ "setRestitution", _wrap_Shape_setRestitution },
		{ "setDensity", _wrap_Shape_setDensity },
		{ "setSensor", _wrap_Shape_setSensor },
		{ "getFriction", _wrap_Shape_getFriction },
		{ "getRestituion", _wrap_Shape_getRestituion },
		{ "getDensity", _wrap_Shape_getDensity },
		{ "isSensor", _wrap_Shape_isSensor },
		{ "testPoint", _wrap_Shape_testPoint },
		{ "testSegment", _wrap_Shape_testSegment },
		{ "setCategoryBits", _wrap_Shape_setCategoryBits },
		{ "getCategoryBits", _wrap_Shape_getCategoryBits },
		{ "setMaskBits", _wrap_Shape_setMaskBits },
		{ "getMaskBits", _wrap_Shape_getMaskBits },
		{ "setCategory", _wrap_Shape_setCategory },
		{ "getCategory", _wrap_Shape_getCategory },
		{ "setData", _wrap_Shape_setData },
		{ "getData", _wrap_Shape_getData },
		{ "getBoundingBox", _wrap_Shape_getBoundingBox },
		{ 0, 0 }
	};

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_SHAPE_W
