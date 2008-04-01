/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MOUSE_H
#define LOVE_MOUSE_H

// LOVE
#include "Module.h"

namespace love
{

	/**
	* Mouse module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Mouse : public Module
	{
	public:

		// From Module.
		bool extra(const std::string & so);
	};
}

#endif // LOVE_AUDIO_H
