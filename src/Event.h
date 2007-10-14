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

// string
#include <string>
using std::string;

// STL

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
		string name;

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
		 * @brief Gets the name.
		 * @return Name.
		 **/
		string getName() const;

		/**
		* @brief Sets type.
		* @param type 
		**/
		void setType(int type);

		/**
		 * @brief Sets the name.
		 * @param name Name of the event.
		 **/
		void setName(string name);

	};

	typedef boost::shared_ptr<Event> pEvent;

} // love

#endif
