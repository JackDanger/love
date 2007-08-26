#include "AStar.h"

namespace love
{

	Node::Node()
	{
		x = 0;
		y = 0;
		passable = false;
		parent = NULL;
	}

	Node::Node(Point *location)
	{
		x = location->getX();
		y = location->getY();
		passable = true;
		parent = NULL;
	}

	Node::Node(float newX, float newY)
	{
		x = newX;
		y = newY;
		passable = true;
		parent = NULL;
	}

	Node::~Node()
	{
		delete parent;
	}

	bool Node::operator == (Node &n)
	{
		return (x == n.x) && (y == n.y);
	}

	bool Node::operator < (Node &n)
	{
		return (x + y) < (n.x + n.y);
	}

}// love