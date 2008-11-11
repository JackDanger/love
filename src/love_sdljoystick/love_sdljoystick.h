/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_MODULE_SDLJOYSTICK_H
#define LOVE_MODULE_SDLJOYSTICK_H

// LOVE
#include "../liblove/luax.h"

namespace love
{
namespace sdljoystick
{
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

	/**
	* Gets whether the passed index is valid and if not prints out an error.
	**/
	bool checkJoystickIndex(int index);

	/**
	* Gets the amount of joysticks that are connected to the computer.
	**/
	int getNumJoysticks();

	/**
	* Gets the name of a joystick based on its index.
	* @param index The index of the desired joystick.
	**/
	const char * getName(int index);

	/**
	* Opens a joystick for callback monitoring.
	* @param index The index of the desired joystick.
	**/
	bool open(int index);

	/**
	* Checks whether a joystick is open for input reading.
	* @param index The index of the desired joystick.
	**/
	bool isOpen(int index);

	/**
	* Gets the amount of axes available on the desired joystick.
	* @param index The index of the desired joystick.
	**/
	int getNumAxes(int index);

	/**
	* Gets the amount of trackballs available on the desired joystick.
	* @param index The index of the desired joystick.
	**/
	int getNumBalls(int index);

	/**
	* Gets the amount of buttons available on the desired joystick.
	* @param index The index of the desired joystick.
	**/
	int getNumButtons(int index);

	/**
	* Gets the amount of viewhats available on the desired joystick.
	* @param index The index of the desired joystick.
	**/
	int getNumHats(int index);

	/**
	* Gets the status of an axis available on the desired joystick.
	* @param index The index of the desired joystick.
	* @param axis The index of the desired axis.
	**/
	float getAxis(int index, int axis);

	/**
	* Gets the status of all the axes on the joystick.
	* @param index The index of the desired joystick.
	**/
	int getAxes(lua_State * L);

	/**
	* Gets the relative axis status of a trackball available on the desired joystick 
	* (since last call of this function).
	* @param index The index of the desired joystick.
	* @param ball The index of the desired trackball.
	**/
	int getBall(lua_State * L);

	/**
	* Gets the status of an button available on the desired joystick.
	* @param index The index of the desired joystick.
	* @param button The index of the desired button.
	**/
	bool isDown(int index, int button);

	/**
	* Gets the status of an viewhat available on the desired joystick.
	* @param index The index of the desired joystick.
	* @param hat The index of the desired hat.
	**/
	int getHat(int index, int hat);

	/**
	* Closes a joystick, so that no events are fired from that joystick.
	* @param index The index of the desired joystick.
	**/
	void close(int index);

} // sdljoystick
} // love

#endif // LOVE_MODULE_SDLJOYSTICK_H
