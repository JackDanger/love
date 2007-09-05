/**
* @file Initializable.h
* @author Anders Ruud
* @date 2007-08-17
* @brief Contains definition for class Initializable.
**/

#ifndef LOVE_INITIALIZABLE_H
#define LOVE_INITIALIZABLE_H

// LOVE

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Initializable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-17
	* @brief 
	**/
	class Initializable
	{
	protected:

		// Whether init has been called.
		bool inited;

	public:

		/**
		* @brief Constructor. Sets inited to false.
		**/
		Initializable();
		
		virtual ~Initializable();
		
		/**
		* @brief Method should contain statements that initialize the object.
		* @return LOVE_OK if no errors. 
		**/ 
		virtual int init() = 0;

		/**
		* @brief Checks whether something is inited.
		* @return True if something is inited, false otherwise.
		**/
		bool isInited() const;

	};

	typedef boost::shared_ptr<Initializable> pInitializable;

} // love

#endif

