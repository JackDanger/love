/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_AUDIO_OPENAL_AUDIBLE_H
#define LOVE_AUDIO_OPENAL_AUDIBLE_H

// LOVE
#include "../../Object.h"

// OpenAL
#include <alut.h>

namespace love
{
namespace audio
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
		virtual void rewind(ALuint source) = 0;
	}; // Audible

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_AUDIBLE_H