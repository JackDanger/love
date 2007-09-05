#ifndef LOVE_H
#define LOVE_H

namespace love
{
	class Core;

	// The almighty global Core.
	extern Core * core;

	// LOVE version
	enum
	{
		LOVE_MAJOR_VERSION = 0, 
		LOVE_MINOR_VERSION = 2, 
		LOVE_REVISION = 229
	};

	enum 
	{
		LOVE_ERROR = 0,
		LOVE_OK = 1		
	};

	enum
	{
		LOVE_QUALITY_LOW = 0, 
		LOVE_QUALITY_MEDIUM = 2, 
		LOVE_QUALITY_HIGH = 4
	};

}

#endif

