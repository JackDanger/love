/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#include "wrap_CircleShape.h"

namespace love
{
namespace physics
{
namespace box2d
{
	CircleShape * luax_checkcircleshape(lua_State * L, int idx)
	{
		return luax_checktype<CircleShape>(L, idx, "CircleShape", LOVE_PHYSICS_CIRCLE_SHAPE_BITS);
	}

	int _wrap_CircleShape_getRadius(lua_State * L)
	{
		CircleShape * c = luax_checkcircleshape(L, 1);
		lua_pushnumber(L, c->getRadius());
		return 1;
	}

	static const luaL_Reg wrap_CircleShape_functions[] = {
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

	int wrap_CircleShape_open(lua_State * L)
	{
		luax_register_type(L, "CircleShape", wrap_CircleShape_functions);
		return 0;
	}

} // box2d
} // physics
} // love
