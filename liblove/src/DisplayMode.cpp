#include "DisplayMode.h"
#include "love.h"
#include "Core.h"


namespace love
{

	DisplayMode::DisplayMode() : width(800), height(600), colorDepth(32), fullscreen(false), vsync(false), fsaa(0)
	{
		setType(LOVE_TYPE_DISPLAY_MODE);
	}

	DisplayMode::DisplayMode(int width, int height, int colorDepth, bool fullscreen, bool vsync, int fsaa)
		: width(width), height(height), colorDepth(colorDepth), fullscreen(fullscreen), vsync(vsync), fsaa(fsaa)
	{
		setType(LOVE_TYPE_DISPLAY_MODE);
	}

	DisplayMode::~DisplayMode()
	{
	}

	void DisplayMode::resize(int width, int height)
	{
		// Resize
		this->width = width;
		this->height = height;
	}

	int DisplayMode::getWidth() const
	{
		return width;
	}
	int DisplayMode::getHeight() const
	{
		return height;
	}

	int DisplayMode::getColorDepth() const
	{
		return colorDepth;
	}

	bool DisplayMode::isFullscreen() const
	{
		return fullscreen;
	}

	bool DisplayMode::isVsync() const
	{
		return vsync;
	}

	int DisplayMode::getFSAA() const
	{
		return fsaa;
	}

	bool DisplayMode::equals(const DisplayMode & displayMode) const
	{
		return	this->width == displayMode.getWidth() && this->height == displayMode.getHeight();
	}

}// love
