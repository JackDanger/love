#ifndef LOVE_SCROLL_MENU_H
#define LOVE_SCROLL_MENU_H

#include "AbstractMenu.h"

namespace love
{
	/**
	 * @class ScrollMenu
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-11-20
	 * @brief A menu that can be scrolled.
	 **/
	class ScrollMenu : public gcn::ScrollArea, public AbstractMenu
	{
	protected:
		gcn::Container * container;

		virtual void positionItem(gcn::Widget * item);

	public:
		ScrollMenu(pAbstractFont font, pAbstractColor color, int type = LOVE_MENU_VERTICAL);
		~ScrollMenu();

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

		virtual void setFont(const pAbstractFont & font);
		virtual void setBackgroundColor(const pAbstractColor & color);

		virtual int getWidth();
		virtual int getHeight();
		virtual int getX();
		virtual int getY();
		virtual unsigned int getBorderSize();

		virtual pAbstractFont getFont();
		//virtual pAbstractColor getColor();
		virtual pAbstractColor getBackgroundColor();
		//virtual pAbstractColor getBorderColor();

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

	typedef boost::shared_ptr<ScrollMenu> pScrollMenu;
}

#endif
