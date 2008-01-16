%{#include "Audio.h"%}

namespace love
{
	class Audio : public Device
	{
	private:
	public:
		virtual bool isPlaying() const = 0;
		virtual bool isPaused() const = 0;
		virtual void pause() const = 0;
		virtual void stop() const = 0;
		virtual void resume() const = 0;
		virtual void setVolume(float volume) const = 0;
		virtual void play(pSound sound, int loop = 1, int channel = -1) const = 0;
		virtual void play(pMusic music, int loop = 1) const = 0;
		
	};
}
