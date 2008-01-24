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
		
	};
}

// Extensions
%extend love::Audio 
{
	void play(const pSound * sound, int loop = 1, int channel = -1)
	{
		self->play(*sound, loop, channel);
	}
	
	void play(const pMusic * music, int loop = 1)
	{
		self->play(*music, loop);
	}
}
