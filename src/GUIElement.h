#ifndef LOVE_GUI_ELEMENT_H
#define LOVE_GUI_ELEMENT_H

#include "AbstractColor.h"
#include "Color.h"
#include "AnimatedColor.h"

#include "AbstractImage.h"

#include "AbstractFont.h"
#include "Font.h"
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

	public:
		GUIElement();
		~GUIElement();

		virtual void setColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setBorderColor(const pAbstractColor * color);

		/*
		virtual void setColor(const pColor * color);
		virtual void setBackgroundColor(const pColor * color);
		virtual void setBorderColor(const pColor * color);

		virtual void setColor(const pAnimatedColor * color);
		virtual void setBackgroundColor(const pAnimatedColor * color);
		virtual void setBorderColor(const pAnimatedColor * color);
		*/

		virtual pAbstractColor getColor();
		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getBorderColor();
	};

	typedef boost::shared_ptr<GUIElement> pGUIElement;
}

#endif

