/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SYSTEM_H
#define LOVE_SYSTEM_H

// LOVE
#include "Module.h"

namespace love
{

	/**
	* System module interface.
	* @author Anders Ruud
	* @date 2008-04-08
	**/
	class System : public Module
	{
	public:

		// From Module.
		bool extra(const std::string & so);
	};
}

#endif // LOVE_SYSTEM_H
