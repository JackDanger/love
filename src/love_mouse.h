#ifndef LOVE_MOUSE_GLOBALS_H
#define LOVE_MOUSE_GLOBALS_H

/**  
* @file love_mouse.h
* @brief Contains mouse related globals.
* @date 2006-12-01
* @author Anders Ruud
**/    

namespace love  
{    

	enum 
	{
		LOVE_MOUSE_LEFT = 1,
		LOVE_MOUSE_MIDDLE = 2,
		LOVE_MOUSE_RIGHT = 4,
		LOVE_MOUSE_WHEELUP = 8,
		LOVE_MOUSE_WHEELDOWN = 16
	};

} // love

#endif
