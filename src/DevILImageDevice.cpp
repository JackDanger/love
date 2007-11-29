#include "DevILImageDevice.h"
#include "DevILImage.h"
#include "love.h"

namespace love
{
	
	DevILImageDevice::DevILImageDevice()
	{
	}
	
	DevILImageDevice::~DevILImageDevice()
	{
	}

	int DevILImageDevice::init()
	{

		return LOVE_OK;
	}

	AbstractImage * DevILImageDevice::getImage(AbstractFile * file) const
	{
		return new DevILImage(file);
	}

	
} // love
