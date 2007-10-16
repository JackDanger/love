/**
* @file love_globals.h
* @author Anders Ruud
* @date 2006-11-21
* @brief Contains all (?) globals.
**/

#ifndef LOVE_GLOBALS_H
#define LOVE_GLOBALS_H

namespace love
{

	enum
	{
		LOVE_GL_VERSION_1_2 = 1,
		LOVE_GL_VERSION_1_3, 
		LOVE_GL_VERSION_1_4,
		LOVE_GL_VERSION_1_5,
		LOVE_GL_VERSION_2_0
	};

	enum
	{
		LOVE_METHOD_LOAD			= 0x1,
		LOVE_METHOD_UPDATE			= 0x2, 
		LOVE_METHOD_RENDER			= 0x4,
		LOVE_METHOD_KEYPRESSED		= 0x8,
		LOVE_METHOD_KEYRELEASED		= 0x10,
		LOVE_METHOD_MOUSEPRESSED	= 0x20,
		LOVE_METHOD_MOUSERELEASED	= 0x40,
		LOVE_METHOD_EVENT			= 0x80,
		LOVE_METHOD_ALL				= 0xFF
	};
	

} // love

#endif
