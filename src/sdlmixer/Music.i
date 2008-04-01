%{#include "Music.h"%}

namespace love_sdlmixer
{
	class Music
	{
	private:
	public:
	}; // Music

	typedef boost::shared_ptr<Music> pMusic;
	
} // love

%template(SmartMusic) boost::shared_ptr<love_sdlmixer::Music>;