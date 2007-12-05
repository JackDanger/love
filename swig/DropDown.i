
namespace love
{
	class DropDown : public GUIElement
	{
	protected:
	public:
		//DropDown(GUIList * list);
		//~DropDown();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		//virtual void setName(const string & name);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setListColor(const pAbstractColor & color);
		//virtual void setListBackgroundColor(const pAbstractColor & color);
		//virtual void setSelectedColor(const pAbstractColor & color);
		//virtual void setSelectedBackgroundColor(const pAbstractColor & color);
		//virtual void setButtonColor(const pAbstractColor & color);
		//virtual void setButtonBackgroundColor(const pAbstractColor & color);
		//virtual void setButtonHoverColor(const pAbstractColor & color);
		//virtual void setButtonHoverBackgroundColor(const pAbstractColor & color);
		//virtual void setButtonPressedColor(const pAbstractColor & color);
		//virtual void setButtonPressedBackgroundColor(const pAbstractColor & color);

		//virtual void setFont(const pAbstractFont & font);

		//virtual void setBackgroundImage(const pAbstractImage & image);
		//virtual void setListImage(const pAbstractImage & image);
		//virtual void setButtonImage(const pAbstractImage & image);
		//virtual void setButtonHoverImage(const pAbstractImage & image);
		//virtual void setButtonPressedImage(const pAbstractImage & image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		//virtual const string & getName();

		virtual void adjustSize();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getListColor();
		virtual pAbstractColor getListBackgroundColor();
		virtual pAbstractColor getHoverColor();
		virtual pAbstractColor getHoverBackgroundColor();
		virtual pAbstractColor getSelectedColor();
		virtual pAbstractColor getSelectedBackgroundColor();
		virtual pAbstractColor getButtonColor();
		virtual pAbstractColor getButtonBackgroundColor();
		virtual pAbstractColor getButtonHoverColor();
		virtual pAbstractColor getButtonHoverBackgroundColor();
		virtual pAbstractColor getButtonPressedColor();
		virtual pAbstractColor getButtonPressedBackgroundColor();

		virtual pAbstractFont getFont();

		virtual pAbstractImage getBackgroundImage();
		virtual pAbstractImage getListImage();
		virtual pAbstractImage getButtonImage();
		virtual pAbstractImage getButtonHoverImage();
		virtual pAbstractImage getButtonPressedImage();

		//virtual void add(const string & text);
		virtual void remove(int i);
		virtual void clear();
		//virtual string getElementAt(int i);
		virtual int getSelected();
		virtual void setSelected(int selected);
		//virtual string getSelectedElement();
		virtual int getNumberOfElements();
		
		virtual void closeOnSelect(bool value);
		virtual bool closesOnSelect();
	};

	typedef boost::shared_ptr<DropDown> pDropDown;
}

// Extensions
%extend love::DropDown {

	void setName(const char * name)
	{
		self->setName(string(name));
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setListColor(const pAbstractColor * color)
	{
		self->setListColor(*color);
	}
	
	void setListBackgroundColor(const pAbstractColor * color)
	{
		self->setListBackgroundColor(*color);
	}
	
	void setHoverColor(const pAbstractColor * color)
	{
		self->setHoverColor(*color);
	}
	
	void setHoverBackgroundColor(const pAbstractColor * color)
	{
		self->setHoverBackgroundColor(*color);
	}
	
	void setSelectedColor(const pAbstractColor * color)
	{
		self->setSelectedColor(*color);
	}
	
	void setSelectedBackgroundColor(const pAbstractColor * color)
	{
		self->setSelectedBackgroundColor(*color);
	}
	
	void setButtonColor(const pAbstractColor * color)
	{
		self->setButtonColor(*color);
	}
	
	void setButtonBackgroundColor(const pAbstractColor * color)
	{
		self->setButtonBackgroundColor(*color);
	}
	
	void setButtonHoverColor(const pAbstractColor * color)
	{
		self->setButtonHoverColor(*color);
	}
	
	void setButtonHoverBackgroundColor(const pAbstractColor * color)
	{
		self->setButtonHoverBackgroundColor(*color);
	}
	
	void setButtonPressedColor(const pAbstractColor * color)
	{
		self->setButtonPressedColor(*color);
	}
	
	void setButtonPressedBackgroundColor(const pAbstractColor * color)
	{
		self->setButtonPressedBackgroundColor(*color);
	}
	
	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	void setBackgroundImage(const pAbstractImage * image)
	{
		self->setBackgroundImage(*image);
	}
	
	void setListImage(const pAbstractImage * image)
	{
		self->setListImage(*image);
	}

	void setButtonImage(const pAbstractImage * image)
	{
		self->setButtonImage(*image);
	}
	
	void setButtonHoverImage(const pAbstractImage * image)
	{
		self->setButtonHoverImage(*image);
	}
	
	void setButtonPressedImage(const pAbstractImage * image)
	{
		self->setButtonPressedImage(*image);
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