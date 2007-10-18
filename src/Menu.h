#ifndef LOVE_MENU_H
#define LOVE_MENU_H

#include "AbstractColor.h"
#include "AbstractGraphics.h"
#include "AbstractImage.h"
#include "Button.h"
#include "DropDown.h"
#include "Label.h"
#include "MultilineLabel.h"
#include "Padded.h"
#include "TextField.h"
#include "RadioButton.h"
#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	class GUIText;
	/**
	 * @class Menu
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-11
	 * @brief Holds the graphical information and the items that make up a menu.
	 **/
	class Menu : public gcn::Container, public Padded
	{
	private:
		
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pAbstractImage background;
		GUIText * text;
		int width, height;
		int type;
		int spacing;
		int position;
		int alignment;
		int verticalAlignment;
		bool stretch;
		bool visible;

		void positionItem(gcn::Widget * item);

	public:
		static const int LOVE_MENU_VERTICAL = 1;
		static const int LOVE_MENU_HORIZONTAL = 2;

		/**
		 * @param type The type of menu (vertical / horizontal).
		 * @brief Calls the GUIchan constructor and sets the background as invisible.
		 **/
		Menu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~Menu();

		void setSize(int width, int height);
		void setWidth(int width);
		void setHeight(int height);
		void setBorderSize(unsigned int size);
		void setPosition(int x, int y);
		void setX(int x);
		void setY(int y);

		void show();
		void hide();

		void setFont(AbstractFont * font);
		void setFont(const pAbstractFont * font);
		void setColor(const pAbstractColor * color);
		void setBackgroundColor(const pAbstractColor * color);
		void setBorderColor(const pAbstractColor * color);
		void setBackground(const pAbstractImage * image);

		void stretchContent(bool stretch);
		void align(int alignment);
		void valign(int alignment);

		void setSpacing(int spacing); //how much distance there is to be between the items

		int getWidth();
		int getHeight();
		int getX();
		int getY();
		unsigned int getBorderSize();

		int getSpacing();

		void adjustSize(); //resize to content
		void adjustWidth(); //adjust width only
		void adjustHeight(); //adjust height only
		int adjustContent(); //aligns all the content to the alignment

		void draw(gcn::Graphics* graphics);
		void drawBorder(gcn::Graphics* graphics);
		void drawChildren(gcn::Graphics* graphics);

		Menu * addMenu(int type, int width = 0, int height = 0);
		Label * addLabel(const char * caption, int width = 0, int height = 0);
		MultilineLabel * addMultilineLabel(const char * caption, int width = 0, int height = 0);
		Label * addImage(const pAbstractImage * image);
		Button * addButton(const char * name, const char * caption, int width = 0, int height = 0);
		TextField * addTextField(const char * name, const char * text = "", int width = 0, int height = 0);
		DropDown * addDropDown(const char * name, int width = 0, int height = 0);
		RadioButton * addRadioButton(const char * name, const char * caption = "", int width = 0, int height = 0);
	};

	typedef boost::shared_ptr<Menu> pMenu;
}

#endif

