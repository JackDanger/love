/**
* @file Body.h
* @brief Contains definition of class Body.
* @date 2006-05-05
* @author Anders Ruud
**/

#ifndef LOVE_BODY_H
#define LOVE_BODY_H

#include "Entity.h"
#include "Vextor.h"
#include "Matrix.h"
#include "GridElement.h"
#include "Physical.h"
#include "PointMass.h"

#include <vector>
#include <cmath>

using namespace std;

namespace love 
{

	class Cell;
	class Grid;

	/**
	* @class Body
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-05-05
	* @brief A Body is convex shape to which you can apply physics and collision handling.
	**/
	class Body : public Entity, public GridElement, public Physical, public PointMass
	{

	private:
		
		float VERY_SMALL;

	public:

		/**
		* @brief Creates a new Body object.
		**/
		Body();

		/**
		* @brief Creates a new Body object.
		**/
		Body(Vextor position, vector<Vextor> vertices, float mass);

		~Body();


		/**
		* @brief Renders the body once.
		**/
		void render();

		void renderVextor(const Vextor & v);

		/**
		* @brief Updates the body once.
		* @param dt Time since last frame.
		**/
		void update(float dt);

		/**
		* @brief Adds an impulse to the displacement.
		* @param f The impulse to add to the displacement.
		* @param dt Time since last frame in seconds.
		**/
		void addImpulse(const Vextor & f, float dt);
			
	};

	typedef boost::shared_ptr<Body> pBody;

} // love

#endif
