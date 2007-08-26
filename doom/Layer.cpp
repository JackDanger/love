#include "Layer.h"

namespace love
{


	/**
	* This default contructor sets some default values.
	**/
	Layer::Layer()
	{
		setType(LOVE_TYPE_LAYER);
	}

	Layer::~Layer()
	{
	}

	void Layer::update(float dt)
	{
	}

	void Layer::render()
	{
	}

	float Layer::getOffsetX()
	{
		return xOffset;
	}

	float Layer::getOffsetY()
	{
		return yOffset;
	}

	bool Layer::isRepeatingX()
	{
		return xRepeat == true;
	}

	bool Layer::isRepeatingY()
	{
		return yRepeat = true;
	}

}// love