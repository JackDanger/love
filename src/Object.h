/**
* @file Object.h
* @author Anders Ruud
* @date 2006-10-30
* @brief Contains definition for class Object.
**/

#ifndef LOVE_OBJECT_H
#define LOVE_OBJECT_H

// LOVE
#include "love_globals.h"
#include "love_types.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Object
	* @version 1.1
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-10-30
	* @brief Superclass of almost all classes is LÖVE.
	**/
	class Object
	{
	private:

		// We want name to be accessible from Container.
		template <class T>
		friend class Container;

		// Name of object. Should be same as index in some container.
		std::string name;

		// Type identifier
		int type;

	public:

		/**
		* @brief Contructs an empty Object.
		**/
		Object();
		virtual ~Object();

		/**
		* @brief Gets name.
		* @return name.
		**/
		const std::string & getName() const;

		/**
		* @brief Returns a textual representation of the Object.
		* @return A string describing the Object.
		* This is very useful for debug purposes, etc.
		**/
		virtual const std::string toString() const;

		/**
		* @brief Gets the type identifier for this Object.
		* @return The type identifier.
		**/
		int getType() const;

		/**
		* @brief Sets the type identifier for this Object.
		* @param type The new identifier.
		**/
		void setType(int type);

	};

	typedef boost::shared_ptr<Object> pObject;

} // love

#endif
