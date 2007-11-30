#include "GUIElement.h"

namespace love
{
	GUIElement::GUIElement()
	{
	}

	GUIElement::~GUIElement()
	{
	}

	void GUIElement::setColor(const pAbstractColor & color)
	{
		this->color = color;
	}

	void GUIElement::setBackgroundColor(const pAbstractColor & color)
	{
		backgroundColor = color;
	}

	void GUIElement::setBorderColor(const pAbstractColor & color)
	{
		borderColor = color;
	}

	void GUIElement::setFont(const pAbstractFont & font)
	{
		if(this->font == 0)
			this->font.reset<GUIText>(new GUIText(font));
		else
			this->font->setFont(font);
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

	pAbstractFont GUIElement::getFont()
	{
		return font->getFont();
	}
}
