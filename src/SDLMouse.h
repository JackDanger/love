/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDL_MOUSE_H
#define LOVE_SDL_MOUSE_H

// LOVE
#include "Mouse.h"

namespace love
{

	/**
	* SDL Mouse implementation.
	*
	* @author Anders Ruud
	* @date 2006-12-01
	**/
	class SDLMouse : public Mouse
	{
	protected:
	public:

		virtual ~SDLMouse();

		// From Device.
		bool init(int argc, char* argv[]);
		void quit();

		// From Mouse.
		float getX() const;
		float getY() const;
		bool isDown(int button) const;
		void setVisible(bool visible);
		bool isVisible() const;

	}; // SDLMouse

} // love

#endif // LOVE_SDL_MOUSE_H
