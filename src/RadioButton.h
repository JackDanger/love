#ifndef LOVE_RADIO_BUTTON_H
#define LOVE_RADIO_BUTTON_H

#include "GUIElement.h"

namespace love
{
	class RadioButton : public gcn::RadioButton, public GUIElement
	{
	protected:
		pAbstractImage defaultImage; // "off"
		pAbstractImage markedImage; // "on"
		int alignment;
		int verticalAlignment;

	public:
		RadioButton(const string caption = "");
		~RadioButton();

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
		virtual void setDefaultImage(const pAbstractImage * image);
		virtual void setMarkedImage(const pAbstractImage * image);

		virtual void setFont(const pAbstractFont * font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		virtual const char * getCaption();
		virtual const char * getName();
		virtual bool isMarked();

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractImage getDefaultImage();
		virtual pAbstractImage getMarkedImage();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawBox(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<RadioButton> pRadioButton;
}

#endif
