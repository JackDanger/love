
namespace love
{
	class AbstractMenu : public GUIElement, public Padded
	{
	protected:
	public:
		//static const int LOVE_MENU_VERTICAL = 1;
		//static const int LOVE_MENU_HORIZONTAL = 2;
		//static const int LOVE_MENU_DEFAULT = 0;
		//static const int LOVE_MENU_WINDOW = 1;
		//static const int LOVE_MENU_SCROLL = 2;

		//AbstractMenu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);
		//~AbstractMenu();

		virtual void show() = 0;
		virtual void hide() = 0;
		virtual bool isVisible() = 0;

		//virtual void setFont(const pAbstractFont & font);
		//virtual void setColor(const pAbstractColor & color);
		//virtual void setBackgroundColor(const pAbstractColor & color);
		//virtual void setBackground(const pAbstractImage & image);

		virtual void setSpacing(int spacing);

		virtual void stretchContent(bool stretch);
		virtual void align(int alignment);
		virtual void valign(int alignment);

		virtual pAbstractFont getFont();
		virtual pAbstractColor getBackgroundColor();

		virtual int getSpacing();

		int getMenuType() const;

		virtual void setSize(int width, int height) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual void setBorderSize(unsigned int size) = 0;
		virtual void setPosition(int x, int y) = 0;
		virtual void setX(int x) = 0;
		virtual void setY(int y) = 0;

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual int getX() = 0;
		virtual int getY() = 0;
		virtual unsigned int getBorderSize() = 0;

		virtual void adjustSize() = 0; //resize to content
		virtual void adjustWidth() = 0; //adjust width only
		virtual void adjustHeight() = 0; //adjust height only
		virtual int adjustContent() = 0; //aligns all the content to the alignment

		// used with WindowMenu only
		virtual void setCaption(const char * caption) = 0;
		virtual void setTitleBarHeight(unsigned int height) = 0;
		virtual const char * getCaption() = 0;
		virtual unsigned int getTitleBarHeight() = 0;

		// adding things
		virtual boost::shared_ptr<AbstractMenu> addMenu(int type, int width = 0, int height = 0);
		virtual boost::shared_ptr<AbstractMenu> addScrollMenu(int type, int width = 0, int height = 0);
	};

	typedef boost::shared_ptr<AbstractMenu> pAbstractMenu;
}


// Extensions
%extend love::AbstractMenu {

	void setFont(const pAbstractFont * font)
	{
		self->setFont(*font);
	}
	
	void setColor(const pAbstractColor * color)
	{
		self->setColor(*color);
	}
	
	void setBackgroundColor(const pAbstractColor * color)
	{
		self->setBackgroundColor(*color);
	}
	
	void setBackground(const pAbstractImage * image)
	{
		self->setBackground(*image);
	}
	
	boost::shared_ptr<AbstractMenu> addWindowMenu(int type, const char * caption = "", int width = 0, int height = 0)
	{
		return self->addWindowMenu(type, string(caption), width, height);
	}
	
	pLabel addLabel(const char * caption, int width = 0, int height = 0)
	{
		return self->addLabel(string(caption), width, height);
	}
	
	pMultilineLabel addMultilineLabel(const char * caption, int width = 0, int height = 0)
	{
		return self->addMultilineLabel(string(caption), width, height);
	}
	
	pLabel addImage(const pAbstractImage * image)
	{
		return self->addImage(*image);
	}
	
	pButton addButton(const char * name, const char * caption, int width = 0, int height = 0)
	{
		return self->addButton(string(name), string(caption), width, height);
	}
	
	pTextField addTextField(const char * name, const char * text = "", int width = 0, int height = 0)
	{
		return self->addTextField(string(name), string(text), width, height);
	}
	
	pDropDown addDropDown(const char * name, int width = 0, int height = 0)
	{
		return self->addDropDown(string(name), width, height);
	}
	
	pRadioButton addRadioButton(const char * name, const char * caption = "", int width = 0, int height = 0)
	{
		return self->addRadioButton(string(name), string(caption), width, height);
	}
	
	pCheckBox addCheckBox(const char * name, const char * caption = "", int width = 0, int height = 0)
	{
		return self->addCheckBox(string(name), string(caption), width, height);
	}
	
	pSlider addSlider(const char * name, unsigned int orientation = Slider::LOVE_SLIDER_HORIZONTAL, double scaleStart = 0, double scaleEnd = 1, int width = 0, int height = 0)
	{
		return self->addSlider(string(name), orientation, scaleStart, scaleEnd, width, height);
	}
	
	pListBox addListBox(const char * name, int width = 0, int height = 0)
	{
		return self->addListBox(string(name), width, height);
	}
	
	pTextBox addTextBox(const char * name, int width = 0, int height = 0)
	{
		return self->addTextBox(string(name), width, height);
	}

};