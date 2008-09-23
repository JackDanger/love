/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* An interface to add joystick devices via SDL.
* 
* @author Michael Enger
* @date 2008-08-01
*/
#ifndef LOVE_MOD_SDLJOYSTICK_H
#define LOVE_MOD_SDLJOYSTICK_H

// LOVE
#include <love/mod.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_sdljoystick
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

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
	void open(int index);

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

} // love_sdljoystick

#endif // LOVE_MOD_SDLJOYSTICK_H
