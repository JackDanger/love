namespace love
{
	class Label : public GUIElement
	{
	protected:
	public:
		//Label(const string caption = "");
		//virtual ~Label();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		//virtual void setCaption(const string & caption);
		
		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setFont(const pAbstractFont & font);

		virtual void align(int alignment);
		virtual void valign(int alignment);

		//virtual void setBackgroundImage(const pAbstractImage & image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		//virtual const string getCaption();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractImage getBackgroundImage();
		virtual pAbstractFont getFont();

		virtual void adjustSize();
	};

	typedef boost::shared_ptr<Label> pLabel;
}

// Extensions
%extend love::Label {

	void setCaption(const char * caption)
	{
		self->setCaption(string(caption));
	}

	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setBackgroundImage(const pAbstractImage * image)
	{
		self->setBackgroundImage(*image);
	}
	
	const char * getCaption()
	{
		return self->getCaption().c_str();
	}

};