#include "Renderable.h"

namespace love 
{

	Renderable::~Renderable()
	{
		
	}
	
	bool Renderable::isVisible()
	{
		return visible;
	}

	void Renderable::setVisible(bool visible)
	{
		this->visible = visible;
	}

	void Renderable::render() const
	{
	}

	unsigned char Renderable::getOpacity()
	{
		return this->opacity;
	}

	void Renderable::setOpacity(unsigned char opacity)
	{
		this->opacity = opacity;
	}

}// love
