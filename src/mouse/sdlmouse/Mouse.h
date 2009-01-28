/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Mouse module using the SDL's input abstraction.
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_MOUSE_SDLMOUSE_MOUSE_H
#define LOVE_MOUSE_SDLMOUSE_MOUSE_H

// LOVE
#include "../../luax.h"

namespace love
{
namespace mouse
{
namespace sdlmouse
{
	class Mouse
	{
	private:
		static Mouse * _instance;
	protected:
		Mouse();
	public:

		static Mouse * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		int getX() const;
		int getY() const;
		void getPosition(int * x, int * y) const;
		void setPosition(int x, int y);
		void setVisible(bool visible);
		bool isDown(int button) const;
		bool isVisible() const;

	}; // Mouse

} // sdlmouse
} // mouse
} // love

#endif // LOVE_MOUSE_SDLMOUSE_MOUSE_H