#ifndef LOVE_DROP_DOWN_H
#define LOVE_DROP_DOWN_H

#include "GUIElement.h"
#include "GUIList.h"

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
	class DropDown : public gcn::DropDown, public GUIElement
	{
	protected:
		GUIList * list;
		pAbstractColor activeColor;
		pAbstractColor activeBackgroundColor;
		pAbstractColor selectionColor;
		pAbstractColor selectionBackgroundColor;
		pAbstractColor buttonColor;
		pAbstractColor buttonBackgroundColor;
		pAbstractImage button;
		pAbstractImage buttonPressed;

	public:
		DropDown(GUIList * list);
		~DropDown();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const char * name);

		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setActiveColor(const pAbstractColor * color);
		virtual void setActiveBackgroundColor(const pAbstractColor * color);
		virtual void setSelectionColor(const pAbstractColor * color);
		virtual void setSelectionBackgroundColor(const pAbstractColor * color);
		virtual void setButtonColor(const pAbstractColor * color);
		virtual void setButtonBackgroundColor(const pAbstractColor * color);

		virtual void setFont(const pAbstractFont * font);

		virtual void setButton(const pAbstractImage * image);
		virtual void setButtonPressed(const pAbstractImage * image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const char * getName();

		virtual void adjustSize();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getActiveColor();
		virtual pAbstractColor getActiveBackgroundColor();
		virtual pAbstractColor getSelectionColor();
		virtual pAbstractColor getSelectionBackgroundColor();
		virtual pAbstractColor getButtonColor();
		virtual pAbstractColor getButtonBackgroundColor();

		virtual pAbstractFont getFont();

		virtual pAbstractImage getButton();
		virtual pAbstractImage getButtonPressed();

		virtual void add(const char * text);
		virtual void remove(int i);
		virtual void clear();
		virtual const char * getElementAt(int i);
		virtual int getSelected();
		virtual const char * getSelectedElement();
		virtual int getNumberOfElements();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawButton(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<DropDown> pDropDown;
}

#endif
