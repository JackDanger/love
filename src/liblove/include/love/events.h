/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* This file contains definitions for a few
* custom events that we'll use through SDL.
* 
* @author Anders Ruud
* @date 2008-04-08
*/

#ifndef LOVE_EVENTS_H
#define LOVE_EVENTS_H

namespace love
{
	// Cleverly match these to SDL's user events
	enum
	{
		EVENT_RESTART = 24, // Restart the game.
		EVENT_SUSPEND = 25, // Suspend the game.
		EVENT_MAX = 32 // Just to remember that 32 = upper limit.
	};
} // love

#endif // LOVE_EVENTS_H
