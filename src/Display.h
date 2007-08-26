/**
* @file Display.h
* @author Anders Ruud
* @date 2007-02-04
* @brief Contains definition for class Display.
**/

#ifndef LOVE_DISPLAY_H
#define LOVE_DISPLAY_H

// LOVE
#include "Object.h"
#include "DisplayMode.h"

// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

using std::vector;

namespace love
{

	/**
	* @class Display
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-02-04
	* @brief 
	**/
	class Display
	{
	private:

		// displayModes
		vector<pDisplayMode> displayModes;

		// currentDisplayMode
		pDisplayMode currentDisplayMode;

	public:

		/**
		* @brief Contructs an empty Display.
		**/
		Display();
		virtual ~Display();

		/**
		* @brief Gets displayModes.
		* @return displayModes.
		**/
		const vector<pDisplayMode> & getDisplayModes() const;

		/**
		* @brief Gets currentDisplayMode.
		* @return currentDisplayMode.
		**/
		const pDisplayMode & getCurrentDisplayMode() const;

		/**
		* @brief Sets currentDisplayMode.
		* @param currentDisplayMode 
		**/
		void setCurrentDisplayMode(pDisplayMode currentDisplayMode);

		void queueMode(pDisplayMode displayMode);
		void queueMode(int width, int height, int colorDepth, bool fullscreen, bool vsync = false);

		int getWidth() const;
		int getHeight() const;
		int getColorDepth() const;
		bool isFullscreen() const;

	};

	typedef boost::shared_ptr<Display> pDisplay;

} // love

#endif

