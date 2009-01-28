/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#include "wrap_Contact.h"

namespace love
{
namespace physics
{
namespace box2d
{

	Contact * luax_checkcontact(lua_State * L, int idx)
	{
		return luax_checktype<Contact>(L, idx, "Contact", LOVE_PHYSICS_CONTACT_BITS);
	}

	int _wrap_Contact_getPosition(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		return t->getPosition(L);
	}

	int _wrap_Contact_getVelocity(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		return t->getVelocity(L);
	}

	int _wrap_Contact_getNormal(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		return t->getNormal(L);
	}

	int _wrap_Contact_getSeparation(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		lua_pushnumber(L, t->getSeparation());
		return 1;
	}

	int _wrap_Contact_getFriction(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		lua_pushnumber(L, t->getFriction());
		return 1;
	}

	int _wrap_Contact_getRestitution(lua_State * L)
	{
		Contact * t = luax_checkcontact(L, 1);
		lua_pushnumber(L, t->getRestitution());
		return 1;
	}

	static const luaL_Reg wrap_Contact_functions[] = {
		{ "__index", _wrap__index },
		{ "__gc", _wrap__gc },
		{ "getPosition", _wrap_Contact_getPosition },
		{ "getVelocity", _wrap_Contact_getVelocity },
		{ "getNormal", _wrap_Contact_getNormal },
		{ "getSeparation", _wrap_Contact_getSeparation },
		{ "getFriction", _wrap_Contact_getFriction },
		{ "getRestitution", _wrap_Contact_getRestitution },
		{ 0, 0 }
	};

	int wrap_Contact_open(lua_State * L)
	{
		luax_register_type(L, "Contact", wrap_Contact_functions);
		return 0;
	}

} // box2d
} // physics
} // love
