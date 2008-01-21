/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_DEVICE_H
#define LOVE_DEVICE_H

// LOVE

// STL

namespace love
{

	/**
	* The superclass of all devices. 
	*
	* @author Anders Ruud
	* @date 2007-08-17
	**/
	class Device
	{
	private:
	public:

		virtual ~Device();

		/**
		* Inits the device. May or may not use the command line
		* parameters. True on success, false on error.
		**/
		virtual bool init(int argc, char* argv[]) = 0;

		/**
		* Should free any resources init allocates. Automatically called when 
		* device is deleted.
		**/
		virtual void quit() = 0;

	}; // Device

} // love

#endif // LOVE_DEVICE_H
