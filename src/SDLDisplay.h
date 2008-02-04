/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDL_DISPLAY_H
#define LOVE_SDL_DISPLAY_H

// LOVE
#include "Display.h"

// Forward declaring this.
struct SDL_VideoInfo;

namespace love
{

	// Forward declarations.
	class Graphics;

	/**
	* The SDL display device. For now, this also implies 
	* OpenGL rendering context.
	*
	* @author Anders Ruud
	* @date 2007-08-17
	**/
	class SDLDisplay : public Display
	{
	private:

		// Contains SDL's information about the display device.
		const SDL_VideoInfo * video;

	public:

		virtual ~SDLDisplay();

		// From Device.
		bool init(int argc, char* argv[]);
		void quit();

		// From Display.
		int isSupported(const display_mode & dm);
		int tryChange(const display_mode & dm);
		Graphics * newGraphics() const;
		void setTitle(const std::string & title) const;

	}; // SDLDisplay

} // love

#endif // LOVE_SDL_DISPLAY_H
