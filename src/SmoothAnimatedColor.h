/**
* @file SmoothAnimatedColor.h
* @author Anders Ruud
* @date 2007-05-22
* @brief Contains definition for class SmoothAnimatedColor.
**/

#ifndef LOVE_SMOOTHANIMATEDCOLOR_H
#define LOVE_SMOOTHANIMATEDCOLOR_H

// LOVE
#include "AnimatedColor.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class SmoothAnimatedColor
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-22
	* @brief 
	**/
	class SmoothAnimatedColor : public AnimatedColor
	{
	private:

	public:

		/**
		* @brief Contructs an empty SmoothAnimatedColor.
		**/
		SmoothAnimatedColor(Container<AbstractColor> * colors);
		virtual ~SmoothAnimatedColor();

		virtual float map(float t);

	};

	typedef boost::shared_ptr<SmoothAnimatedColor> pSmoothAnimatedColor;

} // love

#endif

