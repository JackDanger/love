/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
*/

#ifndef LOVE_JOYSTICK_SDLJOYSTICK_WRAP_JOYSTICK_H
#define LOVE_JOYSTICK_SDLJOYSTICK_WRAP_JOYSTICK_H

// LOVE
#include "../../wrap.h"

namespace love
{
namespace joystick
{
namespace sdljoystick
{
	int _wrap_getNumJoysticks(lua_State * L);
	int _wrap_getName(lua_State * L);
	int _wrap_open(lua_State * L);
	int _wrap_isOpen(lua_State * L);
	int _wrap_getNumAxes(lua_State * L);
	int _wrap_getNumBalls(lua_State * L);
	int _wrap_getNumButtons(lua_State * L);
	int _wrap_getNumHats(lua_State * L);
	int _wrap_getAxis(lua_State * L);
	int _wrap_getAxes(lua_State * L);
	int _wrap_getBall(lua_State * L);
	int _wrap_isDown(lua_State * L);
	int _wrap_getHat(lua_State * L);
	int _wrap_close(lua_State * L);
	int wrap_Joystick_open(lua_State * L);

} // sdljoystick
} // joystick
} // love

#endif // LOVE_JOYSTICK_SDLJOYSTICK_WRAP_JOYSTICK_H
