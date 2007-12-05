
namespace love
{
	class GUIElement
	{
	protected:
	public:
		//GUIElement();
		//virtual ~GUIElement();

		//virtual void setColor(const pAbstractColor & color);
		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setBorderColor(const pAbstractColor & color);

		//virtual void setFont(const pAbstractFont & font);

		virtual pAbstractColor getColor();
		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getBorderColor();
		
		virtual pAbstractFont getFont();

		virtual void setSize(int width, int height) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual void setBorderSize(unsigned int size) = 0;

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual unsigned int getBorderSize() = 0;

		virtual void adjustSize() = 0;
	};

	typedef boost::shared_ptr<GUIElement> pGUIElement;
}

// Extensions
%extend love::GUIElement {

	void setColor(const pAbstractColor * color)
	{
		self->setColor(*color);
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setBorderColor(const pAbstractColor * color)
	{
		self->setBorderColor(*color);
	}

	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
};