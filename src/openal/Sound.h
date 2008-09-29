/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENAL_SOUND_H 
#define LOVE_OPENAL_SOUND_H 

// LOVE
#include <love/luax.h>
#include <love/Resource.h>

// OpenAL
#include <AL/alut.h>

namespace love_openal
{
	/**
	* @author Anders Ruud
	* @date 2008-09-23
	**/
	class Sound : public love::Resource
	{
	private:

		ALuint buffer;
		ALuint source;

	public:
	
		/**
		* Creates a new sound from the given file.
		**/
		Sound(love::pFile file);
		virtual ~Sound();

		// From resource
		bool load();
		void unload();

		void play();
		void pause();
		void stop();

		void rewind();
		void seek(float pos);

		bool isPlaying() const;
		bool isPaused() const;
		bool isStopped() const;

		void setLooping(bool looping);
		bool isLooping() const;

		void setVolume(float volume);
		float getVolume() const;
		
		void setPitch();
		float getPitch() const;

		void setRelative(bool relative);
		bool isRelative() const;

		void setPosition(float x, float y, float z = 0.0f);
		int getPosition(lua_State * L);

		// TODO: Check which way z is.
		void setDirection(float x, float y, float z = 1.0f);
		int getDirection(lua_State * L);

		void setVelocity(float x, float y, float z = 0.0f);
		int getVelocity(lua_State * L);

		void setMinDistance(float min);
		float getMinDistance() const;

		void setMaxDistance(float max);
		float getMaxDistance() const;

		void setMinVolume(float volume);
		float getMinVolume() const;

		void setMaxVolume(float volume);
		float getMaxVolume() const;

	}; // Sound

	typedef boost::shared_ptr<Sound> pSound;
	
} // love_openal

#endif // LOVE_OPENAL_SOUND_H
