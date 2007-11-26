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
		if(color == 0)
			this->color.reset();
		else
			this->color = (*color);
		//this->font->setColor(*color);
	}

	void GUIElement::setBackgroundColor(const pAbstractColor * color)
	{
		if(color == 0)
			this->backgroundColor.reset();
		else
			this->backgroundColor = (*color);
	}

	void GUIElement::setBorderColor(const pAbstractColor * color)
	{
		if(color == 0)
			this->borderColor.reset();
		else
			this->borderColor = (*color);
	}

	void GUIElement::setFont(const pAbstractFont * font)
	{
		if(this->font == 0)
			this->font.reset<GUIText>(new GUIText(*font));
		else if(font == 0)
			this->font.reset();
		else
			this->font->setFont(*font);
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
