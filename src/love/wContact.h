/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#ifndef LOVE_CONTACT_W
#define LOVE_CONTACT_W

#include "luax.h"

#include "wwrap.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{
	static const bits LOVE_WRAP_CONTACT_BITS = (LOVE_CONTACT_BITS | LOVE_WRAP_BITS);

	// This macro makes checking for the correct type slightly more compact.
	#define luax_checkcontact(L, idx) luax_checktype<Contact>(L, 1, "Contact", LOVE_WRAP_CONTACT_BITS)

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

	static const luaL_Reg Contact_mt[] = {
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

} // love
} // LOVE_WRAP_NAMESPACE

#endif // LOVE_CONTACT_W
