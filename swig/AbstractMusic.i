namespace love
{
	class AbstractMusic  : public Object, public Resource, public Loadable
	{
	private:
	public:
		
	}; // AbstractMusic
	
} // love

%template(SmartMusic) boost::shared_ptr<love::AbstractMusic>;