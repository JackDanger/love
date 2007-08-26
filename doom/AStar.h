#include "Polygon.h"
#include "Point.h"
#include "Path.h"
#include <vector>
using namespace std;

#ifndef AMF_NODE_H
#define AMF_NODE_H

namespace love
{


	/**
	* @class Node
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2006-03-07
	* @brief Node used by the class AStar.
	**/
	class Node
	{
	public:
		float x;
		float y;
		float g;
		float h;
		bool passable;
		Node *parent;

		/**
		 * @brief Default constructor which initializes all values (as containing nothing).
		 **/
		Node();

		/**
		 * @param location The Point to create the Node at.
		 * @brief Constructor which creates a Node based on a Point object.
		 * @see Point
		 **/
		Node(Point *location);

		/**
		 * @param newX The X-position of the new Node.
		 * @param newY The Y-position of the new Node.
		 * @brief Constructor which creates a Node at a certain position.
		 * @see Point
		 **/
		Node(float newX, float newY);

		/**
		 * @brief Deconstructor. Deletes pointers.
		 **/
		~Node();

		bool operator == (Node &n);
		bool operator < (Node &n);
	};


}// love

#endif

#ifndef AMF_ASTAR_H
#define AMF_ASTAR_H

#define OPEN 1
#define CLOSED 2


namespace love
{

	/**
	* @class AStar
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2006-03-07
	* @brief A basic implementation of the A* algorithm.
	**/
	class AStar 
	{
	private:
		Point *begin; //the beginning of the path
		Point *end; //the end of the path
		Polygon * object; //object which will be moved along path
		vector<Node*> open;
		vector<Node*> closed;
		Path path;
		float size; //distance between the nodes

		/**
		 * @param list The list which the node will be added to.
		 * @param node The Node pointer to be added.
		 * @brief Adds a Node pointer to a vector.
		 * @see Node
		 **/
		void add(int list, Node *node);

		/**
		 * @param list The list which the node will be removed from.
		 * @param node The Node pointer to be removed.
		 * @brief Removes a Node pointer from one of the vectors. Why couldn't vectors be easier to use??
		 * @see Node
		 **/
		void remove(int list, Node *node);

		/**
		 * @param list Designates which list to search in
		 * @param x X-value of the sought Node
		 * @param y Y-value of the sought Node
		 * @return Pointer to a Node object
		 * @brief Searches the designated list for a Node which has the designated x and y values and returns that.
		 * @see Node
		 **/
		Node* getNode(int list, float x, float y);

		/**
		 * @param x1 X-position of the first point.
		 * @param y1 Y-position of the first point.
		 * @param x2 X-position of the second point.
		 * @param y2 Y-position of the second point.
		 * @param allowDiagonals Designates whether the algorithm will include diagonal movement.
		 * @return The distance between the two points.
		 * @brief Calculates the distance between the two points (x1,y1) and (x2,y2). It uses size * 1.0
		 *        for the horizontal/vertical distance and size * 1.4 for diagonal disance (if allowed).
		 **/
		float calculateDistance(float x1, float y1, float x2, float y2, bool allowDiagonals);

		/**
		 * @brief Calls the other calculateDistance function with the bool false. Used as a default.
		 * @see calculateDistance(float,float,float,float,bool)
		 **/
		float calculateDistance(float x1, float y1, float x2, float y2);

		/**
		 * @param current A pointer to the current Node being worked upon.
		 * @param includeDiagonals Dictates whether diagonal movement is allowed.
		 * @brief A recursive function which passes through the different nodes finding a path to the end.
		 *        (a scary Mike function)
		 **/
		Node* findPath(Node *current, bool includeDiagonals);
		int count; //remove this and change Node* to void for the future.

		/**
		 * @brief Calls the other findPath function with the bool false. Used as a default.
		 * see findPath(Node*,bool)
		 **/
		void findPath(Node *current);

		/**
		 * @param current The Node which the path leads to.
		 * @brief Creates a Path to the passed Node.
		 **/
		void createPath(Node *current);

		/**
		 * @return A Path object dictating the path between from and to.
		 * @brief Sets everything up and calls the various functions to create a path. Used so
		 *        that I don't have to repeat all the commands for each of the public getPath functions.
		 **/
		Path getPath();
	public:
		/**
		 * @brief Default constructor. Sets the size (distance between nodes) to 10.
		 **/
		AStar();

		/**
		 * @param distanceBetweenNodes Sets the size (the distance between the nodes).
		 * @brief Probably the constructor which will be used the most (as the other one is just ghei)!
		 **/
		AStar(float distanceBetweenNodes);

		/**
		 * @brief Deconstructor. Deletes pointers and clears vectors.
		 **/
		~AStar();

		/**
		 * @param from The Point where the search will start.
		 * @param to The Point where the search will end (if it doesn't fail).
		 * @return A Path betwen the Points.
		 * @brief Used to get a Path from Point to Point.
		 * @see Point
		 * @see Path
		 **/
		Path getPath(Point &from, Point &to);

		/**
		 * @param from The CPolygon where the search will start (potentially the object which will move).
		 * @param to The Point where the search will end (if it doesn't fail).
		 * @return A Path between the CPolygon and the point.
		 * @brief Used to get a Path from CPolygon to Point.
		 * @see CPolygon
		 * @see Point
		 * @see Path
		 **/
		Path getPath(Polygon &from, Point &to);

		/**
		 * @param from The CPolygon where the search will start (potentially the object which will move).
		 * @param to The CPolygon where the search will end (if it doesn't fail).
		 * @return A Path between the two CPolygons.
		 * @brief Used to get a Path from CPolygon to CPolygon.
		 * @see CPolygon
		 * @see Path
		 **/
		Path getPath(Polygon &from, Polygon &to);

	};

}// love

#endif