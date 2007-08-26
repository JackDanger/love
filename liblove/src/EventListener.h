/**
* @file EventListener.h
* @brief
* @date 2006-04-01
* @author Anders Ruud
**/

#ifndef LOVE_EVENT_LISTENER_H
#define LOVE_EVENT_LISTENER_H

// LOVE
#include "Listener.h"
#include "Event.h"

namespace love
{

	/**
	* @class EventListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-08-25
	* @brief An interface which provides the ability to catch Events.
	* @see Event
	**/
	class EventListener : public Listener
	{

	private:
	public:
		
		/**
		* @brief This is called every time an Event "happens".
		* @param e The Event that was just fired.
		**/
		virtual void eventFired(pEvent e) = 0;

	};

}// love

#endif
