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
		
		AbstractColor * color;
		AbstractColor * backgroundColor;
		AbstractImage * background;
		GUIText * text;
		int width, height;
		int type;
		int spacing;
		int position;
		int alignment;
		int verticalAlignment;
		bool stretch;

		void positionItem(gcn::Widget * item);

	public:
		static const int LOVE_MENU_VERTICAL = 1;
		static const int LOVE_MENU_HORIZONTAL = 2;
		static const int LOVE_ALIGN_LEFT = 1;
		static const int LOVE_ALIGN_RIGHT = 2;
		static const int LOVE_ALIGN_CENTER = 3;
		static const int LOVE_ALIGN_TOP = 4;
		static const int LOVE_ALIGN_BOTTOM = 5;

		/**
		 * @param type The type of menu (vertical / horizontal).
		 * @brief Calls the GUIchan constructor and sets the background as invisible.
		 **/
		Menu(int type = LOVE_MENU_VERTICAL);

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~Menu();

		/**
		 * The following are Container functions, but should be documented:
		 * setPosition(x,y)
		 * setX(x)
		 * setY(y)
		 * setSize(width, height)
		 * setWidth(width)
		 * setHeight(height)
		 *
		 * getX()
		 * getY()
		 * getWidth()
		 * getHeight()
		 **/

		void setFont(AbstractFont * font);
		void setColor(AbstractColor * color);

		void align(int alignment);
		void valign(int alignment);

		void setBackgroundColor(AbstractColor * color);
		void setBackground(AbstractImage * image);

		void setSpacing(int spacing); //how much distance there is to be between the items
		int getSpacing();

		void adjustSize(); //resize to content
		int adjustContent(); //aligns all the content to the new(?) alignment

		void stretchContent(bool stretch);

		void draw(gcn::Graphics* graphics);

		Menu * addMenu(int type, int width = 0, int height = 0);
		Label * addLabel(const char * caption, int width = 0, int height = 0);
		MultilineLabel * addMultilineLabel(const char * caption, int width = 0, int height = 0);
		Label * addImage(AbstractImage * image);
		Button * addButton(const char * caption, int width = 0, int height = 0);
		TextField * addTextField(const char * text, int width = 0, int height = 0);
		DropDown * addDropDown(int width = 0, int height = 0);
	};

	typedef boost::shared_ptr<Menu> pMenu;
}

#endif

