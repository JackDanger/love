
namespace love
{
	class CheckBox : public gcn::CheckBox, public GUIElement
	{
	protected:
	public:
		//CheckBox(const string & caption = "");
		//~CheckBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);

		//virtual void setCaption(const string & caption);
		//virtual void setName(const string & name);
		virtual void setMarked(bool marked);

		virtual void align(int alignment);
		virtual void valign(int alignment);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setHoverColor(const pAbstractColor & color);
		//virtual void setMarkedColor(const pAbstractColor & color);
		//virtual void setDefaultImage(const pAbstractImage & image);
		//virtual void setHoverImage(const pAbstractImage & image);
		//virtual void setMarkedImage(const pAbstractImage & image);

		//virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		//virtual const string & getCaption();
		//virtual const string & getName();
		virtual bool isMarked();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getHoverColor();
		virtual pAbstractColor getMarkedColor();
		virtual pAbstractImage getDefaultImage();
		virtual pAbstractImage getHoverImage();
		virtual pAbstractImage getMarkedImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();
	};

	typedef boost::shared_ptr<CheckBox> pCheckBox;
}

// Extensions
%extend love::CheckBox {

	void setCaption(const char * name)
	{
		self->setCaption(string(name));
	}

	void setName(const char * name)
	{
		self->setName(string(name));
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setHoverColor(const pAbstractColor * color)
	{
		self->setHoverColor(*color);
	}
	
	void setMarkedColor(const pAbstractColor * color)
	{
		self->setMarkedColor(*color);
	}
	
	void setDefaultImage(const pAbstractImage * image)
	{
		self->setDefaultImage(*image);
	}
	
	void setHoverImage(const pAbstractImage * image)
	{
		self->setHoverImage(*image);
	}
	
	void setMarkedImage(const pAbstractImage * image)
	{
		self->setMarkedImage(*image);
	}
	
	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	const char * getCaption()
	{
		return self->getCaption().c_str();
	}
	
	const char * getName()
	{
		return self->getName().c_str();
	}
};