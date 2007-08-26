#include "Path.h"

namespace love
{

	// (DE)CONSTRUCTORS

	Path::Path()
	{}

	Path::Path(vector<Point> path)
	{
		points = path;
	}

	Path::~Path()
	{
		points.clear();
	}

	// PUBLIC FUNCTIONS

	void Path::add(Point point)
	{
		points.push_back(point);
	}

	void Path::remove(Point point)
	{
		for(unsigned int i = 0; i < points.size(); i++)
		{
			if(points.at(i) == point)
				points.erase(points.begin() + i);
		}
	}

	void Path::clear()
	{
		points.clear();
	}

	void Path::render()
	{
		for each (Point p in points)
			p.render();
	}

	bool Path::isEmpty()
	{
		if(points.size() == 0)
			return true;
		else
			return false;
	}

	Point Path::getNextPoint(bool remove)
	{
		if(remove)
		{
			Point temp = points.at(points.size()-1);
			points.erase(points.end());
			return temp;
		}
		else
			return points.at(points.size()-1);
	}

	Point Path::getNextPoint()
	{
		return getNextPoint(true);
	}

}// love