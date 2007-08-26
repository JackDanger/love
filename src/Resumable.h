/**
* @file Resumable.h
* @author Anders Ruud
* @date 2007-02-02
* @brief Contains definition for class Resumable.
**/

#ifndef LOVE_RESUMABLE_H
#define LOVE_RESUMABLE_H

// LOVE

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Resumable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-02-02
	* @brief 
	**/
	class Resumable
	{
	private:

	public:

		/**
		* @brief Contructs an empty Resumable.
		**/
		Resumable();
		virtual ~Resumable();

		/**
		* @brief Called when something is suspended.
		**/
		virtual void suspend() = 0;

		/**
		* @brief Called when something is resumed.
		**/
		virtual void resume() = 0;

	};

	typedef boost::shared_ptr<Resumable> pResumable;

} // love

#endif

