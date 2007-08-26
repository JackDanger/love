/**
* @file Window.h
* @author 
* @date 2006-10-31
* @brief Contains definition for class Window.
**/

#ifndef LOVE_WINDOW_H
#define LOVE_WINDOW_H

// LOVE
#include "Object.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Window
	* @version 1.0
	* @since 1.0
	* @author 
	* @date 2006-10-31
	* @brief 
	**/
	class Window : public Object
	{
	private:

		// width
		int width;

		// height
		int height;

		// fullscreen
		bool fullscreen;

	public:

		/**
		* @brief Contructs a default empty Window.
		**/
		Window();

		/**
		* @brief Contructs a Window.
		* @param width The width of the Window.
		* @param height The height of the Window.
		* @param fullscreen Wether or not we should use fullscreen.
		**/
		Window(int width, int height, bool fullscreen);

		virtual ~Window();

		/**
		* @brief Gets width.
		* @return width.
		**/
		int getWidth() const;


		/**
		* @brief Gets height.
		* @return height.
		**/
		int getHeight() const;


		/**
		* @brief Gets fullscreen.
		* @return fullscreen.
		**/
		bool isFullscreen() const;


	};

	typedef boost::shared_ptr<Window> pWindow;

} // love

#endif
