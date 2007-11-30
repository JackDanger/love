#ifndef LOVE_MENU_H
#define LOVE_MENU_H

#include "AbstractMenu.h"

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
	class Menu : public gcn::Container, public AbstractMenu
	{
	protected:
		virtual void positionItem(gcn::Widget * item);

	public:
		Menu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);
		~Menu();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setPosition(int x, int y);
		virtual void setX(int x);
		virtual void setY(int y);

		virtual void setFont(const pAbstractFont & font);
		virtual void setBackgroundColor(const pAbstractColor & color);

		virtual int getWidth();
		virtual int getHeight();
		virtual int getX();
		virtual int getY();
		virtual unsigned int getBorderSize();

		virtual pAbstractFont getFont();
		virtual pAbstractColor getBackgroundColor();

		virtual void adjustSize(); //resize to content
		virtual void adjustWidth(); //adjust width only
		virtual void adjustHeight(); //adjust height only
		virtual int adjustContent(); //aligns all the content to the alignment

		virtual void draw(gcn::Graphics* graphics);
		virtual void drawBorder(gcn::Graphics* graphics);
		virtual void drawChildren(gcn::Graphics* graphics);

		virtual void add(gcn::Widget * widget);

		// used with WindowMenu only
		virtual void setCaption(const char * caption);
		virtual void setTitleBarHeight(unsigned int height);
		virtual const char * getCaption();
		virtual unsigned int getTitleBarHeight();
	};

	typedef boost::shared_ptr<Menu> pMenu;
}

#endif

