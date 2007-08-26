/**
* @file AbstractDevice.h
* @author Anders Ruud
* @date 2007-08-17
* @brief Contains definition for class AbstractDevice.
**/

#ifndef LOVE_ABSTRACTDEVICE_H
#define LOVE_ABSTRACTDEVICE_H

// LOVE
#include "Object.h"
#include "Initializable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class Parameters;

	/**
	* @class AbstractDevice
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-17
	* @brief The superclass of all devices. Nothing here yetm but you never know.
	**/
	class AbstractDevice : public Object, public Initializable
	{
	private:

	public:

		/**
		* @brief Configure the device from input parameters.
		* @return LOVE_OK on success. 
		**/
		virtual int configure(Parameters * parameters);

	};

	typedef boost::shared_ptr<AbstractDevice> pAbstractDevice;

} // love

#endif

