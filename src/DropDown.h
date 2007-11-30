#ifndef LOVE_DROP_DOWN_H
#define LOVE_DROP_DOWN_H

#include "GUIElement.h"
#include "GUIList.h"
#include "Padded.h"

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
	class DropDown : public gcn::DropDown, public GUIElement, public Padded
	{
	protected:
		GUIList * list;

		pAbstractColor listColor;
		pAbstractColor listBackgroundColor;
		pAbstractColor hoverColor;
		pAbstractColor hoverBackgroundColor;
		pAbstractColor selectedColor;
		pAbstractColor selectedBackgroundColor;

		pAbstractColor buttonColor;
		pAbstractColor buttonHoverColor;
		pAbstractColor buttonPressedColor;

		pAbstractColor buttonBackgroundColor;
		pAbstractColor buttonHoverBackgroundColor;
		pAbstractColor buttonPressedBackgroundColor;

		pAbstractImage backgroundImage;
		pAbstractImage listImage;

		pAbstractImage button;
		pAbstractImage buttonHover;
		pAbstractImage buttonPressed;

		int spacing; // spacing around items

		bool mCloseOnSelect; // whether to close on select
		bool mHasMouse; // whether the mouse is present in the widget
		int mHoverSelect; // the list item being hovered over

		int getItemHeight(); // height of each list item
		int getItemAt(int x, int y); //gets a list item at the specified (relative to the list) positions (-1 if outside boundaries)

	public:
		DropDown(GUIList * list);
		~DropDown();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setName(const string & name);

		virtual void setSpacing(int spacing);

		virtual void setBackgroundColor(const pAbstractColor & color);
		virtual void setListColor(const pAbstractColor & color);
		virtual void setListBackgroundColor(const pAbstractColor & color);
		virtual void setHoverColor(const pAbstractColor & color);
		virtual void setHoverBackgroundColor(const pAbstractColor & color);
		virtual void setSelectedColor(const pAbstractColor & color);
		virtual void setSelectedBackgroundColor(const pAbstractColor & color);
		virtual void setButtonColor(const pAbstractColor & color);
		virtual void setButtonBackgroundColor(const pAbstractColor & color);
		virtual void setButtonHoverColor(const pAbstractColor & color);
		virtual void setButtonHoverBackgroundColor(const pAbstractColor & color);
		virtual void setButtonPressedColor(const pAbstractColor & color);
		virtual void setButtonPressedBackgroundColor(const pAbstractColor & color);

		virtual void setFont(const pAbstractFont & font);

		virtual void setBackgroundImage(const pAbstractImage & image);
		virtual void setListImage(const pAbstractImage & image);
		virtual void setButton(const pAbstractImage & image);
		virtual void setButtonHover(const pAbstractImage & image);
		virtual void setButtonPressed(const pAbstractImage & image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const string & getName();

		virtual int getSpacing();

		virtual void adjustHeight();
		virtual void adjustSize();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getListColor();
		virtual pAbstractColor getListBackgroundColor();
		virtual pAbstractColor getHoverColor();
		virtual pAbstractColor getHoverBackgroundColor();
		virtual pAbstractColor getSelectedColor();
		virtual pAbstractColor getSelectedBackgroundColor();
		virtual pAbstractColor getButtonColor();
		virtual pAbstractColor getButtonBackgroundColor();
		virtual pAbstractColor getButtonHoverColor();
		virtual pAbstractColor getButtonHoverBackgroundColor();
		virtual pAbstractColor getButtonPressedColor();
		virtual pAbstractColor getButtonPressedBackgroundColor();

		virtual pAbstractFont getFont();

		virtual pAbstractImage getBackgroundImage();
		virtual pAbstractImage getListImage();
		virtual pAbstractImage getButton();
		virtual pAbstractImage getButtonHover();
		virtual pAbstractImage getButtonPressed();

		virtual void add(const string & text);
		virtual void remove(int i);
		virtual void clear();
		virtual string getElementAt(int i);
		virtual int getSelected();
		virtual void setSelected(int selected);
		virtual string getSelectedElement();
		virtual int getNumberOfElements();

		virtual void closeOnSelect(bool value);
		virtual bool closesOnSelect();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawList(gcn::Graphics * graphics);
		virtual void drawButton(gcn::Graphics * graphics);

		virtual void mouseEntered(gcn::MouseEvent & mouseEvent);
		virtual void mouseExited(gcn::MouseEvent & mouseEvent);
		virtual void mouseMoved(gcn::MouseEvent & mouseEvent);
		virtual void mousePressed(gcn::MouseEvent & mouseEvent);
	};

	typedef boost::shared_ptr<DropDown> pDropDown;
}

#endif
