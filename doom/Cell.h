#ifndef LOVE_CELL_H
#define LOVE_CELL_H

#include "Entity.h"
#include "Container.h"
#include "GridElement.h"

#include <set>
#include <bitset>

using std::set;

namespace love
{
		
	class Grid;

	class Cell : public Entity
	{
	private:

		// Contains IDs for all resident GridElements.
		set<int> elements;

		// The Cell which contains this cell one the grid "above"
		Cell * parentCell;

		// The Grid this Cell belongs to.
		Grid * parentGrid;

		// Pointers to nearby cells
		Cell * nw;
		Cell * w;
		Cell * sw;
		Cell * s;
		Cell * se;
		Cell * e;
		Cell * ne;
		Cell * n;

		// Indicates whether the Cell is empty or not.
		bool empty;

	public:
	
		bool colored;

		Cell();
		Cell(float x, float y, Cell * parentCell);
		~Cell();

		void render();

		void colorParents();

		void insert(GridElement * g);

		void remove(GridElement * g);

		void clear();

		bool isResident(GridElement * g);

		int getCellSize();

		void setNeighbors(Cell * nw, Cell * w, Cell * sw, Cell * s, Cell * se, Cell * e, Cell * ne, Cell * n);

		Cell * getNW();
		Cell * getW();
		Cell * getSW();
		Cell * getS();
		Cell * getSE();
		Cell * getE();
		Cell * getNE();
		Cell * getN();


		Cell * getParentCell() const;

		void setParentCell(Cell * c);

		Grid * getParentGrid() const;
		
		void setParentGrid(Grid * g);

		const set<int> & getElements() const;

		bool isEmpty();

	};
}

#endif