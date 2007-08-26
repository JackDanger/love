#include "Window.h"

namespace love
{

	Window::Window() : width(1024), height(768), fullscreen(false)
	{
		setType(LOVE_TYPE_WINDOW);
	}

	Window::Window(int width, int height, bool fullscreen) : width(width), height(height), fullscreen(fullscreen)
	{
		setType(LOVE_TYPE_WINDOW);
	}

	Window::~Window()
	{
	}

	int Window::getWidth() const
	{
		return width;
	}

	int Window::getHeight() const
	{
		return height;
	}

	bool Window::isFullscreen() const
	{
		return fullscreen;
	}


}// love