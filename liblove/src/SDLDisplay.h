/**
* @file SDLDisplay.h
* @author Anders Ruud
* @date 2007-08-17
* @brief Contains definition for class SDLDisplay.
**/

#ifndef LOVE_SDL_DISPLAY_H
#define LOVE_SDL_DISPLAY_H

// LOVE
#include "AbstractDisplay.h"
#include "DisplayMode.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

// SDL
#include "SDL.h"

namespace love
{

	/**
	* @class SDLDisplay
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-17
	* @brief 
	**/
	class SDLDisplay : public AbstractDisplay
	{
	private:

		// Contains SDL's information about the display device.
		const SDL_VideoInfo * video;

	public:

		/**
		* @brief Contructs an empty SDLDisplay.
		**/
		SDLDisplay();
		virtual ~SDLDisplay();

		/**
		* @brief Inits the Display.
		* @return LOVE_OK if no errors.
		**/
		virtual int init();

		/**
		* @brief Checks if a display mode is supported.
		* @param displayMode The DisplayMode to check.
		* @returns 0 if supported, -1 on total fail, or a number representing 
		* a supported color depth for the given resolution. (If any)
		**/ 
		virtual int isSupported(DisplayMode displayMode);

		/**
		* @brief Tries to change the display mode.
		* @param displayMode The DisplayMode to change to.
		* @return 0 if success, -1 on total fail, or another number representing 
		* the amount of color bits we got.
		**/
		virtual int tryChange(DisplayMode displayMode);

		/**
		* @brief Generates a caption for the window.
		* @return The caption for the window.
		**/
		std::string makeCaption() const;


	};

	typedef boost::shared_ptr<SDLDisplay> pSDLDisplay;

} // love

#endif

