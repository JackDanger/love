/**
* @file DisplayMode.h
* @author Anders Ruud
* @date 2007-02-02
* @brief Contains definition for class DisplayMode.
**/

#ifndef LOVE_DISPLAYMODE_H
#define LOVE_DISPLAYMODE_H

// LOVE
#include "Object.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class DisplayMode
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-02-02
	* @brief 
	**/
	class DisplayMode : public Object
	{
	private:

		friend class AbstractDisplay;

		// width
		int width;

		// height
		int height;

		// colorDepth
		int colorDepth;

		// fullscreen
		bool fullscreen;

		// Wait for vertical refresh
		bool vsync;

		// Anti-aliasing
		int fsaa;

	public:

		/**
		* @brief Creates fullscreen 800x600x32
		**/
		DisplayMode();

		/**
		* @brief Creates a new display mode.
		**/
		DisplayMode(int width, int height, int colorDepth = 32, bool fullscreen = true, bool vsync = false, int fsaa = 0);

		/**
		* @brief Destructor.
		**/
		virtual ~DisplayMode();

		/**
		* @brief Rezises the display mode, using existing settings for everything except resolution.
		* @param width The width of the new display mode.
		* @param height The height of the new display mode.
		**/ 
		void resize(int width, int height);

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
		* @brief Gets colorDepth.
		* @return colorDepth.
		**/
		int getColorDepth() const;

		/**
		* @brief Gets fullscreen.
		* @return fullscreen.
		**/
		bool isFullscreen() const;

		/**
		* @brief Gets wether or not the DisplayMode should wait for veritcal refresh.
		* @return True if waiting for vert refresh, false otherwise.
		**/
		bool isVsync() const;

		/**
		* @brief Gets the amount of FSAA multisamples.
		* @return The amount of FSAA multisamples.
		**/
		int getFSAA() const;

		bool equals(const DisplayMode & displayMode) const;

	};

	typedef boost::shared_ptr<DisplayMode> pDisplayMode;

} // love

#endif

