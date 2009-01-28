/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-09
**/

#ifndef LOVE_PHYSICS_BOX2D_WRAP_CONTACT_H
#define LOVE_PHYSICS_BOX2D_WRAP_CONTACT_H

// LOVE
#include "../../wrap.h"
#include "Contact.h"

namespace love
{
namespace physics
{
namespace box2d
{
	Contact * luax_checkcontact(lua_State * L, int idx);
	int _wrap_Contact_getPosition(lua_State * L);
	int _wrap_Contact_getVelocity(lua_State * L);
	int _wrap_Contact_getNormal(lua_State * L);
	int _wrap_Contact_getSeparation(lua_State * L);
	int _wrap_Contact_getFriction(lua_State * L);
	int _wrap_Contact_getRestitution(lua_State * L);
	int wrap_Contact_open(lua_State * L);

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WRAP_CONTACT_H
