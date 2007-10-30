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

	/*
	void GUIElement::setColor(const pColor * color)
	{
		this->color = (*color);
	}

	void GUIElement::setBackgroundColor(const pColor * color)
	{
		this->backgroundColor = (*color);
	}

	void GUIElement::setBorderColor(const pColor * color)
	{
		this->borderColor = (*color);
	}

	void GUIElement::setColor(const pAnimatedColor * color)
	{
		this->color = (*color);
	}

	void GUIElement::setBackgroundColor(const pAnimatedColor * color)
	{
		this->backgroundColor = (*color);
	}

	void GUIElement::setBorderColor(const pAnimatedColor * color)
	{
		this->borderColor = (*color);
	}
	*/

	pAbstractColor GUIElement::getColor()
	{
		return color;
	}

	pAbstractColor GUIElement::getBackgroundColor()
	{
		return color;
	}

	pAbstractColor GUIElement::getBorderColor()
	{
		return color;
	}
}