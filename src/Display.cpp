#include "Display.h"

namespace love
{
	
	Display::~Display()
	{
	}

	const display_mode & Display::getCurrent() const
	{
		return current;
	}

	int Display::toggleVSync()
	{
		display_mode d = current;
		d.vsync = !current.vsync;
		return tryChange(d);
	}

	int Display::toggleFullscreen()
	{
		display_mode d = current;
		d.fullscreen = !current.fullscreen;
		return tryChange(d);
	}

	int Display::tryChange(int width, int height, int clr, bool fullscreen, bool vsync, int fsaa)
	{
		display_mode dm;
		dm.width = width;
		dm.height = height;
		dm.color_depth = clr;
		dm.fullscreen = fullscreen;
		dm.vsync = vsync;
		dm.fsaa = fsaa;
		return tryChange(dm);
	}

	int Display::tryResize(const display_mode & dm)
	{
		display_mode d = current;
		d.width = dm.width;
		d.height = dm.height;
		d.fullscreen = current.fullscreen;
		d.vsync = current.vsync;
		d.fsaa = current.fsaa;
		return tryChange(d);
	}

	int Display::getWidth() const
	{
		return current.width;
	}

	int Display::getHeight() const
	{
		return current.height;
	}


}// love
