/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* An interface to add gamepad devices via SDL.
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
	bool checkIndex(int index);

	/**
	* Gets the amount of gamepads that are connected to the computer.
	**/
	int getNumGamepads();

	/**
	* Gets the name of a gamepad based on its index.
	* @param index The index of the desired gamepad.
	**/
	const char * getName(int index);

	/**
	* Opens a gamepad for callback monitoring.
	* @param index The index of the desired gamepad.
	**/
	void open(int index);

	/**
	* Checks whether a gamepad is open for input reading.
	* @param index The index of the desired gamepad.
	**/
	bool isOpen(int index);

	/**
	* Gets the amount of axes available on the desired gamepad.
	* @param index The index of the desired gamepad.
	**/
	int getNumAxes(int index);

	/**
	* Gets the amount of trackballs available on the desired gamepad.
	* @param index The index of the desired gamepad.
	**/
	int getNumBalls(int index);

	/**
	* Gets the amount of buttons available on the desired gamepad.
	* @param index The index of the desired gamepad.
	**/
	int getNumButtons(int index);

	/**
	* Gets the amount of viewhats available on the desired gamepad.
	* @param index The index of the desired gamepad.
	**/
	int getNumHats(int index);

	/**
	* Gets the status of an axis available on the desired gamepad.
	* @param index The index of the desired gamepad.
	* @param axis The index of the desired axis.
	**/
	int getAxis(int index, int axis);

	/**
	* Gets the relative x-axis status of a trackball available on the desired gamepad (since last call of this function).
	* @param index The index of the desired gamepad.
	* @param ball The index of the desired trackball.
	**/
	int getBallX(int index, int ball);

	/**
	* Gets the relative y-axis status of a trackball available on the desired gamepad (since last call of this function).
	* @param index The index of the desired gamepad.
	* @param ball The index of the desired trackball.
	**/
	int getBallY(int index, int ball);

	/**
	* Gets the status of an button available on the desired gamepad.
	* @param index The index of the desired gamepad.
	* @param button The index of the desired button.
	**/
	int getButton(int index, int button);

	/**
	* Gets the status of an viewhat available on the desired gamepad.
	* @param index The index of the desired gamepad.
	* @param hat The index of the desired hat.
	**/
	int getHat(int index, int hat);

	/**
	* Closes a gamepad, so that no events are fired from that gamepad.
	* @param index The index of the desired gamepad.
	**/
	void close(int index);

} // love_sdljoystick

#endif // LOVE_MOD_SDLJOYSTICK_H
