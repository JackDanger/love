/**
* @file DevILImageDevice.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class DevILImageDevice.
**/

#ifndef LOVE_DEVILIMAGEDEVICE_H 
#define LOVE_DEVILIMAGEDEVICE_H 

// LOVE
#include "AbstractImageDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class DevILImageDevice
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class DevILImageDevice : public AbstractImageDevice
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty DevILImageDevice.
		**/
		DevILImageDevice();
		
		/**
		* @brief Destructor.
		**/
		virtual ~DevILImageDevice();

		/**
		* @brief Inits the image device.
		* @return LOVE_OK if no errors.
		**/
		int init();

		/**
		* @brief Gets an image that is compatible with the current image device.
		* @param file The file to create the image from.
		**/
		AbstractImage * getImage(AbstractFile * file) const;
		
	}; // DevILImageDevice
	
	typedef boost::shared_ptr<DevILImageDevice> pDevILImageDevice;
	
} // love

#endif
