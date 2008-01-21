/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_DISPLAY_H
#define LOVE_DISPLAY_H

// LOVE
#include "Device.h"

// STL

namespace love
{
	// Forward declarations.
	class Graphics;

	/**
	* Represents a specific display mode.
	**/
	struct display_mode
	{
		int width, height; // The size of the screen.
		int color_depth; // The color depth of the display mode.
		bool fullscreen; // Fullscreen (true), or windowed (false).
		bool vsync; // Vsync enabled (true), or disabled (false).
		int fsaa; // 0 for no FSAA, otherwise 1, 2 or 4.
	};

	/**
	* Represents the abstract display device.
	*
	* @author Anders Ruud
	* @date 2007-08-17
	**/
	class Display : public Device
	{
	protected:

		// The current display mode.
		display_mode current;

	public:

		virtual ~Display();

		/**
		* Gets current display_mode.
		**/
		const display_mode & getCurrent() const;

		/**
		* Checks if a display mode is supported.
		* @param dm The display mode to check.
		* @return 0 if supported, -1 on total fail, or a number representing 
		* a supported color depth for the given resolution. (If any).
		**/ 
		virtual int isSupported(const display_mode & dm) = 0;

		/**
		* Tries to change the display mode.
		* @param dm The DisplayMode to change to.
		* @return 0 on success, -1 on total fail, or another number representing 
		* the amount of color bits we got.
		**/
		virtual int tryChange(const display_mode & dm) = 0;

		/**
		* Tries to change the display mode.
		* @param width Screen width.
		* @param height Screen height.
		* @param clr Color depth.
		* @param fullscreen Fullscreen or windowed. (True = fullscreen)
		* @param vsync Wait for vertical sync. (True = enabled)
		* @param fsaa Anti-aliasing. (1, 2, 4)
		**/
		int tryChange(int width, int height, int clr = 32, bool fullscreen = false, bool vsync = true, int fsaa = 0);

		/**
		* Changes the display resolution, but keeps all other settings.
		* @param displayMode The new display mode to set to. (Only dimensions will be used)
		* @return 0 on success.
		**/
		int tryResize(const display_mode & dm);

		/**
		* Toggles V-sync. Keeps all other settings.
		**/
		int toggleVSync();

		/**
		* Toggles fullscreen. Keeps all other settings. 
		**/
		int toggleFullscreen();

		/**
		* Gets a graphics context that is compatible with the current display.
		* A graphics context.
		**/
		virtual Graphics * getGraphics() const = 0;

		/**
		* Gets the width of the current display mode.
		**/
		int getWidth() const;

		/**
		* Gets the height of the current display mode.
		**/
		int getHeight() const;

	}; // Display

} // love

#endif // LOVE_DISPLAY_H


