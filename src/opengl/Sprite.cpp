#include "Sprite.h"

namespace love_opengl
{

	Sprite::Sprite() : width(0), height(0), alpha(1), center_x(0), center_y(0)
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

	void Sprite::setCenter(float x, float y)
	{
		center_x = x;
		center_y = y;
	}

	float Sprite::getCenterX() const
	{
		return center_x;
	}

	float Sprite::getCenterY() const
	{
		return center_y;
	}

} // love
