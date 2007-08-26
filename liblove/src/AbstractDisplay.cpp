#include "AbstractDisplay.h"
#include "love.h"

namespace love
{

	AbstractDisplay::AbstractDisplay() : listener(0)
	{
	}

	AbstractDisplay::~AbstractDisplay()
	{
	}

	const DisplayMode & AbstractDisplay::getCurrentDisplayMode() const
	{
		return currentDisplayMode;
	}

	int AbstractDisplay::toggleVSync()
	{
		DisplayMode dm = currentDisplayMode;
		dm.vsync = !dm.vsync;
		return tryChange(dm);
	}

	int AbstractDisplay::toggleFullscreen()
	{
		DisplayMode dm = currentDisplayMode;
		dm.fullscreen = !dm.fullscreen;
		return tryChange(dm);
	}

	int AbstractDisplay::tryResize(DisplayMode displayMode)
	{
		DisplayMode dm = currentDisplayMode;
		dm.width = displayMode.width;
		dm.height = displayMode.height;
		dm.fullscreen = currentDisplayMode.fullscreen;
		dm.vsync = currentDisplayMode.vsync;
		currentDisplayMode.fsaa = currentDisplayMode.fsaa;
		return tryChange(dm);
	}


}// love
