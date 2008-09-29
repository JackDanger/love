#include "love_openal.h"

// AL
#include <AL/alut.h>

namespace love_openal
{

	// Required modules + Core.
	love::Core * core = 0;
	love::Filesystem * filesystem = 0;

	pSound sound;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.audio [" << "OpenAL/SDL_sound" << "]" << std::endl;

		// Get modules.
		filesystem = core->getFilesystem();

		// Verify all.
		if(!filesystem->verify())
		{
			std::cerr << "Required module filesystem not loaded." << std::endl;
			return false;
		}

		love_openal::core = core;

		// Setup OpenAL.
		if(alutInit(0, 0)!=AL_TRUE)
		{
			std::cerr << "Could not init OpenAL." << std::endl;
 			return false;
		}

		// Set function pointers and load module.
		{
			love::Audio * a = core->getAudio();
			a->loaded = true;
		}

		ALfloat listenerPos[]={0,0,4.0};
		ALfloat listenerVel[]={0.0,0.0,0.0};
		ALfloat listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

    	alListenerfv(AL_POSITION,listenerPos);
    	alListenerfv(AL_VELOCITY,listenerVel);
    	alListenerfv(AL_ORIENTATION,listenerOri);

		// Create a sound.
		//love::pFile file;
		//sound = pSound(new Sound(file));
		//sound->play();

		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.audio [" << "OpenAL/SDL_sound" << "]" << std::endl;
		alutExit();
		return true;
	}

	bool module_open(void * vm)
	{
		return true;
	}

} // love_openal
