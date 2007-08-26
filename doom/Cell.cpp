#include "Cell.h"
#include "Grid.h"

namespace love
{

	Cell::Cell()
	{
	}

	Cell::Cell(float x, float y, Cell * parentCell)
	{
		setPosition(x, y);
		this->parentCell = parentCell;

		this->parentGrid = 0;

		colored = false;
		empty = true;
	}


	Cell::~Cell()
	{
	}

	void Cell::render()
	{

		float size = (float)getCellSize();

		if(colored)
		{

			glColor4ub(255,0,0,50);
			glBegin(GL_QUADS);
				glVertex2f(getX(), getY());
				glVertex2f(getX(), getY()+size);
				glVertex2f(getX()+size, getY()+size);
				glVertex2f(getX()+size, getY());
			glEnd();
		}
	}


	void Cell::colorParents()
	{
		

		if(parentCell != 0)
		{
			colored = true;
			parentCell->colorParents();
		}
	}

	void Cell::insert(GridElement * g)
	{
		g->setParentCell(this);
		elements.insert(g->getGridElementId());
		empty = false;
	}

	void Cell::remove(GridElement * g)
	{
		elements.erase(elements.find(g->getGridElementId()));

		if(elements.size() <= 0)
			empty = true;
	}

	void Cell::clear()
	{
		elements.clear();
		empty = true;
	}

	bool Cell::isResident(GridElement * g)
	{
		return elements.find(g->getGridElementId()) != elements.end();
	}

	int Cell::getCellSize()
	{
		return parentGrid->getCellSize();
	}

	void Cell::setNeighbors(Cell * nw, Cell * w, Cell * sw, Cell * s, Cell * se, Cell * e, Cell * ne, Cell * n)
	{
		this->nw	= nw;
		this->w		= w;
		this->sw	= sw;
		this->s		= s;
		this->se	= se;
		this->e		= e;
		this->ne	= ne;
		this->n		= n;
	}

	Cell * Cell::getNW()
	{
		return nw;
	}

	Cell * Cell::getW()
	{
		return w;
	}

	Cell * Cell::getSW()
	{
		return sw;
	}

	Cell * Cell::getS()
	{
		return s;
	}

	Cell * Cell::getSE()
	{
		return se;
	}

	Cell * Cell::getE()
	{
		return e;
	}

	Cell * Cell::getNE()
	{
		return ne;
	}

	Cell * Cell::getN()
	{
		return n;
	}

	Cell * Cell::getParentCell() const
	{
		return parentCell;
	}

	void Cell::setParentCell(Cell * c)
	{
		this->parentCell = c;
	}

	Grid * Cell::getParentGrid() const
	{
		return parentGrid;
	}
	
	void Cell::setParentGrid(Grid * g)
	{
		this->parentGrid = g;
	}

	const set<int> & Cell::getElements() const
	{
		return elements;
	}

	bool Cell::isEmpty()
	{
		return empty;
	}



}