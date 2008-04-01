/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_AUDIO_H
#define LOVE_AUDIO_H

// LOVE
#include "Module.h"

namespace love
{

	/**
	* Audio module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Audio : public Module
	{
	public:

		// From Module.
		bool extra(const std::string & so);
	};
}

#endif // LOVE_AUDIO_H
