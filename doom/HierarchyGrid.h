#ifndef LOVE_HIERARCHYGRID_H
#define LOVE_HIERARCHYGRID_H

#include "AbstractEntity.h"
#include "Grid.h"
#include "Body.h"
#include "Container.h"
#include "GridElement.h"

#include "love_gl.h"
#include <vector>
#include <climits>

using std::vector;

namespace love
{

	class HierarchyGrid : public AbstractEntity
	{

	private:

		vector<Grid> grids;
		
		int fit(float radius);

	public:
		
		static int insertedElements;

		HierarchyGrid();
		HierarchyGrid(int mapSize, int tileSize, int levels);
		~HierarchyGrid();

		void add(Grid grid);

		void render();

		void color(float x, float y);

		void insert(GridElement * g);

		void remove(GridElement * g);

		void move(GridElement * g);

		void clear();

	};

	typedef boost::shared_ptr<HierarchyGrid> pHierarchyGrid;

}

#endif