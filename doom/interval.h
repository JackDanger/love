#ifndef LOVE_INTERVAL_H
#define LOVE_INTERVAL_H

namespace love 
{

	// Boost
	#include <boost/shared_ptr.hpp>


		/**
		* @struct interval
		* @version 1.0
		* @since 1.0
		* @author Anders Ruud
		* @date 2006-02-07
		* @brief A collection of a min and max value.
		**/
		struct interval
		{
			float min;
			float max;
		};

		typedef boost::shared_ptr<interval> pinterval;

}//love
#endif