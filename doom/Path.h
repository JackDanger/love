#ifndef AMF_PATH_H
#define AMF_PATH_H

#include <vector>
#include "Point.h"
using namespace std;

namespace love
{

		/**
		* @class Path
		* @version 1.0
		* @since 1.0
		* @author Michael Enger
		* @date 2006-03-07
		* @brief A series of Points designating a path for "something" to follow. Used by AStar
		* @see Point
		* @see AStar
		**/
		class Path
		{
		private:
			// These points represent the path
			vector<Point> points;
		public:
			/**
			 * @brief Default constructor for making a new path (and adding points afterwards).
			 **/
			Path();

			/**
			 * @param points A vector of Points.
			 * @brief A constructor which creates a path based on the passed vector of points.
			 * @see Point
			 **/
			Path(vector<Point> points);

			/**
			 * Deconstructor. Clears the point vector.
			 **/
			~Path();

			/**
			 * @param A Point object which is to be added.
			 * @brief Adds the Point to the vector.
			 **/
			void add(Point point);

			/**
			 * @param The Point object which is to be removed.
			 * @brief Searches the vector and removes the correct point.
			 **/
			void remove(Point point);

			/**
			 * @brief Clears the vector of all information and null-sets all other variables.
			 **/
			void clear();

			/**
			 * @brief Renders all the Points by calling their appropriate render functions.
			 * @see Point::render()
			 **/
			void render();

			/**
			 * @return A boolean value true if the Path is empty.
			 * @brief Checks whether the points vector has any entries.
			 **/
			bool isEmpty();

			/**
			 * @param remove Whether it will remove the Point.
			 * @return The Point object which comes next in the path.
			 * @brief Gets the next point in the path and (potentially) removes the point.
			 **/
			Point getNextPoint(bool remove);

			/**
			 * @brief Calls the other getNextPoint function with the parameter true as default.
			 * @see getNextPoint(bool)
			 **/
			Point getNextPoint();
		};

}// love

#endif