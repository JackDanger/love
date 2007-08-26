/**
* @file Polygon.h
* @author Anders Ruud
* @date 2007-01-20
* @brief Contains definition for class Polygon.
**/

#ifndef LOVE_POLYGON_H
#define LOVE_POLYGON_H

// LOVE
#include "Shape.h"

// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

using std::vector;

namespace love
{

	/**
	* @class Polygon
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-01-20
	* @brief 
	**/
	class Polygon : public Shape 
	{
	private:

		// vertices
		vector<Vextor> vertices;

	public:

		/**
		* @brief Contructs an empty Polygon.
		**/
		Polygon();
		virtual ~Polygon();

		/**
		* @brief Gets vertices.
		* @return vertices.
		**/
		const vector<Vextor> & getVertices() const;

		/**
		* @brief Add a Vextor to the Polygon.
		* @parameter The added Vextor.
		**/
		void addPoint(float x, float y);

		void render();


	};

	typedef boost::shared_ptr<Polygon> pPolygon;

} // love

#endif

