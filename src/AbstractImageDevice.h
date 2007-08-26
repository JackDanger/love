/**
* @file AbstractImageDevice.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class AbstractImageDevice.
**/

#ifndef LOVE_ABSTRACTIMAGEDEVICE_H 
#define LOVE_ABSTRACTIMAGEDEVICE_H 

// LOVE
#include "AbstractDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class AbstractImage;
	class AbstractFile;

	/**
	* @class AbstractImageDevice
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class AbstractImageDevice : public AbstractDevice
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty AbstractImageDevice.
		**/
		AbstractImageDevice();
		
		/**
		* @brief Destructor.
		**/
		virtual ~AbstractImageDevice();

		/**
		* @brief Gets an image that is compatible with the current image device.
		* @param file The file to create the image from.
		**/
		virtual AbstractImage * getImage(AbstractFile * file) const = 0;
		
	}; // AbstractImageDevice
	
	typedef boost::shared_ptr<AbstractImageDevice> pAbstractImageDevice;
	
} // love

#endif
