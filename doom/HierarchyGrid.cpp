#include "HierarchyGrid.h"

namespace love
{
	
	int HierarchyGrid::insertedElements = 0;

	HierarchyGrid::HierarchyGrid()
	{
	}

	HierarchyGrid::HierarchyGrid(int mapSize, int tileSize, int levels)
	{
		for(int i=0;i<levels;i++)
		{
			
			int width	= mapSize	/ (mapSize/(int)(pow((double)2, (double)i)));
			int height	= width;
			int cs		= (int)(mapSize * tileSize /(pow((double)2, (double)i)));


			grids.push_back(Grid(width, height, cs));
		}

		// Set parent grids
		for(int i=0;i<levels;i++)
		{
			if(i > 0)
				grids[i].createGrid(&grids[i-1]);
			else
				grids[i].createGrid(0);

			grids[i].applyParent();
		}

		

	}

	HierarchyGrid::~HierarchyGrid()
	{
	}

	void HierarchyGrid::add(Grid grid)
	{
		grids.push_back(grid);
	}

	void HierarchyGrid::render()
	{

		for(int i=0;i<(int)grids.size();i++)
		{

			int alp = 60+(i*10);
			if(alp>255) alp = 255;

			glColor4ub(0,0,0,alp);
			
			grids[i].render();

		}

	}

	void HierarchyGrid::color(float x, float y)
	{
		if(!grids.empty())
			grids.back().colorCellAt(x, y);
	}


	int HierarchyGrid::fit(float radius)
	{
		// Find the Grid with the proper cell size
		for(int i = (int)grids.size() - 1; i >= 0 ; i-- )
			if(grids[i].getCellSize() > 2 * radius)
				return i;

		return 0;
	}

	void HierarchyGrid::insert(GridElement * g)
	{

		float r = g->getInsertionRadius();

		int level = fit(r);

		grids[level].insert(g);

	}

	void HierarchyGrid::remove(GridElement * g)
	{
		g->removeFromCell();
	}

	void HierarchyGrid::move(GridElement * g)
	{
	}

	void HierarchyGrid::clear()
	{

		for(unsigned int i = 0; i < grids.size(); i++)
			grids[i].clear();
	}


}//love