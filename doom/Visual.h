#ifndef LOVE_VISUAL_H
#define LOVE_VISUAL_H



// LOVE
#include "AbstractEntity.h"


// boost
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace love
{

	/**
	* @class Visual
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-08
	* @brief Superclass of Image and all Animations.
	**/
	class Visual : public AbstractEntity
	{
	private:
	public:
	};

}// LOVE

#endif