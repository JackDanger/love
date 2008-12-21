/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#include "Sound.h"

namespace love
{
namespace openal
{
	Sound::Sound(SoundData * data)
	{
		int decoded = data->decodeAll();
		
		// Generate the buffer.
		alGenBuffers(1, &buffer);

		alBufferData(buffer, AL_FORMAT_STEREO16, data->getData(), 
			data->getSize(), 44100);

		// Note: we're done with the sound data
		// at this point.
	}

	Sound::~Sound()
	{
	}

	void Sound::init(ALuint source)
	{
		// Set the buffer for the sound.
		alSourcei(source, AL_BUFFER, buffer);
	}

	void Sound::update(ALuint source)
	{
		// No need.
	}

} // openal
} // love