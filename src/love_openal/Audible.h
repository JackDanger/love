/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_OPENAL_AUDIBLE_H
#define LOVE_OPENAL_AUDIBLE_H

// LOVE
#include "../liblove/Object.h"

// OpenAL
#include <alut.h>

namespace love
{
namespace openal
{
	class Audible : public Object
	{
	public:
		virtual ~Audible();
		virtual void init(ALuint source) = 0;
		virtual void update(ALuint source) = 0;
		virtual void quit(ALuint source) = 0;
	}; // Audible

} // openal
} // love

#endif // LOVE_OPENAL_AUDIBLE_H