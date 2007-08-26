#include "Tile.h"

namespace love 
{


	Tile::Tile()
	{

	}

	Tile::Tile(float x, float y, unsigned short id)
	{
		this->x = x;
		this->y = y;
		this->id = id;

	}

	Tile::~Tile()
	{
	}

	float Tile::getX()
	{
		return this->x;
	}

	void Tile::setX(float x)
	{
		this->x = x;
	}

	float Tile::getY()
	{
		return this->y;
	}

	void Tile::setY(float y)
	{
		this->y = y;
	}

	unsigned short Tile::getId()
	{
		return this->id;
	}

	void Tile::setId(unsigned short id)
	{
		this->id = id;
	}

}// love