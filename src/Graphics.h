/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/
#ifndef LOVE_GRAPHICS_H
#define LOVE_GRAPHICS_H

// LOVE
#include "Module.h"

namespace love
{
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

	// Function pointer typedefs.
	typedef int (*fptr_is_supported)(const display_mode &);
	typedef bool (*fptr_try_change)(const display_mode &);
	typedef bool (*fptr_toggleFullscreen)();
	typedef void (*fptr_print)(const char *);

	/**
	* Audio module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Graphics : public Module
	{
	public:

		// Pointers to functions.
		fptr_is_supported is_supported;
		fptr_try_change try_change;
		fptr_void clear;
		fptr_void present;
		fptr_void4f line;
		fptr_toggleFullscreen toggleFullscreen;
		fptr_void draw_console;
		fptr_print print;

		Graphics();

		// From Module.
		bool extra(const std::string & so);

	};
}

#endif
