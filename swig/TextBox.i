
namespace love
{
	class TextBox : public GUIElement
	{
	protected:
	public:
		//TextBox(const string & text = "");
		//virtual ~TextBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		//virtual void setText(const string & text);
		//virtual void setName(const string & name);

		virtual void setCaretColumn(int column);
		virtual void setCaretPosition(unsigned int position);
		virtual void setCaretRow(int row);
		virtual void setCaretRowColumn(int row, int column);
		virtual void setEditable(bool editable);
		//virtual void setTextRow(int row, const string & text);

		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setActiveColor(const pAbstractColor & color);
		//virtual void setActiveBackgroundColor(const pAbstractColor & color);

		//virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		//virtual const string getText();
		//virtual const string & getName();

		virtual unsigned int getCaretColumn() const;
		virtual unsigned int getCaretPosition() const;
		virtual unsigned int getCaretRow() const;
		virtual unsigned int getNumberOfRows() const;
		//virtual const string & getRow(int row) const;
		virtual bool isEditable () const;

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getActiveColor();
		virtual pAbstractColor getActiveBackgroundColor();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics* graphics);
		virtual void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<TextBox> pTextBox;
}

// Extensions
%extend love::TextBox {

	void setText(const char * text)
	{
		self->setText(string(text));
	}

	void setName(const char * name)
	{
		self->setName(string(name));
	}
	
	void setTextRow(int row, const char * text)
	{
		self->setTextRow(row, string(text));
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
	
	const char * getRow(int row)
	{
		return self->getRow(row).c_str();
	}
};