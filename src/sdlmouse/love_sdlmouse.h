/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This is a small interface to the mouse device
* via SDL.
* 
* @author Anders Ruud
* @date 2008-03-16
*/

#ifndef LOVE_MOD_SDLMOUSE_H
#define LOVE_MOD_SDLMOUSE_H

// LOVE
#include <love/mod.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_sdlmouse
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	/**
	* Gets current mouse position on x-axis.
	**/
	float getX();

	/**
	* Gets current mouse position on x-axis.
	**/
	float getY();

	/**
	* Sets the mouse position.
	**/
	void setPosition(float x, float y);

	/**
	* Checks if a mouse button is pressed.
	**/
	bool isDown(int button);

	/**
	* Changes cursor visibility.
	* @param visible True = visible, false = invisible.
	**/
	void setVisible(bool visible);

	/**
	* Returns true if the mouse is visible, false otherwise.
	**/
	bool isVisible();

	/**
	* Native function with two return values (x,y). The same
	* can be achieved with separate calls to getX() and getY(), 
	* but getting the mouse position is common, and this
	* will make the process prettier.
	* Does not take any parameters, and returns two numbers.
	**/
	int getPosition(lua_State * L);


} // love_sdlmouse

#endif // LOVE_MOD_SDLMOUSE_H
