/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_PHYSICS_H
#define LOVE_PHYSICS_H

// LOVE
#include "Module.h"

namespace love
{

	/**
	* Physics module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Physics : public Module
	{
	public:

		// From Module.
		bool extra(const std::string & so);
	};
}

#endif // LOVE_PHYSICS_H
