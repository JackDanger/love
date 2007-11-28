#ifndef LOVE_GUI_ELEMENT_H
#define LOVE_GUI_ELEMENT_H

#include "AbstractColor.h"
#include "Color.h"
#include "AnimatedColor.h"

#include "AbstractImage.h"

#include "AbstractFont.h"
#include "GUIText.h"

#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

using std::string;

namespace love
{
	/**
	 * @class GUIElement
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-10-28
	 * @brief
	 **/
	class GUIElement
	{
	protected:
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pGUIText font;

	public:
		GUIElement();
		virtual ~GUIElement();

		virtual void setColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setBorderColor(const pAbstractColor * color);

		virtual void setFont(const pAbstractFont * font);

		virtual pAbstractColor getColor();
		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getBorderColor();
		
		virtual pAbstractFont getFont();

		virtual void setSize(int width, int height) = 0;
		virtual void setWidth(int width) = 0;
		virtual void setHeight(int height) = 0;
		virtual void setBorderSize(unsigned int size) = 0;

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual unsigned int getBorderSize() = 0;

		virtual void adjustSize() = 0;
	};

	typedef boost::shared_ptr<GUIElement> pGUIElement;
}

#endif

