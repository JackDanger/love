#ifndef LOVE_CHECK_BOX_H
#define LOVE_CHECK_BOX_H

#include "GUIElement.h"

namespace love
{
	class CheckBox : public gcn::CheckBox, public GUIElement
	{
	protected:
		pAbstractImage defaultImage; // "off"
		pAbstractImage hoverImage;
		pAbstractImage markedImage; // "on"
		pAbstractColor hoverColor;
		pAbstractColor markedColor;
		int alignment;
		int verticalAlignment;
		bool mHasMouse; // when the mouse is over the widget

	public:
		CheckBox(const string & caption = "");
		~CheckBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);

		virtual void setCaption(const char * caption);
		virtual void setName(const char * name);
		virtual void setMarked(bool marked);

		virtual void align(int alignment);
		virtual void valign(int alignment);

		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setHoverColor(const pAbstractColor * color);
		virtual void setMarkedColor(const pAbstractColor * color);
		virtual void setDefaultImage(const pAbstractImage * image);
		virtual void setHoverImage(const pAbstractImage * image);
		virtual void setMarkedImage(const pAbstractImage * image);

		virtual void setFont(const pAbstractFont * font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		virtual const char * getCaption();
		virtual const char * getName();
		virtual bool isMarked();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getHoverColor();
		virtual pAbstractColor getMarkedColor();
		virtual pAbstractImage getDefaultImage();
		virtual pAbstractImage getHoverImage();
		virtual pAbstractImage getMarkedImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawBox(gcn::Graphics * graphics);

		//overriding the guichan stuff to give hover "ability"
		virtual void mouseEntered(gcn::MouseEvent & mouseEvent);
		virtual void mouseExited(gcn::MouseEvent & mouseEvent);
	};

	typedef boost::shared_ptr<CheckBox> pCheckBox;
}

#endif
