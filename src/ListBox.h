#ifndef LOVE_LIST_BOX_H
#define LOVE_LIST_BOX_H

#include "GUIElement.h"
#include "GUIList.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	/**
	 * @class ListBox
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-10-28
	 * @brief A list box used by the Menu.
	 **/
	class ListBox : public gcn::ListBox, public GUIElement
	{
	protected:
		GUIList * list;
		pAbstractColor activeColor;
		pAbstractColor selectionColor;

	public:
		ListBox(GUIList * list);
		~ListBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const char * name);

		virtual void setActiveColor(const pAbstractColor * color);
		virtual void setActiveColor(const pColor * color);
		virtual void setActiveColor(const pAnimatedColor * color);
		virtual void setSelectionColor(const pAbstractColor * color);
		virtual void setSelectionColor(const pColor * color);
		virtual void setSelectionColor(const pAnimatedColor * color);

		virtual const pAbstractColor * getActiveColor();
		virtual const pAbstractColor * getSeclectionColor();

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const char * getName();

		virtual void adjustSize();

		virtual void add(const char * text);
		virtual void remove(int i);
		virtual void clear();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<ListBox> pListBox;
}

#endif
