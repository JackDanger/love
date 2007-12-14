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
		pAbstractImage backgroundImage;
		pAbstractColor selectionColor;
		pAbstractColor selectionBackgroundColor;

	public:
		ListBox(GUIList * list);
		~ListBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const std::string & name);

		virtual void setBackgroundColor(const pAbstractColor & color);
		virtual void setSelectionColor(const pAbstractColor & color);
		virtual void setSelectionBackgroundColor(const pAbstractColor & color);
		virtual void setBackgroundImage(const pAbstractImage & image);

		virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const std::string & getName();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getSelectionColor();
		virtual pAbstractColor getSelectionBackgroundColor();
		virtual pAbstractImage getBackgroundImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void add(const std::string & text);
		virtual void remove(int i);
		virtual void clear();
		virtual std::string getElementAt(int i);
		virtual int getSelected();
		virtual std::string getSelectedElement();
		virtual int getNumberOfElements();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<ListBox> pListBox;
}

#endif
