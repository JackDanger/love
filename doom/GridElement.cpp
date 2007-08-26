#include "GridElement.h"
#include "Vextor.h"
#include "Cell.h"

namespace love
{

	GridElement::GridElement()
	{
		this->level = -1;
		parentCell = 0;
	}

	GridElement::~GridElement()
	{
	}

	void GridElement::setParentCell(Cell * c)
	{
		this->parentCell = c;
	}

	Cell * GridElement::getParentCell()
	{
		return parentCell;
	}

	void GridElement::removeFromCell()
	{
		if(parentCell != 0)
			parentCell->remove(this);

		parentCell = 0;
	}

	int GridElement::getLevel()
	{
		return level;
	}

	void GridElement::setLevel(int level)
	{
		this->level = level;
	}

}//love