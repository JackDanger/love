/**
* @file CollisionDetector.h
* @brief Contains definition of class CollisionDetector.
* @date 2006-04-01
* @author Anders Ruud
**/

#ifndef LOVE_COLLISION_DETECTOR_H
#define LOVE_COLLISION_DETECTOR_H

#include "Object.h"
#include "Polygon.h"
#include "interval.h"
#include "Body.h" 
#include "Container.h"
#include "Cell.h"

#include <vector>
#include <set>

using namespace std;

namespace love
{


	/**
	* @class CollisionDetector
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-04-01
	* @brief Detects collisions between shapes.
	* @todo Make this into static class?
	**/
	class CollisionDetector : public Object
		{
		private:
			
			/**
			* @brief Gets the projection interval for the given Polygon
			* along the given axis.
			**/
			void calculateInterval(pBody & b, Vextor & axis, interval& intr);

			float getOverlap(interval & i1, interval & i2);

			bool axisSeparates(	pBody & b1, pBody & b2, 
								Vextor & axis, 
								Vextor & xPosition, Vextor & xVelocity, Matrix & xOrientation, 
								float & t);

			bool find_mtd(vector<Vextor> & axis, vector<float> & t_axis, Vextor & N, float & t);

			void handleCollision(pBody& b1, pBody& b2, Vextor& N, float t);
			void handleOverlap(pBody& b1, pBody& b2, Vextor& mtd);

			int numcells;

		public:

			CollisionDetector();
			~CollisionDetector();

			// @todo setResponse()?-ish;


			/**
			* @brief Detects a collision between to polygons.
			**/
			bool intersects(pBody & b1, pBody & b2, Vextor & N, float & t);

			bool intersects(pBody &b1, pBody &b2);

			// bool detect(Entity &e1, Entity &e2);

			void resolve(const Container<Body> & bodies);
			void resolve(pBody &b1, pBody &b2);
			void resolveCell(const Container<Body> & bodies, pBody & b, Cell * c);
			void resolveGrid(const Container<Body> & bodies, pBody & b, Cell * c);

		};

	typedef boost::shared_ptr<CollisionDetector> pCollisionDetector;

}// love

#endif