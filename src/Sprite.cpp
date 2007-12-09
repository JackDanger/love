#include "Sprite.h"

namespace love
{

	Sprite::Sprite()
	{
		setType(LOVE_TYPE_SPRITE);
		this->width = 0;
		this->height = 0;
		this->alpha = 255;
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

	void Sprite::bind()
	{
	}

	void Sprite::beginRender()
	{
	}

	void Sprite::sendVertices()
	{
	}

	void Sprite::endRender()
	{
	}


	void Sprite::render()	
	{
	}

	void Sprite::render(float x, float y)
	{
	}

	void Sprite::renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{

	}

	void Sprite::render(float x, float y, float width, float height)
	{
	}


}// love
