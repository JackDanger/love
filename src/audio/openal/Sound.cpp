/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

#include "Sound.h"

namespace love
{
namespace audio
{
namespace openal
{
	Sound::Sound(love::sound::SoundData * data)
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
		alDeleteBuffers(1, &buffer);
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

	void Sound::quit(ALuint source)
	{
		// Also no need.
	}

	void Sound::rewind(ALuint source)
	{
		alSourceRewind(source);
	}

} // openal
} // audio
} // love