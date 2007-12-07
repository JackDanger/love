
namespace love
{

	class TextField : public GUIElement, public Padded
	{
	protected:
	public:
		//TextField(const string & text = "");
		//virtual ~TextField();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);

		//virtual void setText(const string & text);
		//virtual void setName(const string & name);

		virtual void setCaretPosition(unsigned int position);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setActiveColor(const pAbstractColor & color);
		//virtual void setActiveBackgroundColor(const pAbstractColor & color);
		//virtual void setBackgroundImage(const pAbstractImage & image);

		//virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		//virtual const string & getText();
		//virtual const string & getName();

		virtual unsigned int getCaretPosition();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getActiveColor();
		virtual pAbstractColor getActiveBackgroundColor();
		virtual pAbstractImage getBackgroundImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();
	};

	typedef boost::shared_ptr<TextField> pTextField;
}

// Extensions
%extend love::TextField {

	void setText(const char * text)
	{
		self->setText(string(text));
	}
	
	void setName(const char * name)
	{
		self->setName(string(name));
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setActiveColor(const pAbstractColor * color)
	{
		self->setActiveColor(*color);
	}

	void setActiveBackgroundColor(const pAbstractColor * color)
	{
		self->setActiveBackgroundColor(*color);
	}
	
	void setBackgroundImage(const pAbstractImage * image)
	{
		self->setBackgroundImage(*image);
	}
	
	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	const char * getText()
	{
		return self->getText().c_str();
	}
	
	const char * getName()
	{
		return self->getName().c_str();
	}

};