/**
* @file Resource.h
* @author Anders Ruud
* @date 2007-08-18
* @brief Contains definition for class Resource.
**/

#ifndef LOVE_RESOURCE_H
#define LOVE_RESOURCE_H

// LOVE

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	// Forward declarations.
	class AbstractFile;

	/**
	* @class Resource
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-18
	* @brief A resource is something which is loaded from a file.
	**/
	class Resource
	{
	protected:

		// file
		AbstractFile * file;

	public:

		/**
		* @brief Contructs an empty Resource.
		**/
		Resource(AbstractFile * file);

		/**
		* @brief Destructor.
		**/
		virtual ~Resource();

	};

	typedef boost::shared_ptr<Resource> pResource;

} // love

#endif

