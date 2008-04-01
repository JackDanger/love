%module mod_sdlmixer

%{#include "love_sdlmixer.h"%}

%{#include <boost/shared_ptr.hpp>%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%include Sound.i
%include Music.i

namespace love_sdlmixer
{
	pSound newSound(const char * filename);
	pMusic newMusic(const char * filename);
	bool isPlaying();
	bool isPaused();
	void pause();
	void stop();
	void resume();
	void setVolume(float volume);
	void play(const pSound & sound, int loop = 1, int channel = -1);
	void play(const pMusic & music, int loop = 1);
}
