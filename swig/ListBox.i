
namespace love
{

	class ListBox : public gcn::ListBox, public GUIElement
	{
	protected:
	public:
		//ListBox(GUIList * list);
		//~ListBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		//virtual void setName(const string & name);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setSelectionColor(const pAbstractColor & color);
		//virtual void setSelectionBackgroundColor(const pAbstractColor & color);
		//virtual void setBackgroundImage(const pAbstractImage & image);

		//virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		//virtual const string & getName();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getSelectionColor();
		virtual pAbstractColor getSelectionBackgroundColor();
		virtual pAbstractImage getBackgroundImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		//virtual void add(const string & text);
		virtual void remove(int i);
		virtual void clear();
		//virtual string getElementAt(int i);
		virtual int getSelected();
		//virtual string getSelectedElement();
		virtual int getNumberOfElements();
	};

	typedef boost::shared_ptr<ListBox> pListBox;
}

// Extensions
%extend love::ListBox {

	void setName(const char * name)
	{
		self->setName(string(name));
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setSelectionColor(const pAbstractColor * color)
	{
		self->setSelectionColor(*color);
	}
	
	void setSelectionBackgroundColor(const pAbstractColor * color)
	{
		self->setSelectionBackgroundColor(*color);
	}
	
	void setBackgroundImage(const pAbstractImage * image)
	{
		self->setBackgroundImage(*image);
	}
	
	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	const char * getName()
	{
		return self->getName().c_str();
	}
	
	void add(const char * text)
	{
		self->add(string(text));
	}
	
	const char * getElementAt(int i)
	{
		return self->getElementAt(i).c_str();
	}
	
	const char * getSelectedElement()
	{
		return self->getSelectedElement().c_str();
	}
};