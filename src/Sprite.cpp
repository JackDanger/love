#include "Sprite.h"

namespace love
{

	Sprite::Sprite() : width(0), height(0), alpha(1)
	{
	}

	Sprite::~Sprite()
	{
	}

	float Sprite::getWidth() const
	{
		return this->width;
	}

	float Sprite::getHeight() const
	{
		return this->height;
	}

	float Sprite::getAlpha() const
	{
		return this->alpha;
	}

	void Sprite::setAlpha(float alpha)
	{
		this->alpha = alpha;
	}

} // love
