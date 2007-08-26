/**
* @file DisplayModeListener.h
* @author Anders Ruud
* @date 2007-02-04
* @brief Contains definition for class DisplayModeListener.
**/

#ifndef LOVE_DISPLAYMODELISTENER_H
#define LOVE_DISPLAYMODELISTENER_H

// LOVE

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class DisplayModeListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-02-04
	* @brief This class keeps track of changes in the DisplayMode.
	* This is useful for knowing when the user changes the display mode.
	* (Which again is useful for reloading the destroyed OpenGL context)
	**/
	class DisplayModeListener
	{
	private:

		// The number of times the display mode has been changed since
		// last reset.
		int num;

	public:

		/**
		* @brief Contructs an empty DisplayModeListener.
		**/
		DisplayModeListener();

		/**
		* @brief Destructor.
		**/
		virtual ~DisplayModeListener();

		/**
		* @brief Should be called when the display mode is changed.
		**/
		virtual void displayModeChanged();

		/**
		* @brief Checks if the display mode has changed since last reset.
		* @return True if display mode has changed, false otherwise.
		**/
		bool isDisplayModeChanged() const;
		
		/**
		* @brief Gets the amount of display mode changes since last reset.
		* @return The number of display mode changes.
		**/
		int getDisplayModeChangedNum() const;

		/**
		* @brief Sets the display mode listener counter to 0.
		**/
		void resetDisplayModeListener();

	};

	typedef boost::shared_ptr<DisplayModeListener> pDisplayModeListener;

} // love

#endif

