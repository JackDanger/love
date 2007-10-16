/**
* @file MessageEvent.h
* @author Anders Ruud
* @date 2006-11-21
* @brief Contains definition for class MessageEvent.
**/

#ifndef LOVE_MESSAGEEVENT_H
#define LOVE_MESSAGEEVENT_H

// LOVE
#include "Event.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{

	/**
	* @class MessageEvent
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-21
	* @brief 
	**/
	class MessageEvent : public Event
	{
	private:

		// message
		string message;

	public:

		/**
		* @brief Contructs an empty MessageEvent.
		**/
		MessageEvent();

		MessageEvent(string message);

		virtual ~MessageEvent();

		/**
		* @brief Gets message.
		* @return message.
		**/
		const char * getMessage() const;
	};

	typedef boost::shared_ptr<MessageEvent> pMessageEvent;

} // love

#endif
