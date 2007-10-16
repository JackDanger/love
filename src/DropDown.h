#ifndef LOVE_DROP_DOWN_H
#define LOVE_DROP_DOWN_H

#include "AbstractColor.h"
#include "GUIList.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	/**
	 * @class DropDown
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-17
	 * @brief A drop-down list to be used by the Menu.
	 **/
	class DropDown : public gcn::DropDown
	{
	protected:
		GUIList * list;
		pAbstractColor color;
		pAbstractColor activeColor;
		pAbstractColor backgroundColor;
		pAbstractColor activeBackgroundColor;
		pAbstractColor selectionBackgroundColor;
		pAbstractColor borderColor;
		pAbstractColor buttonColor;
		pAbstractColor buttonBackgroundColor;

	public:
		DropDown(GUIList * list);
		~DropDown();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const char * name);

		virtual void setColor(const pAbstractColor * color);
		virtual void setActiveColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setActiveBackgroundColor(const pAbstractColor * color);
		virtual void setSelectionBackgroundColor(const pAbstractColor * color);
		virtual void setBorderColor(const pAbstractColor * color);
		virtual void setButtonColor(const pAbstractColor * color);
		virtual void setButtonBackgroundColor(const pAbstractColor * color);

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
		virtual void drawButton(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<DropDown> pDropDown;
}

#endif

