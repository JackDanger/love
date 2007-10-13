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
	private:
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

		/**
		 * gcn::DropDown functions that should be documented:
		 * setSize(width, height)
		 * setWidth(width)
		 * setHeight(height)
		 * setBorderSize(size)
		 * adjustHeight()
		 */

		void setColor(const pAbstractColor * color);
		void setActiveColor(const pAbstractColor * color);
		void setBackgroundColor(const pAbstractColor * color);
		void setActiveBackgroundColor(const pAbstractColor * color);
		void setSelectionBackgroundColor(const pAbstractColor * color);
		void setBorderColor(const pAbstractColor * color);
		void setButtonColor(const pAbstractColor * color);
		void setButtonBackgroundColor(const pAbstractColor * color);

		void add(const char * text);
		void remove(int i);
		void clear();

		void draw(gcn::Graphics * graphics);
		void drawBorder(gcn::Graphics * graphics);
		void drawButton(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<DropDown> pDropDown;
}

#endif

