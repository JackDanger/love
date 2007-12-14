/**
* @file Event.h
* @author Anders Ruud
* @date 2006-11-21
* @brief Contains definition for class Event.
**/

#ifndef LOVE_EVENT_H
#define LOVE_EVENT_H

// LOVE
#include "Object.h"

// STL
//#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Event
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-21
	* @brief 
	**/
	class Event : public Object
	{
	private:

		// type
		int type;

	public:

		/**
		* @brief Contructs an empty Event.
		**/
		Event();
		virtual ~Event();

		/**
		* @brief Gets type.
		* @return type.
		**/
		int getType() const;

		/**
		* @brief Sets type.
		* @param type 
		**/
		void setType(int type);

	};

	typedef boost::shared_ptr<Event> pEvent;

} // love

#endif
