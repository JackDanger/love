/**
* @file Updateable.h
* @brief Contains definition of class Updateable.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_UPDATEABLE_H
#define LOVE_UPDATEABLE_H

namespace love
{

	/**
	* @class Updateable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-01-15
	* @brief Superclass for all objects in the engine that constantly 
	* needs to change state.
	**/
	class Updateable
	{
	private:
	public:
		
		Updateable();
		virtual ~Updateable();

		/**
		* @brief Updates the state of the object.
		* @param dt The time since last frame. 
		*
		* Remember to call this function ever frame for each 
		* updatable object.
		**/
		virtual void update(float dt) = 0; 
	};

}// love

#endif
