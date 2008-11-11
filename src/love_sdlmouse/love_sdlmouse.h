/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_MODULE_SDLMOUSE_H
#define LOVE_MODULE_SDLMOUSE_H

// LOVE
#include <love/luax.h>

namespace love
{
namespace sdlmouse
{
	int luainfo(lua_State * L);
	int luaopen(lua_State * L);
	int luagc(lua_State * L);

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

} // sdlmouse
} // love

#endif // LOVE_MODULE_SDLMOUSE_H
