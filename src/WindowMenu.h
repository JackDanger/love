#ifndef LOVE_WINDOW_MENU_H
#define LOVE_WINDOW_MENU_H

#include "AbstractMenu.h"

namespace love
{
	class GUIText;
	/**
	 * @class Menu
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-11-20
	 * @brief A menu that can be dragged around.
	 **/
	class WindowMenu : public gcn::Window, public AbstractMenu
	{
	protected:
		virtual void positionItem(gcn::Widget * item);

	public:
		WindowMenu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);
		~WindowMenu();

		virtual void show();
		virtual void hide();
		virtual bool isVisible();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setPosition(int x, int y);
		virtual void setX(int x);
		virtual void setY(int y);
		virtual void setCaption(const char * caption);
		virtual void setTitleBarHeight(unsigned int height);

		virtual void setFont(const pAbstractFont & font);
		virtual void setBackgroundColor(const pAbstractColor & color);

		virtual int getWidth();
		virtual int getHeight();
		virtual int getX();
		virtual int getY();
		virtual unsigned int getBorderSize();
		virtual const char * getCaption();
		virtual unsigned int getTitleBarHeight();

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

		// overwritten to remove focus
	};

	typedef boost::shared_ptr<WindowMenu> pWindowMenu;
}

#endif

