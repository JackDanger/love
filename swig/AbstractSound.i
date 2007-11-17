namespace love
{
	class AbstractSound : public Object, public Resource, public Loadable
	{
	private:
	public:
			
		virtual void setVolume(float volume) = 0;
		
	}; // AbstractSound
	
} // love

%template(SmartSound) boost::shared_ptr<love::AbstractSound>;

