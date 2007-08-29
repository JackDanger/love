/**
* @file AbstractDisplay.h
* @author Anders Ruud
* @date 2007-08-17
* @brief Contains definition for class AbstractDisplay.
**/

#ifndef LOVE_ABSTRACTDISPLAY_H
#define LOVE_ABSTRACTDISPLAY_H

// LOVE
#include "DisplayMode.h"
#include "AbstractDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class DisplayModeListener;
	class AbstractGraphics;

	/**
	* @class AbstractDisplay
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-17
	* @brief 
	**/
	class AbstractDisplay : public AbstractDevice
	{
	protected:

		// currentDisplayMode
		DisplayMode currentDisplayMode;

		// The listener to call when display mode changes.
		DisplayModeListener * listener;


	public:

		// Friends go here
		friend class Core;

		/**
		* @brief Contructs an empty AbstractDisplay.
		**/
		AbstractDisplay();
		virtual ~AbstractDisplay();

		/**
		* @brief Gets currentDisplayMode.
		* @return currentDisplayMode.
		**/
		const DisplayMode & getCurrentDisplayMode() const;

		/**
		* @brief Checks if a display mdoe is supported.
		* @param displayMode The DisplayMode to check.
		* @returns 0 if supported, -1 on total fail, or a number representing 
		* a supported color depth for the given resolution. (If any)
		**/ 
		virtual int isSupported(DisplayMode displayMode) = 0;

		/**
		* @brief Tries to change the display mode.
		* @param displayMode The DisplayMode to change to.
		* @return 0 if success, -1 on total fail, or another number representing 
		* the amount of color bits we got.
		**/
		virtual int tryChange(DisplayMode displayMode) = 0;


		/**
		* @brief Changes the display resolution, but keeps all other settings.
		* @param displayMode The new display mode to set to. (Only dimensions will be used)
		* @return LOVE_OK if no errors.
		**/
		int tryResize(DisplayMode displayMode);

		/**
		* @brief Toggles V-sync.
		* @return LOVE_OK if no errors.
		**/
		int toggleVSync();

		/**
		* @brief Toggles fullscreen. 
		* @return LOVE_OK if no errors.
		**/
		int toggleFullscreen();

		/**
		* @brief Gets a graphics context that is compatible with the current display.
		* @return A graphics context.
		**/
		virtual AbstractGraphics * getGraphics() const = 0;

		/**
		* @brief Gets the width of the current display mode.
		* @return The width of the current display mode.
		**/
		virtual int getWidth() const = 0;

		/**
		* @brief Gets the height of the current display mode.
		* @return The height of the current display mode.
		**/
		virtual int getHeight() const = 0;

	};

	typedef boost::shared_ptr<AbstractDisplay> pAbstractDisplay;

} // love

#endif

