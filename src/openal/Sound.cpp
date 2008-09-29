#include "Sound.h"

namespace love_openal
{

	Sound::Sound(love::pFile file)
		: love::Resource(file)
	{

		static const ALfloat origo[] = {0,0,0};

		buffer = alutCreateBufferHelloWorld();

		if( ALUT_ERROR_NO_ERROR == alutGetError() )
			printf("No error so far.\n");

		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
		alSourcei(source, AL_LOOPING, AL_TRUE);
    	alSourcef(source, AL_PITCH, 1.0f);
    	alSourcef(source, AL_GAIN, 1.0f);
    	alSourcefv(source, AL_POSITION, origo);
    	alSourcefv(source, AL_VELOCITY, origo);

		if( ALUT_ERROR_NO_ERROR == alGetError() )
			printf("No error so far.\n");

	}

	Sound::~Sound()
	{
		alDeleteSources(1, &source);
	}

	bool Sound::load()
	{
		return true;
	}

	void Sound::unload()
	{
	}

	void Sound::play()
	{
		alSourcePlay(source);
				if( ALUT_ERROR_NO_ERROR == alGetError() )
			printf("No error so far.\n");
	}

	void Sound::pause()
	{
	}

	void Sound::stop()
	{
	}

	void Sound::rewind()
	{
	}

	void Sound::seek(float pos)
	{
	}

	bool Sound::isPlaying() const
	{
		return true;
	}

	bool Sound::isPaused() const
	{
		return true;
	}

	bool Sound::isStopped() const
	{
		return true;
	}

	void Sound::setLooping(bool looping)
	{
	}

	bool Sound::isLooping() const
	{
		return true;
	}

	void Sound::setVolume(float volume)
	{
	}

	float Sound::getVolume() const
	{
		return 1.0f;
	}

	void Sound::setPitch()
	{
	}

	float Sound::getPitch() const
	{
		return 1.0f;
	}

	void Sound::setRelative(bool relative)
	{
	}

	bool Sound::isRelative() const
	{
		return true;
	}

	void Sound::setPosition(float x, float y, float z)
	{
	}

	int Sound::getPosition(lua_State * L)
	{
		return 0;
	}

	// TODO: Check which way z is.
	void Sound::setDirection(float x, float y, float z)
	{
	}

	int Sound::getDirection(lua_State * L)
	{
		return 0;
	}

	void Sound::setVelocity(float x, float y, float z)
	{
	}

	int Sound::getVelocity(lua_State * L)
	{
		return 0;
	}

	void Sound::setMinDistance(float min)
	{
	}

	float Sound::getMinDistance() const
	{
		return 1.0f;
	}

	void Sound::setMaxDistance(float max)
	{
	}

	float Sound::getMaxDistance() const
	{
		return 1.0f;
	}

	void Sound::setMinVolume(float volume)
	{
	}

	float Sound::getMinVolume() const
	{
		return 1.0f;
	}

	void Sound::setMaxVolume(float volume)
	{
	}

	float Sound::getMaxVolume() const
	{
		return 1.0f;
	}

} // love_openal
