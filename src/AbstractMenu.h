#ifndef LOVE_ABSTRACT_MENU_H
#define LOVE_ABSTRACT_MENU_H

// LOVE
#include "GUIElement.h"
#include "AbstractColor.h"
#include "AbstractGraphics.h"
#include "AbstractImage.h"
#include "Text.h"

// GUI elements
#include "Button.h"
#include "DropDown.h"
#include "Label.h"
#include "MultilineLabel.h"
#include "Padded.h"
#include "TextField.h"
#include "RadioButton.h"
#include "CheckBox.h"
#include "Slider.h"
#include "ListBox.h"
#include "TextBox.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

using std::vector;

namespace love
{
	class GUIText;
	/**
	 * @class AbstractMenu
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-11
	 * @brief Holds the graphical information and the items that make up a menu.
	 **/
	class AbstractMenu : public GUIElement, public Padded
	{
	protected:
		pAbstractImage background;
		pGUIText text;
		vector<pGUIElement> children; // you are all my children

		int menuType; // used for adding/removing the menu from teh GUIContainer
		int type;
		int spacing;
		int position;
		int alignment;
		int verticalAlignment;
		bool stretch;
		bool visible;

		virtual void positionItem(gcn::Widget * item) = 0;

	public:
		static const int LOVE_MENU_VERTICAL = 1;
		static const int LOVE_MENU_HORIZONTAL = 2;
		static const int LOVE_MENU_DEFAULT = 0;
		static const int LOVE_MENU_WINDOW = 1;
		static const int LOVE_MENU_SCROLLING = 2;

		/**
		 * @param type The type of menu (vertical / horizontal).
		 * @brief Calls the GUIchan constructor and sets the background as invisible.
		 **/
		AbstractMenu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		~AbstractMenu();

		virtual void show();
		virtual void hide();

		virtual void setFont(const pAbstractFont * font);
		//virtual void setColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		//virtual void setBorderColor(const pAbstractColor * color);
		virtual void setBackground(const pAbstractImage * image);

		virtual void setSpacing(int spacing); //how much distance there is to be between the items

		virtual void stretchContent(bool stretch);
		virtual void align(int alignment);
		virtual void valign(int alignment);

		virtual pAbstractFont getFont();
		//virtual pAbstractColor getColor();
		virtual pAbstractColor getBackgroundColor();
		//virtual pAbstractColor getBorderColor();

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

		// gui-chan draw functions
		virtual void draw(gcn::Graphics* graphics) = 0;
		virtual void drawBorder(gcn::Graphics* graphics) = 0;
		virtual void drawChildren(gcn::Graphics* graphics) = 0;

		virtual void add(gcn::Widget * widget) = 0;

		virtual boost::shared_ptr<AbstractMenu> addMenu(int type, int width = 0, int height = 0);
		virtual pLabel addLabel(const char * caption, int width = 0, int height = 0);
		virtual pMultilineLabel addMultilineLabel(const char * caption, int width = 0, int height = 0);
		virtual pLabel addImage(const pAbstractImage * image);
		virtual pButton addButton(const char * name, const char * caption, int width = 0, int height = 0);
		virtual pTextField addTextField(const char * name, const char * text = "", int width = 0, int height = 0);
		virtual pDropDown addDropDown(const char * name, int width = 0, int height = 0);
		virtual pRadioButton addRadioButton(const char * name, const char * caption = "", int width = 0, int height = 0);
		virtual pCheckBox addCheckBox(const char * name, const char * caption = "", int width = 0, int height = 0);
		virtual pSlider addSlider(const char * name, unsigned int orientation = Slider::LOVE_SLIDER_HORIZONTAL, double scaleStart = 0, double scaleEnd = 1, int width = 0, int height = 0);
		virtual pListBox addListBox(const char * name, int width = 0, int height = 0);
		//This is very buggy. I'll look at it later.
		//virtual TextBox * addTextBox(const char * name, int width = 0, int height = 0);
	};

	typedef boost::shared_ptr<AbstractMenu> pAbstractMenu;
}

#endif
