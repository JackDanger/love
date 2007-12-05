
namespace love
{
	class Button : public GUIElement
	{
	protected:
	public:
		//Button(const string & caption);
		//virtual ~Button();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		//virtual void setCaption(const string & caption);
		//virtual void setName(const string & name);

		virtual void align(int alignment);
		virtual void valign(int alignment);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setHoverColor(const pAbstractColor & color);
		//virtual void setPressedColor(const pAbstractColor & color);
		//virtual void setHoverBackgroundColor(const pAbstractColor & color);
		//virtual void setPressedBackgroundColor(const pAbstractColor & color);

		//virtual void setDefaultImage(const pAbstractImage & image);
		//virtual void setHoverImage(const pAbstractImage & image);
		//virtual void setPressedImage(const pAbstractImage & image);

		//virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		//virtual const string & getCaption();
		//virtual const string & getName();
		
		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getHoverColor();
		virtual pAbstractColor getPressedColor();
		virtual pAbstractColor getHoverBackgroundColor();
		virtual pAbstractColor getPressedBackgroundColor();
		
		virtual pAbstractImage getDefaultImage();
		virtual pAbstractImage getHoverImage();
		virtual pAbstractImage getPressedImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

	};

	typedef boost::shared_ptr<Button> pButton;
}

// Extensions
%extend love::Button {

	void setCaption(const char * caption)
	{
		self->setCaption(string(caption));
	}
	
	void setName(const char * name)
	{
		self->setName(string(name));
	}

	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setHoverColor(const pAbstractColor * color)
	{
		self->setHoverColor(*color);
	}
	
	void setPressedColor(const pAbstractColor * color)
	{
		self->setPressedColor(*color);
	}
	
	void setHoverBackgroundColor(const pAbstractColor * color)
	{
		self->setHoverBackgroundColor(*color);
	}
	
	void setPressedBackgroundColor(const pAbstractColor * color)
	{
		self->setPressedBackgroundColor(*color);
	}

	void setDefaultImage(const pAbstractImage * image)
	{
		self->setDefaultImage(*image);
	}
	
	void setHoverImage(const pAbstractImage * image)
	{
		self->setHoverImage(*image);
	}
	
	void setPressedImage(const pAbstractImage * image)
	{
		self->setPressedImage(*image);
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