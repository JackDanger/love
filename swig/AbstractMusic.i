namespace love
{
	class AbstractMusic  : public Object, public Resource, public Loadable
	{
	private:
	public:
		
	}; // AbstractMusic
	
	typedef boost::shared_ptr<AbstractMusic> pAbstractMusic;
	
} // love

%template(SmartMusic) boost::shared_ptr<love::AbstractMusic>;