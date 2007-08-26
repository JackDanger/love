#include "Astar.h"

namespace love
{
		// (DE)CONSTRUCTORS

		AStar::AStar()
		{
			size = 10.0f;
		}

		AStar::AStar(float distanceBetweenNodes)
		{
			size = distanceBetweenNodes;
		}

		AStar::~AStar()
		{
			delete begin;
			delete end;
			open.clear();
			closed.clear();
		}

		// PRIVATE FUNCTIONS

		void AStar::add(int list, Node *node)
		{
			switch(list)
			{
				case OPEN:
					open.push_back(node);
					break;
				case CLOSED:
					closed.push_back(node);
					break;
			}
		}

		void AStar::remove(int list, Node *node)
		{
			switch(list)
			{
				case OPEN:
					for(unsigned int i = 0; i < open.size(); i++)
					{
						if(open.at(i) == node)
						{
							open.erase(open.begin() + i);
						}
					}
					break;
				case CLOSED:
					for(unsigned int i = 0; i < closed.size(); i++)
					{
						if(closed.at(i) == node)
							closed.erase(closed.begin() + i);
					}
					break;
			}
		}

		Node* AStar::getNode(int list, float x, float y)
		{
			switch(list)
			{
				case OPEN:
					for(unsigned int i = 0; i < open.size(); i++)
					{
						if(open.at(i)->x == x && open.at(i)->y == y)
							return open.at(i);
					}
					break;
				case CLOSED:
					for(unsigned int i = 0; i < closed.size(); i++)
					{
						if(closed.at(i)->x == x && closed.at(i)->y == y)
							return closed.at(i);
					}
					break;
			}

			return NULL;
		}

		float AStar::calculateDistance(float x1, float y1, float x2, float y2, bool includeDiagonals)
		{
			 float total = 0;
			 
			 float x = x2 - x1;
			 if(x < 0)
				 x = -x;

			 float y = y2 - y1;
			 if(y < 0)
				 y = -y;

			 if(includeDiagonals)
			 {
				 if(x > y)
					 total = y * (int)(1.4 * size) + ((x - y) * size);
				 else //y > x
					 total = x * (int)(1.4 * size) + ((y - x) * size);
			 }
			 else
			 {
				 total = (x + y) * size;
			 }

			 return total;
		}

		float AStar::calculateDistance(float x1, float y1, float x2, float y2)
		{
			return calculateDistance(x1,y1,x2,y2,false);
		}

		Node* AStar::findPath(Node *current, bool allowDiagonals)
		{
			Node *temp = NULL;

			//move node to closed list
			add(CLOSED,current);
			remove(OPEN,current);

			//for each adjacent node
			for(float x = (current->x - size); x < (current->x + size); x += size)
			{
				for(float y = (current->y - size); y < (current->y + size); y += size)
				{
					if( !(x == current->x && y == current->y) && (getNode(CLOSED,x,y) == NULL) )
					{
						temp = getNode(OPEN,x,y);

						if(temp == NULL)
						{
							temp = new Node(x,y);
							//if it's in range of the end, then we assume that it's the end
							if( (x == end->getX() && y == end->getY()) 
								|| ( ((x >= (end->getX() - size)) && (x < end->getX() ))
									&& ((y >= (end->getY() - size)) && (y < end->getY() )) )
								)
							{
								temp->x = end->getX();
								temp->y = end->getY();
							}
							if(temp->passable)
							{
								temp->parent = current;
								temp->g = current->g + calculateDistance(current->x,current->y,x,y,allowDiagonals);
								temp->h = calculateDistance(end->getX(),end->getY(),x,y,false);
								add(OPEN,temp);
							}
						}
						else
						{
							if(temp->passable)
							{
								float tempG = current->g + calculateDistance(current->x,current->y,x,y,allowDiagonals);
								if(tempG < temp->g)
								{
									temp->g = tempG;
									temp->parent = current;
								}
							}
						}
					} //endif
				} //endfor
			} //endfor

			//get the next node to check (with the lowest f [f = g + h] )
			temp = NULL;
			for(unsigned int i = 0; i < open.size(); i++)
			{
				if( (temp == NULL) || (open.at(i)->g + open.at(i)->h) < (temp->g + temp->h) )
					temp = open.at(i);
			}
			//and repeat the process
			count++;
			if( (temp != NULL) //unless there are no more (path not found)
				&& (getNode(CLOSED,end->getX(),end->getY()) == NULL) && count <= 10) //or the target is in the closed list (path found)
				findPath(temp,allowDiagonals);
			else
				return current;

			// I added this, Mike. (You had a control-path warning) (>^-^)>
			return 0;
		}

		void AStar::findPath(Node *current)
		{
			findPath(current, false);
		}

		void AStar::createPath(Node *current)
		{
			if(current->parent != NULL)
				createPath(current->parent);

			Point temp;
			temp.setX(current->y);
			temp.setY(current->y);

			path.add(temp);
		}

		Path AStar::getPath()
		{
			Node *temp = new Node(begin);

			open.clear();
			closed.clear();
			path.clear();
			
			open.push_back(temp);
			count = 0;
			temp = findPath(temp,true);
			
			//temp = getNode(CLOSED,end->getX(),end->getY());
			if(temp != NULL)
				createPath(temp);
			return path;
		}

		// PUBLIC FUNCTIONS

		Path AStar::getPath(Point &from, Point &to)
		{
			begin = &from;
			end = &to;

			return getPath();
		}

		Path AStar::getPath(Polygon &from, Point &to)
		{
			//begin = &from.getCentroid();
			end = &to;

			return getPath();
		}

		Path AStar::getPath(Polygon &from, Polygon &to)
		{
			//begin = &from.getCentroid();
			//end = &to.getCentroid();

			return getPath();
		}
}// love