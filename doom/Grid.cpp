#include "Grid.h"
#include "Cell.h"

namespace love
{

	Grid::Grid()
	{

	}

	Grid::Grid(int width, int height, int cellSize)
	{
		setPosition(0,0);
		this->width = width;
		this->height = height;
		this->cellSize = cellSize;
		empty = true;

	}

	Grid::Grid(float x, float y, int width, int height, int cellSize)
	{
		setPosition(x, y);
		this->width = width;
		this->height = height;
		this->cellSize = cellSize;
		empty = true;

	}

	void Grid::createGrid(Grid * parent)
	{

		this->parent = parent;

		int sz = width*height;

		cells.reserve(sz);

		for(int i=0;i<sz;i++)
		{
			float x = (float)((i % width) * cellSize);
			float y = (float)((i / width) * cellSize);

			Cell * pcell = 0;

			if(parent != 0)
				pcell = parent->getCellAt(x, y);

			cells.push_back(Cell(x, y, pcell));
		}

		// Create neighbors
		for(int i=0;i<sz;i++)
		{
			if(width == 1)
			{
				cells[i].setNeighbors(0,0,0,0,0,0,0,0);
				continue;
			}
			
			int nw	= getIndex(i, -1, -1);
			int w	= getIndex(i, -1, 0);
			int sw	= getIndex(i, -1, 1);
			int s	= getIndex(i, 0, 1);
			int se	= getIndex(i, 1, 1);
			int e	= getIndex(i, 1, 0);
			int ne	= getIndex(i, 1, -1);
			int n	= getIndex(i, 0, -1);

			cells[i].setNeighbors(	getNeighbor(nw), getNeighbor(w), getNeighbor(sw), getNeighbor(s), 
									getNeighbor(se), getNeighbor(e), getNeighbor(ne), getNeighbor(n));

		}
	}

	int Grid::getIndex(int i, int dx, int dy)
	{
		int x = i % width;
		int y = (int)(i / width);

		int nx = x + dx;
		int ny = y + dy;

		if(nx < 0 || nx >= width)
			return -1;
		if(ny < 0 || ny >= height)
			return -1;

		return ny * width + nx;
	}
		
	Cell * Grid::getNeighbor(int i)
	{
		if(i >= 0 && i < (int)cells.size())
			return &cells[i];
		else
			return 0;
	}


	Grid::~Grid()
	{
	}

	void Grid::render()
	{

		for(unsigned int i=0;i<cells.size();i++)
		{

			//if(i == 0)
			//	cells[i].colored = true;

			cells[i].render();
			cells[i].colored = false;
		}
	}

	Cell * Grid::getCellAt(const Vextor & position) const
	{
		return getCellAt(position.getX(), position.getY());
	}

	Cell * Grid::getCellAt(float x, float y) const 
	{

		int mx = (int)(x / cellSize);
		int my = (int)(y / cellSize);
		
		unsigned int i = mx + my * this->width;

		if(i >= 0 && i < cells.size())
			return (Cell *)&cells[i];
		else
			return 0;

	}

	int Grid::getSize()
	{
		return width * height;
	}

	void Grid::colorCellAt(float x, float y)
	{
		Cell * c = getCellAt(x, y);

		if(c != 0)
		{
			c->colorParents();
		}
	}

	void Grid::insert(GridElement * g)
	{
		float x = g->getInsertionPosition().getX();
		float y = g->getInsertionPosition().getY();

		Cell * c = getCellAt(x, y);

		if( c != 0)
		{
			c->insert(g);

			empty = false;
		}

	}

	void Grid::clear()
	{
		for(unsigned int i = 0; i< cells.size();i++)
		{
			cells[i].clear();
		}
		empty = true;
	}

	

	void Grid::applyParent()
	{
		for(unsigned int i=0;i<cells.size();i++)
		{
			cells[i].setParentGrid((Grid *)this);
		}
	}

	int Grid::getCellSize()
	{
		return cellSize;
	}

	bool Grid::isEmpty()
	{
		return empty;
	}




}//love