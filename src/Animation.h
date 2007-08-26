/**
* @file Animation.h
* @brief Contains definition of class Animation.
* @date 2006-03-06
* @author Anders Ruud
**/

#ifndef LOVE_ANIMATION_H
#define LOVE_ANIMATION_H

#include "AbstractEntity.h"

namespace love
{

	/**
	* @class Animation
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-06
	* @brief Animation superclass. 
	*
	* Note that animations that are not frame-by-frame
	* also should inherit from this class.
	**/
	class Animation : public AbstractEntity
	{
		private:
		public:	
	};

	typedef boost::shared_ptr<Animation> pAnimation;

}// love

#endif
