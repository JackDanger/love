%{#include "Sound.h"%}

namespace love_sdlmixer
{
	class Sound
	{
	private:
	public:
		virtual void setVolume(float volume) = 0;
		
	}; // Sound

	typedef boost::shared_ptr<Sound> pSound;
	
} // love

%template(SmartSound) boost::shared_ptr<love_sdlmixer::Sound>;