#include "GUIElement.h"

namespace love
{
	GUIElement::GUIElement()
	{
	}

	GUIElement::~GUIElement()
	{
	}

	void GUIElement::setColor(const pAbstractColor * color)
	{
		this->color = (*color);
	}

	void GUIElement::setBackgroundColor(const pAbstractColor * color)
	{
		this->backgroundColor = (*color);
	}

	void GUIElement::setBorderColor(const pAbstractColor * color)
	{
		this->borderColor = (*color);
	}

	pAbstractColor GUIElement::getColor()
	{
		return color;
	}

	pAbstractColor GUIElement::getBackgroundColor()
	{
		return backgroundColor;
	}

	pAbstractColor GUIElement::getBorderColor()
	{
		return borderColor;
	}
}
