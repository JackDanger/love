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
		pAbstractColor selectionColor;
		pAbstractColor selectionBackgroundColor;

	public:
		ListBox(GUIList * list);
		~ListBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const char * name);

		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setSelectionColor(const pAbstractColor * color);
		virtual void setSelectionBackgroundColor(const pAbstractColor * color);

		virtual void setFont(const pAbstractFont * font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const char * getName();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getSeclectionColor();
		virtual pAbstractColor getSeclectionBackgroundColor();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void add(const char * text);
		virtual void remove(int i);
		virtual void clear();
		virtual const char * getElementAt(int i);
		virtual int getSelected();
		virtual const char * getSelectedElement();
		virtual int getNumberOfElements();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<ListBox> pListBox;
}

#endif
