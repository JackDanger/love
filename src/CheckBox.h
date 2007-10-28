#ifndef LOVE_CHECK_BOX_H
#define LOVE_CHECK_BOX_H

#include "AbstractColor.h"
#include "AbstractImage.h"
#include "Font.h"
#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	class CheckBox : public gcn::CheckBox
	{
	protected:
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pAbstractImage defaultImage; // "off"
		pAbstractImage markedImage; // "on"
		int alignment;
		int verticalAlignment;

	public:
		CheckBox(const string caption = "");
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

		virtual void setColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setBorderColor(const pAbstractColor * color);
		virtual void setDefaultImage(const pAbstractImage * image);
		virtual void setMarkedImage(const pAbstractImage * image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		virtual const char * getCaption();
		virtual const char * getName();
		virtual bool isMarked();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawBox(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<CheckBox> pCheckBox;
}

#endif
