/**
* @file Listener.h
* @brief Contains definition of class Listener.
* @date 2006-03-12
* @author Anders Ruud
**/

#ifndef LOVE_LISTENER_H
#define LOVE_LISTENER_H

namespace love
{
	
	/**
	* @class Listener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-12
	* @brief Superclass for all listeners.
	**/
	class Listener
	{
	private:
		// Indicates whether the listening ojbect should respond to input
		bool active;
	public:
		Listener();
		virtual ~Listener();

		/**
		* @brief Indicates whether or not the listener
		* is currently active.
		* @return True if the listener is active, false 
		* otherwise.
		**/
		bool isActive();

		/**
		* @brief Enables/Disables input response.
		* @param active Whether listener should
		* respond to input.
		**/
		void setActive(bool active);
	};


}// love

#endif
