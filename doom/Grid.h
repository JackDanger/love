#ifndef LOVE_GRID_H
#define LOVE_GRID_H
#include "love_gl.h"

#include <vector>
#include "Entity.h"
#include "GridElement.h"
#include "Cell.h"
#include "Vextor.h"

using std::vector;

namespace love
{

	class Grid : public Entity
	{

	private:

		// The size of the Grid in cells
		int width;
		int height;

		// The size of each cell in pixels
		int cellSize;

		// Storage for all the cells
		vector<Cell> cells;

		// The grid "above" this one with double cell size
		Grid * parent;

		// Whether the grid has no elements
		bool empty;

	public:
		
		Grid();
		Grid(int width, int height, int cellSize);
		Grid(float x, float y, int width, int height, int cellSize);

		void createGrid(Grid * parent = 0);
		~Grid();

		void render();

		Cell * getCellAt(float x, float y) const;
		Cell * getCellAt(const Vextor & position) const;

		int getSize();

		void colorCellAt(float x, float y);

		void insert(GridElement * g);

		void clear();
 
		void applyParent();

		int getCellSize();

		bool isEmpty();

		Cell * getNeighbor(int i);

		int getIndex(int i, int dx, int dy);


	};

	typedef boost::shared_ptr<Grid> pGrid;

}

#endif