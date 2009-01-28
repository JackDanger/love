/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-10
**/

#include "wrap_Shape.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Shape * luax_checkshape(lua_State * L, int idx)
	{
		return luax_checktype<Shape>(L, idx, "Shape", LOVE_PHYSICS_SHAPE_BITS);
	}

	int _wrap_Shape_getType(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushinteger(L, t->getType());
		return 1;
	}

	int _wrap_Shape_setFriction(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setFriction(arg1);
		return 0;
	}

	int _wrap_Shape_setRestitution(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setRestitution(arg1);
		return 0;
	}

	int _wrap_Shape_setDensity(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		float arg1 = (float)luaL_checknumber(L, 2);
		t->setDensity(arg1);
		return 0;
	}

	int _wrap_Shape_setSensor(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		bool arg1 = luax_toboolean(L, 2);
		t->setSensor(arg1);
		return 0;
	}

	int _wrap_Shape_getFriction(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushnumber(L, t->getFriction());
		return 1;
	}

	int _wrap_Shape_getRestituion(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushnumber(L, t->getRestituion());
		return 1;
	}

	int _wrap_Shape_getDensity(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushnumber(L, t->getDensity());
		return 1;
	}

	int _wrap_Shape_isSensor(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		luax_pushboolean(L, t->isSensor());
		return 1;
	}

	int _wrap_Shape_getBody(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		Body * body = t->getBody();
		if(body == 0)
			return 0;
		luax_newtype(L, "Body", LOVE_PHYSICS_BODY_BITS, (void*)body);
		return 1;
	}

	int _wrap_Shape_testPoint(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		luax_pushboolean(L, t->testPoint(x, y));
		return 1;
	}

	int _wrap_Shape_testSegment(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		return t->testSegment(L);
	}

	int _wrap_Shape_setCategoryBits(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		int arg1 = luaL_checkint(L, 2);
		t->setCategoryBits(arg1);
		return 0;
	}

	int _wrap_Shape_getCategoryBits(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushinteger(L, t->getCategoryBits());
		return 1;
	}

	int _wrap_Shape_setMaskBits(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		int arg1 = luaL_checkint(L, 2);
		t->setMaskBits(arg1);
		return 0;
	}

	int _wrap_Shape_getMaskBits(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_pushinteger(L, t->getMaskBits());
		return 1;
	}

	int _wrap_Shape_setCategory(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->setCategory(L);
	}

	int _wrap_Shape_getCategory(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->getCategory(L);
	}

	int _wrap_Shape_setMask(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->setMask(L);
	}

	int _wrap_Shape_getMask(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->getMask(L);
	}

	int _wrap_Shape_setData(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->setData(L);
	}

	int _wrap_Shape_getData(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->getData(L);
	}

	int _wrap_Shape_getBoundingBox(lua_State * L)
	{
		Shape * t = luax_checkshape(L, 1);
		lua_remove(L, 1);
		return t->getBoundingBox(L);
	}

	static const luaL_Reg wrap_Shape_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
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

	int wrap_Shape_open(lua_State * L)
	{
		luax_register_type(L, "Shape", wrap_Shape_functions);
		return 0;
	}

} // box2d
} // physics
} // love

