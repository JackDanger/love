/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

#ifndef LOVE_MOUSE_SDL_MOUSE_H
#define LOVE_MOUSE_SDL_MOUSE_H

// LOVE
#include "../../Module.h"
#include "../../luax.h"

namespace love
{
namespace mouse
{
namespace sdl
{
	class Mouse : public Module
	{
	private:
		static Mouse * instance;
	protected:
		Mouse();
	public:

		static Mouse * getInstance();

		// Implements Module.
		int init(lua_State * L);
		int quit(lua_State * L);
		const char * getName() const;
		
		int getX() const;
		int getY() const;
		void getPosition(int * x, int * y) const;
		void setPosition(int x, int y);
		void setVisible(bool visible);
		bool isDown(int button) const;
		bool isVisible() const;

	}; // Mouse

} // sdl
} // mouse
} // love

#endif // LOVE_MOUSE_SDL_MOUSE_H