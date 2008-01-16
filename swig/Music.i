%{#include "Music.h"%}

namespace love
{
	class Music
	{
	private:
	public:
	}; // Music

	typedef boost::shared_ptr<Music> pMusic;
	
} // love

%template(SmartMusic) boost::shared_ptr<love::Music>;