
namespace love
{
	//class AbstractFile;
	
	class AbstractSoundDevice : public AbstractDevice
	{
	private:
	public:
	
		//AbstractSoundDevice();
		//virtual ~AbstractSoundDevice();
		
		// Don't want these to be available ...
		// virtual AbstractSound * getSound(AbstractFile * file) const = 0;
		// virtual AbstractMusic * getMusic(AbstractFile * file) const = 0;
		
		virtual bool isPlaying() const = 0;
		virtual bool isPaused() const = 0;
		virtual void pause() const = 0;
		virtual void stop() const = 0;
		virtual void resume() const = 0;
		virtual void setVolume(float volume) const = 0;

		// Extensions will be used, no need to wrap these ...
		//virtual void play(pAbstractSound sound, int loop = 0, int channel = -1) const = 0;
		//virtual void play(pAbstractMusic music, int loop = 0) const = 0;
		
	}; // AbstractSoundDevice
	
	typedef boost::shared_ptr<AbstractSoundDevice> pAbstractSoundDevice;
	
}


// Extensions
%extend love::AbstractSoundDevice {

	const char * fist() 
	{
		return "Diznick";
	}
	
	void play(const pAbstractSound * sound, int loop = 0, int channel = -1) const
	{
		self->play(*sound, loop, channel);
	}
	
	void play(const pAbstractMusic * music, int loop = 0) const
	{
		self->play(*music, loop);
	}

};