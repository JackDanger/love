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
		AbstractColor * color;
		AbstractColor * activeColor;
		AbstractColor * backgroundColor;
		AbstractColor * activeBackgroundColor;
		AbstractColor * selectionBackgroundColor;
		AbstractColor * borderColor;
		AbstractColor * buttonColor;
		AbstractColor * buttonBackgroundColor;

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

		void setColor(AbstractColor * color);
		void setActiveColor(AbstractColor * color);
		void setBackgroundColor(AbstractColor * color);
		void setActiveBackgroundColor(AbstractColor * color);
		void setSelectionBackgroundColor(AbstractColor * color);
		void setBorderColor(AbstractColor * color);
		void setButtonColor(AbstractColor * color);
		void setButtonBackgroundColor(AbstractColor * color);

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

