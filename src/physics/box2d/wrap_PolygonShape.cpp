/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "wrap_PolygonShape.h"

namespace love
{
namespace physics
{
namespace box2d
{
	PolygonShape * luax_checkpolygonshape(lua_State * L, int idx)
	{
		return luax_checktype<PolygonShape>(L, idx, "PolygonShape", LOVE_PHYSICS_POLYGON_SHAPE_BITS);
	}

	int _wrap_PolygonShape_getPoints(lua_State * L)
	{
		PolygonShape * t = luax_checkpolygonshape(L, 1);
		lua_remove(L, 1);
		return t->getPoints(L);
	}

	static const luaL_Reg wrap_PolygonShape_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getPoints", _wrap_PolygonShape_getPoints },
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

	int wrap_PolygonShape_open(lua_State * L)
	{
		luax_register_type(L, "PolygonShape", wrap_PolygonShape_functions);
		return 0;
	}

} // box2d
} // physics
} // love
