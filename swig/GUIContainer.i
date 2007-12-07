
namespace love
{
	class GUIContainer
	{
	protected:
	public:
		//GUIContainer();
		//~GUIContainer();

		//virtual void add(const pAbstractMenu & menu);
		//virtual void remove(const pAbstractMenu & menu);
		
		virtual bool hasFocus();
	};

	typedef boost::shared_ptr<GUIElement> pGUIElement;
}

// Extensions
%extend love::GUIContainer {

	void add(const pAbstractMenu * menu)
	{
		self->add(*menu);
	}
	
	void remove(const pAbstractMenu * menu)
	{
		self->remove(*menu);
	}
};