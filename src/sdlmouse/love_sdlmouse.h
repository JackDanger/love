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
	
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC module_init(int argc, char ** argv, love::Core * core);
		bool DECLSPEC module_quit();
		bool DECLSPEC module_open(void * vm);
	}

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


} // love_sdlmouse

#endif // LOVE_MOD_SDLMOUSE_H
