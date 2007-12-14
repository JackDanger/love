#include "Display.h"

using std::vector;

namespace love
{

	Display::Display()
	{
	}

	Display::~Display()
	{
	}

	const vector<pDisplayMode> & Display::getDisplayModes() const
	{
		return displayModes;
	}

	const pDisplayMode & Display::getCurrentDisplayMode() const
	{
		return currentDisplayMode;
	}

	void Display::setCurrentDisplayMode(pDisplayMode currentDisplayMode)
	{
		this->currentDisplayMode = currentDisplayMode;
	}


	void Display::queueMode(pDisplayMode displayMode)
	{
		displayModes.push_back(displayMode);
	}

	void Display::queueMode(int width, int height, int colorDepth, bool fullscreen, bool vsync)
	{
		pDisplayMode pdm(new DisplayMode(width, height, colorDepth, fullscreen, vsync));
		displayModes.push_back(pdm);
	}

	int Display::getWidth() const
	{
		return currentDisplayMode->getWidth();
	}

	int Display::getHeight() const
	{
		return currentDisplayMode->getHeight();
	}

	int Display::getColorDepth() const
	{
		return currentDisplayMode->getColorDepth();
	}

	bool Display::isFullscreen() const
	{
		return currentDisplayMode->isFullscreen();
	}

}// love
